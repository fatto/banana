#ifndef banana_utils_hpp
#define banana_utils_hpp

#include <iostream>
#include <GLFW/glfw3.h>

struct utils
{
	static void testErrors()
	{
		GLenum err;
		while((err = glGetError()) != GL_NO_ERROR)
			std::cout << err << std::endl;
	}
};

#endif
