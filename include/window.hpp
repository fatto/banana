#ifndef banana_window_hpp
#define banana_window_hpp

#include "entity.hpp"
#include <GLFW/glfw3.h>

class Window : public Entity<Window>
{
	GLFWwindow* window;
public:
	Window();
	Window(const Window& _win);
	~Window();
	bool shouldExit();
	// void on_update(float t, float dt) { }
	void on_draw();
};
#endif