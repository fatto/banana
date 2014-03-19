//
//  application.cpp
//  banana
//
//  Created by Marco Fattorel on 26/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#include "application.hpp"
#include "window.hpp"
#include "input.hpp"


Application::Application() : g(900, 600), plane_obj("assets/plane.obj")// : gui(900, 600) //image("assets/image.png")
{
	// auto hand = Input::keyPress_signal.connect(std::bind(&Application::on_keyPress, this, std::placeholders::_1));
	// Input::keyPress_signal.connect([this](KeyEvent::KeyCode& key){on_keyPress(key);});
	

	shader.setVertex("shader/flat.vert");
	shader.setFragment("shader/flat.frag");
	shader.link();

	plane.vertices(plane_obj.vertices.data(), plane_obj.vertices.size()*sizeof(vertex));
	plane.indices(plane_obj.indices.data(), plane_obj.indices.size()*sizeof(face));
	plane.addVertexAttrib(shader.attrib("position"), 3, sizeof(vertex), offsetof_ptr(vertex, pos));
	plane.addVertexAttrib(shader.attrib("normal"), 3, sizeof(vertex), offsetof_ptr(vertex, norm));

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
}
Application::~Application()
{
	
}

void Application::update(float t, float dt)
{
	Input::dispatch();
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
	// gui.update(t, dt);
	// if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	// 	player1.editForce();
	// player1.update(t, dt);
	
	// if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	// 	glfwSetWindowShouldClose(window, GL_TRUE);

	// if(Input().buttonDown(Input::joystick::back))
	// 	glfwSetWindowShouldClose(win, GL_TRUE);
	// Input().axesValue(Input::joystick::a);
}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// player1.draw();

	// gui.draw();

	using namespace Mathematics;
	shader.bind();
	shader.load("model", Matrix44().identity());
	shader.load("view", Matrix44().translate({0.f, -2.f, -2.f}));
	shader.load("projection", Matrix44().perspective(tau/4.f, 900/600, 0.1f, 100.f));

	plane.draw();

	shader.unbind();

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
	// Window::drawEach();
	g.draw();
	win.draw();
	glfwPollEvents();
}


//void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
//{
//	//Encode the image
//	unsigned error = lodepng::encode(filename, image, width, height);
//	
//	//if there's an error, display it
//	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
//}
bool Application::shouldExit()
{
	bool should_exit = false;
	// Window::for_each(
	// 	[&](Window& w)
	// 	{
	// 		should_exit = should_exit || w.shouldExit();
	// 	}
	// );
	return should_exit || stop;
}