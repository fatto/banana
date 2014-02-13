//
//  utils.hpp
//  banana
//
//  Created by Marco Fattorel on 27/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

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
