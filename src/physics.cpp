//
//  state.cpp
//  banana
//
//  Created by Marco Fattorel on 29/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#include "physics.hpp"

#include <iostream>

using namespace Mathematics;
using namespace Physics;

struct Collision
{
	Vector3 direction;
	Vector3 point;
	float magnitude;
};

static std::vector<Collision> collisions(const State& state)
{
	std::vector<Collision> ret;
	Matrix44 mat = Matrix44().translate(state.position) * state.orientation.matrix();
	for(auto& v : state.positions)
	{
		Vector3 pos = mat * v;
		if(pos.vec.y < 0.f)
		{
			ret.emplace_back(Collision{Vector3().up(), pos, abs(pos.vec.y)});
		}
	}
	
	return ret;
}

//static void forces(const State& state, float t, Vector3& force, Vector3& torque)
//{
	// attract towards origin
//	force.zero();
//	torque.zero();
//	force.vec.y = -9.81f;
//	torque.vec.y = 1.f;
	
//	force = -10 * state.position;
	
	// sine force to add some randomness to the motion
	
//	force.vec.x += 10 * sin(t*0.9f + 0.5f);
//	force.vec.y += 11 * sin(t*0.5f + 0.4f);
//	force.vec.z += 12 * sin(t*0.7f + 0.9f);
	
	// sine torque to get some spinning action
	
//	torque.vec.x = 1.0f * sin(t*0.9f + 0.5f);
//	torque.vec.y = 1.1f * sin(t*0.5f + 0.4f);
//	torque.vec.z = 1.2f * sin(t*0.7f + 0.9f);
	
	// damping torque so we dont spin too fast
	
//	torque -= 0.2f * state.angularVelocity;
//	std::cout << torque.to_string() << std::endl;
//}

void State::recalculate()
{
	velocity = momentum * inverseMass;
	angularVelocity = inverseInertiaTensor * angularMomentum;
	orientation.normalize();
	float4 fspin;
	fspin.xyz = angularVelocity.vec;
	fspin.w = 0.f;
	spin = .5f * Quaternion(fspin) * orientation;
	Matrix44 translation; translation.translate(position);
	bodyToWorld = translation * orientation.matrix();
	worldToBody = bodyToWorld.inverse();
}

State State::interpolate(const State& a, const State& b, float alpha)
{
	State state = b;
	state.position = a.position*(1.f-alpha) + b.position*alpha;
	state.momentum = a.momentum*(1.f-alpha) + b.momentum*alpha;
	state.orientation = slerp(a.orientation, b.orientation, alpha);
	state.angularMomentum = a.angularMomentum*(1.f-alpha) + b.angularMomentum*alpha;
	state.recalculate();
	return state;
}

void State::integrate(State& state, float t, float dt)
{
	Derivative a = Derivative::evaluate(state, t);
	Derivative b = Derivative::evaluate(state, t, dt*0.5f, a);
	Derivative c = Derivative::evaluate(state, t, dt*0.5f, b);
	Derivative d = Derivative::evaluate(state, t, dt, c);
	
	state.position += 1.0f/6.0f * dt * (a.velocity + 2.0f*(b.velocity + c.velocity) + d.velocity);
	state.momentum += 1.0f/6.0f * dt * (a.force + 2.0f*(b.force + c.force) + d.force);
	state.orientation += 1.0f/6.0f * dt * (a.spin + 2.0f*(b.spin + c.spin) + d.spin);
	state.angularMomentum += 1.0f/6.0f * dt * (a.torque + 2.0f*(b.torque + c.torque) + d.torque);
	
	const float e = 0.2;
	const float u = 0.97;
	std::vector<Collision> collision = collisions(state);
	const float scale = 1.f/float(collision.size());
	for(auto& c : collision)
	{
		if(c.direction.dot(state.momentum) > 0.f)
			continue;
		state.position += c.direction * c.magnitude;
		
		const Vector3 r = c.point - state.position;
		Vector3 velocityAtPoint = state.velocity + state.angularVelocity.cross(r);
		const float vn = min (0.f, velocityAtPoint.dot(c.direction));
		
		Matrix44 rotation = state.orientation.matrix();
		Matrix44 transposeRotation = rotation.transpose();
		Matrix44 i = rotation * state.inverseInertiaTensor * transposeRotation;
		
		const float k = state.inverseMass + r.cross(c.direction).dot(i * r.cross(c.direction));
		const float j = -(1+e) * vn / k;
		
		state.momentum += c.direction * j * scale;
		state.angularMomentum += r.cross(c.direction) * j * scale;
		
		Vector3 tangentVelocity = velocityAtPoint - c.direction * velocityAtPoint.dot(c.direction);
		if(tangentVelocity.lengthSquared() > epsilonSquared)
		{
			Vector3 tangent = tangentVelocity.unit();
			const float vt = velocityAtPoint.dot(tangent);
			const float kt = state.inverseMass + r.cross(tangent).dot(i * r.cross(tangent));
			float jt = clamp(-vt/kt, -u*j, u*j);
			state.momentum += tangent * jt * scale;
			state.angularMomentum += r.cross(tangent) * jt * scale;
		}
	}
	state.recalculate();
}

std::string State::to_string()
{
	return "State\n\tposition:" + position.to_string() +
	"\n\tmomentum:" + momentum.to_string() +
	"\n\torientation:" + orientation.to_string() +
	"\n\tangularMomentum:" + angularMomentum.to_string() +
	"\n\tvelocity:" + velocity.to_string() +
	"\n\tspin:" + spin.to_string() +
	"\n\tangularVelocity:" + angularVelocity.to_string();
}

Derivative Derivative::evaluate(const State& state, float t)
{
	Derivative output;
	output.velocity = state.velocity;
	output.spin = state.spin;
	state.forces(state, t, output.force, output.torque);
	return output;
}

Derivative Derivative::evaluate(State state, float t, float dt, const Derivative& derivative)
{
	state.position += derivative.velocity * dt;
	state.momentum += derivative.force * dt;
	state.orientation += derivative.spin * dt;
//	std::cout << state.angularVelocity.to_string() << std::endl;
	state.angularMomentum += derivative.torque * dt;
	state.recalculate();
	
	Derivative output;
	output.velocity = state.velocity;
	output.spin = state.spin;
	state.forces(state, t+dt, output.force, output.torque);
	return output;
}