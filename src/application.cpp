//
//  application.cpp
//  banana
//
//  Created by Marco Fattorel on 26/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#include "application.hpp"

Application::Application(GLFWwindow* _win) : win(_win), gui(900, 600) //image("assets/image.png")
{
//	image.setFromFile("assets/blur.png");
//	arr.setFromMemory(33, 33, 33, nullptr);
//	
//	utils::testErrors();
//	
//	flat.setVertex("shader/flat.vert");
//	flat.setFragment("shader/flat.frag");
//	flat.link();
//	smooth.setVertex("shader/smooth.vert");
//	smooth.setFragment("shader/smooth.frag");
//	smooth.link();
//	
//	utils::testErrors();
//	
//	Sphere<30,30> planet_data(1.5f);
//
//	vertex ship_vertices[6] = { { {0.f, .5f, 0.f}, {0.f, 1.f, 0.f}, {1.f, 0.f} },
//								{ {0.f, 0.f, .05f}, {0.f, 0.f, 1.f}, {1.f, 0.f} },
//								{ {.15f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {1.f, 0.f} }, 
//								{ {0.f, 0.f, -.05f}, {0.f, 0.f, -1.f}, {1.f, 0.f} },
//								{ {-.15f, 0.f, 0.f}, {-1.f, 0.f, 0.f}, {1.f, 0.f} },
//								{ {0.f, 0.f, 0.f}, {0.f, -1.f, 0.f}, {1.f, 0.f} } };
//	face ship_indices[8] = { {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4 ,1}, {5, 2, 1}, {5, 3, 2}, {5, 4, 3}, {5, 1, 4} };
//
//	assert(flat.attrib("position") == smooth.attrib("position"));
//	assert(flat.attrib("normal") == smooth.attrib("normal"));
//	assert(flat.attrib("coord") == smooth.attrib("coord"));
//
//	planet.vertices(planet_data.vertices.data(), planet_data.vertices.size()*sizeof(vertex));
//	planet.indices(planet_data.indices.data(), planet_data.indices.size()*sizeof(face));
//	planet.addVertexAttrib(flat.attrib("position"), 3, sizeof(vertex), offsetof_ptr(vertex, pos));
//	planet.addVertexAttrib(flat.attrib("normal"), 3, sizeof(vertex), offsetof_ptr(vertex, norm));
//	planet.addVertexAttrib(flat.attrib("coord"), 2, sizeof(vertex), offsetof_ptr(vertex, text));
//
//	ship.vertices(ship_vertices, 6*sizeof(vertex));
//	ship.indices(ship_indices, 6*sizeof(face));
//	ship.addVertexAttrib(flat.attrib("position"), 3, sizeof(vertex), offsetof_ptr(vertex, pos));
//	ship.addVertexAttrib(flat.attrib("normal"), 3, sizeof(vertex), offsetof_ptr(vertex, norm));
//	ship.addVertexAttrib(flat.attrib("coord"), 2, sizeof(vertex), offsetof_ptr(vertex, text));
//
//	utils::testErrors();
//	
//	model_planet = glm::mat4(1.f);
//	model_ship = glm::translate(glm::mat4(1.f), glm::vec3(2.f, 0.f, 0.f));
	glEnable(GL_DEPTH_TEST);
	float gray = 45.f / 255.f;
	glClearColor(gray, gray, gray, 1.f);
}

void Application::update(float t, float dt)
{
//	model_planet = glm::rotate(model_planet, dt, glm::vec3(0.f, 1.f, 0.f));
//	// model_ship = glm::rotate(mode_ship, dt, glm::vec3(0.f, 1.f, 0.f));
//	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.f,0.f,-6.f));
//	projection = glm::perspective(tau/8.f, 4.f/3.f, .1f, 100.f);
//	if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(win, GL_TRUE);
//	if(glfwGetKey(win, GLFW_KEY_F) == GLFW_PRESS)
//		flat_shading = true;
//	else
//		flat_shading = false;
//
//	if(glfwGetKey(win, GLFW_KEY_L) == GLFW_PRESS)
//		lines_draw = true;
//	else
//		lines_draw = false;
//
//	if(glfwGetKey(win, GLFW_KEY_T) == GLFW_PRESS)
//		texture_shading = true;
//	else
//		texture_shading = false;
	gui.update(t, dt);
	if(glfwGetKey(win, GLFW_KEY_F) == GLFW_PRESS)
		player1.editForce();
	player1.update(t, dt);
	
	if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GL_TRUE);

	// if(Input().buttonDown(Input::joystick::back))
	// 	glfwSetWindowShouldClose(win, GL_TRUE);
	// Input().axesValue(Input::joystick::a);
}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	player1.draw();

	gui.draw();

//	Shader& shading = flat_shading ? flat : smooth;
//	shading.bind();
//	shading.load("view", view);
//	shading.load("projection", projection);
//	shading.load("tex", image.getUnit());
//	shading.load("enable_texture", texture_shading);
//	image.bind();
//
//	shading.load("model", model_planet);
//	lines_draw ? planet.drawLines() : planet.draw();
//
//	shading.load("model", model_ship);
//	lines_draw ? ship.drawLines() : ship.draw();
//	
//	image.unbind();
//	shading.unbind();
}


//void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
//{
//	//Encode the image
//	unsigned error = lodepng::encode(filename, image, width, height);
//	
//	//if there's an error, display it
//	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
//}
