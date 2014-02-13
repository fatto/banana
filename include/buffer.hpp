//
//  buffer.hpp
//  banana
//
//  Created by Marco Fattorel on 26/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#ifndef banana_buffer_hpp
#define banana_buffer_hpp

#include <GLFW/glfw3.h>

class Buffer
{
	GLenum type;
	GLenum usage;
	GLuint handle;
public:
	Buffer(GLenum _type, GLenum _usage) : type(_type), usage(_usage) { glGenBuffers(1, &handle); }
	~Buffer() { glDeleteBuffers(1, &handle); }

	Buffer(const Buffer&) = delete;
	Buffer& operator=(const Buffer&) = delete;

	Buffer(Buffer&& b) : type(b.type), usage(b.usage), handle(b.handle)
	{
		b.handle = 0;
	}
	Buffer& operator=(Buffer&& b)
	{
		assert(this != &b);
		type = b.type;
		usage = b.usage;
		handle = b.handle;
		b.handle = 0;
		return *this;
	}

	void bind() { glBindBuffer(type, handle); }
	void unbind() { glBindBuffer(type, 0); }
	void data(void* _data, size_t _size)
	{
		bind();
		glBufferData(type, _size, _data, usage);
		unbind();
	}
};

#endif