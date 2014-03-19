#include "platform.hpp"

#include <GLFW/glfw3.h>

#include <cstdlib>

Platform::Platform()
{
	if(!glfwInit())
		exit(EXIT_FAILURE);
}
Platform::~Platform()
{
	glfwTerminate();
}