#ifndef banana_state_hpp
#define banana_state_hpp

#include "mathematics.hpp"

#include <vector>
#include <functional>

namespace Physics
{
	struct State
	{
		Mathematics::Vector3 position;
		Mathematics::Vector3 momentum;
		Mathematics::Quaternion orientation;
		Mathematics::Vector3 angularMomentum;
		
		Mathematics::Vector3 velocity;
		Mathematics::Quaternion spin;
		Mathematics::Vector3 angularVelocity;
		Mathematics::Matrix44 bodyToWorld;
		Mathematics::Matrix44 worldToBody;
		
		std::vector<Mathematics::Vector3> positions;
		
		float size;
		float mass;
		float inverseMass;
		Mathematics::Matrix44 inertiaTensor;
		Mathematics::Matrix44 inverseInertiaTensor;
		
		std::function<void(const State&, float, Mathematics::Vector3&, Mathematics::Vector3&)> forces;
		
		void recalculate();
		
		static State interpolate(const State& a, const State& b, float alpha);
		static void integrate(State& state, float t, float dt);
		std::string to_string();
	};

	struct Derivative
	{
		Mathematics::Vector3 velocity;
		Mathematics::Vector3 force;
		Mathematics::Quaternion spin;
		Mathematics::Vector3 torque;
		
		static Derivative evaluate(const State& state, float t);
		static Derivative evaluate(State state, float t, float dt, const Derivative& derivative);
	};
}

#endif
