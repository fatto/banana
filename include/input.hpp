#ifndef banana_input_hpp
#define banana_input_hpp

#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>
class Input
{
	int joy;
	struct xbox_pad
	{
#ifdef __APPLE__
		enum
		{
			up = 0,
			down = 1,
			left = 2,
			right = 3,
			start = 4,
			back = 5,
			left_stick = 6,
			right_stick = 7,
			left_back = 8,
			right_back = 9,
			home = 10,
			a = 11,
			b = 12,
			x = 13,
			y = 14
		};
		enum
		{
			left_x = 0,
			left_y = 1,
			right_x = 2,
			right_y = 3,
			left_t = 4,
			right_t = 5
//			0 - left stick x (1=right, -1=left)
//			1 - left stick y (1=down, -1= up)
//			2 - right stick x(1=right, -1=left)
//			3 -  right stick y (1=down, -1= up)
//			4 - LT (-1=out, 1=in)
//			5 - RT (-1=out, 1=in)
		};
#elif __linux
		enum
		{
			a = 0,
			b = 1,
			x = 2,
			y = 3,
			left_back = 4,
			right_back = 5,
			back = 6,
			start = 7,
			home = 8,
			left_stick = 9,
			right_stick = 10
		};
		enum
		{
			left_x = 0,
			left_y = 1,
			left_t = 2,
			right_x = 3,
			right_y = 4,
			right_t = 5,
			dpad_x = 6,
			dpad_y = 7
//			0 - left stick x (1=right, -1=left)
//			1 - left stick y (1=down, -1= up)
//			2 - right stick x(1=right, -1=left)
//			3 -  right stick y (1=down, -1= up)
//			4 - LT (-1=out, 1=in)
//			5 - RT (-1=out, 1=in)
		};
#endif
	};
public:
	struct joystick
	{
		enum e
		{
			a = 0,
			b = 1,
			x = 2,
			y = 3,
			back = xbox_pad::back,
			start = 5
		};
	};
	Input(int i = GLFW_JOYSTICK_1) : joy(i)
	{
		assert(glfwJoystickPresent(joy));
	}
	bool buttonDown(joystick::e b)
	{
		int count = 0;
		const unsigned char* buttons = glfwGetJoystickButtons(joy, &count);
		assert(b < count);
		return bool(buttons[b]);
	}
	float axesValue(joystick::e a)
	{
		int count = 0;
		const float* axes = glfwGetJoystickAxes(joy, &count);
		assert(a < count);
		return axes[a];
	}
};


#endif
