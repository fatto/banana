#ifndef banana_event_hpp
#define banana_event_hpp

#include <GLFW/glfw3.h>

struct KeyEvent
{
	enum Status : int
	{
		RELEASE = GLFW_RELEASE,
		PRESS = GLFW_PRESS
	};
	enum KeyCode : int
	{
		SPACE = GLFW_KEY_SPACE,
		ESC = GLFW_KEY_ESCAPE,
		ALT = GLFW_KEY_LEFT_ALT
	};

	Status action;
	KeyCode key;
};

#endif