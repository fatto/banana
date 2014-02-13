//
//  player.hpp
//  banana
//
//  Created by Marco Fattorel on 26/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#ifndef banana_player_hpp
#define banana_player_hpp

#include <functional>

#include "utils.hpp"
#include "entity.hpp"
#include "material.hpp"
#include "geometry.hpp"
#include "mathematics.hpp"
#include "physics.hpp"
#include "input.hpp"

class Player : public Entity<Player>
{
	Input input;
	Geometry geom;
	std::reference_wrapper<BaseMaterial> mate;
	float elapsed = 0.f;
	Physics::State previous;
	Physics::State current;
	float torque_rotation = 0.f;
public:
	Player();
	void on_draw();
	void on_update(float t, float dt);
	void applyForce(const Physics::State& state, float t, Mathematics::Vector3& force, Mathematics::Vector3& torque);
	void editForce();
};

#endif
