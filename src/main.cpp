//
//  main.cpp
//  banana
//
//  Created by Marco Fattorel on 23/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#include "application.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <chrono>

static void error_callback(int error, const char* description)
{
	std::cout << error << " " << description << std::endl;
}

float time()
{
	using timer = std::chrono::high_resolution_clock;
	
//	static size_t start = 0;
	static timer::time_point start = timer::now();
	const float ratio = float(timer::period::num)/float(timer::period::den);
	
//	size_t counter = std::chrono::duration_cast<std::chrono::microseconds>(timer::now().time_since_epoch()).count();
	timer::time_point now = timer::now();
	
	return (now - start).count() * ratio;
}
int main(int argc, char*argv[])
{
	
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	
	if(!glfwInit())
		exit(EXIT_FAILURE);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow(900, 600, "simple", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	// glfwSwapInterval(0);
	
	// std::cout << glGetString(GL_RENDERER) << std::endl;
	// std::cout << glGetString(GL_VERSION) << std::endl;
	// std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	
	Application gl(window);
	
	const float dt = 0.01f;
	
	float t = 0.f;
	size_t frame = 0;
	float accumulator = 0.f;
	float current_time = 0.f;
	
	while (!glfwWindowShouldClose(window))
	{
		float new_time = time();
		
		float delta_time = new_time - current_time;
		if(delta_time <= 0.f)
			continue;
//		if(fmod(t, 1.f) < Mathematics::epsilon)
//			glfwSetWindowTitle(window, std::to_string(float(frame)/t).c_str());
		current_time = new_time;
		accumulator += delta_time;
		while (accumulator >= dt)
		{
			gl.update(t, dt);
			accumulator -= dt;
			t += dt;
		}
		
		gl.draw();
		++frame;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	
	exit(EXIT_SUCCESS);
}

