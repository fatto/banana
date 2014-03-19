//
//  main.cpp
//  banana
//
//  Created by Marco Fattorel on 23/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#include "application.hpp"

// #include <GLFW/glfw3.h>
#include "window.hpp"
#include "gui.hpp"

#include <iostream>
#include <string>
#include <chrono>

// static void error_callback(int error, const char* description)
// {
// 	std::cout << error << " " << description << std::endl;
// }

float time()
{
	using timer = std::chrono::high_resolution_clock;
	
	static timer::time_point start = timer::now();
	const float ratio = float(timer::period::num)/float(timer::period::den);
	
	timer::time_point now = timer::now();
	
	return (now - start).count() * ratio;
}
int main(int argc, char*argv[])
{
	// std::cout << glGetString(GL_VERSION) << std::endl;
	// std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	
	Application gl;
	
	
	const float dt = 0.01f;
	
	float t = 0.f;
	float accumulator = 0.f;
	float current_time = 0.f;
	
	// while (!gl.shouldExit())
	while (!gl.shouldExit())
	{
		float new_time = time();
		
		float delta_time = new_time - current_time;
		if(delta_time <= 0.f)
			continue;
		current_time = new_time;
		accumulator += delta_time;
		while (accumulator >= dt)
		{
			gl.update(t, dt);
			accumulator -= dt;
			t += dt;
		}

		gl.draw();
		// g.draw(); // ????????
		// w.draw();
	}
	
	return EXIT_SUCCESS;
}

