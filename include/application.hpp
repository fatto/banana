#ifndef banana_application_hpp
#define banana_application_hpp

#include <GLFW/glfw3.h>

//#include "geometry.hpp"
//#include "texture.hpp"
//#include "shader.hpp"

#include "input.hpp"
#include "mathematics.hpp"
#include "player.hpp"
#include "gui.hpp"

#include <array>
#include <cassert>

class Application
{
	GLFWwindow* win;
//	Geometry planet, ship;
//	Texture2D image;
//	Texture2DArray arr;
//	Shader flat, smooth;
//	glm::mat4 model_planet, model_ship, view, projection;
//	bool flat_shading = false;
//	bool lines_draw = false;
//	bool texture_shading = false;
	Player player1;
	Gui gui;
public:
	Application(GLFWwindow* _win);
	void update(float t, float dt);
	void draw();
};

#endif