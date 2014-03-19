#ifndef banana_application_hpp
#define banana_application_hpp

#include <GLFW/glfw3.h>

//#include "geometry.hpp"
//#include "texture.hpp"
//#include "shader.hpp"

#include "platform.hpp"
#include "window.hpp"
#include "input.hpp"
#include "mathematics.hpp"
#include "player.hpp"
#include "gui.hpp"
#include "wavefront.hpp"

#include <array>
#include <cassert>

class Application
{
//	Geometry planet, ship;
//	Texture2D image;
//	Texture2DArray arr;
//	Shader flat, smooth;
//	glm::mat4 model_planet, model_ship, view, projection;
//	bool flat_shading = false;
//	bool lines_draw = false;
//	bool texture_shading = false;
	// Player player1;
	// Gui gui;
	Platform plat;
	Window win;
	Gui g;
	Shader shader;
	Geometry plane;
	Wavefront plane_obj;
public:
	Application();
	~Application();
	void update(float t, float dt);
	void draw();
	bool shouldExit();

	void on_keyPress(KeyEvent::KeyCode key)
	{
		if(key == KeyEvent::ESC)
			stop = true;
		if(key == KeyEvent::ALT)
			std::cout << "deerp" << std::endl;
	}
private:
	bool stop = false;
};

#endif