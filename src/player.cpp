//
//  player.cpp
//  banana
//
//  Created by Marco Fattorel on 26/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#include "player.hpp"
#include "mathematics.hpp"

#include <algorithm>
#include <GLFW/glfw3.h>

using namespace Mathematics;
using namespace Physics;


Player::Player() : mate(BaseMaterial::instance())
{
	Cube cub(0.5f);
	
	current.size = 1.f;
	current.mass = 1.f;
	current.inverseMass = 1.0f / current.mass;
	current.position = Vector3(0.f, 1.f, 0.f);
	current.momentum = Vector3(0.f, 0.f, 0.f);
	current.orientation.identity(); //= Quaternion(tau/4.f, Vector3(1.f, 0.f, 1.f));
	current.angularMomentum = Vector3(0.f, 0.f, 0.f);
	current.inertiaTensor = Matrix44().scale(current.mass * current.size * current.size * 1.0f / 6.0f);
	current.inverseInertiaTensor = current.inertiaTensor.inverse();
	std::transform(cub.vertices.begin(), cub.vertices.end(), std::back_inserter(current.positions),  [](const vertex& vert){ return vert.pos; });
	current.forces = std::bind(&Player::applyForce, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	current.recalculate();
	previous = current;
//	std::cout << current.to_string() << std::endl;
	
	utils::testErrors();
	
	geom.vertices(cub.vertices.data(), cub.vertices.size() * sizeof(vertex));
	geom.indices(cub.indices.data(), cub.indices.size() * sizeof(face));
	geom.addVertexAttrib(mate.get().attrib("position"), 3, sizeof(vertex), offsetof_ptr(vertex, pos));
	geom.addVertexAttrib(mate.get().attrib("colour"), 3, sizeof(vertex), offsetof_ptr(vertex, pos));
	
	utils::testErrors();
}

void Player::on_update(float t, float dt)
{
	elapsed += dt;
	previous = current;
	State::integrate(current, t, dt);
//	std::cout << std::boolalpha <<  << std::endl;
}


void Player::on_draw()
{
	State state = State::interpolate(previous, current, 1.f);
//	float angle; Vector3 axis;
	Matrix44 model = Matrix44().translate(state.position) * state.orientation.matrix();
	mate.get().bind();
	mate.get().updateUniform();
	Matrix44 pers; pers.perspective(tau/6.f, 1.5f, .1f, 100.f); // pers.orthographic(-2.f, 2.f, -2.f, 2.f, -2.f, 2.f);
	Matrix44 view; view.lookat(Vector3(0.f, 4.f, 10.f), Vector3(0.f, 0.f, 0.f), Vector3().up());
//	Matrix44 trans; trans.identity(); // trans.translate(Vector3(1.f, 1.f, 1.f));
//	Matrix44 rot; rot.rotate(elapsed/2.f, Vector3(1.f, 1.f, 0.f));
//	Quaternion qua(elapsed/2.f, Vector3(1.f, 0.f, 0.f).normalize());
	Matrix44 mvp = pers * view * model; //* trans * qua.matrix(); //rot;
	mate.get().load("mvp", mvp);
	geom.draw();
	mate.get().unbind();
}

void Player::applyForce(const State& state, float t, Vector3& force, Vector3& torque)
{
	force.zero();
	torque.zero();
	force.vec.y = -9.81f;
	torque.vec.z = torque_rotation;
	torque = state.orientation.matrix() * torque;
	torque_rotation = 0.f;
}
void Player::editForce()
{
	torque_rotation = 200.f;
}