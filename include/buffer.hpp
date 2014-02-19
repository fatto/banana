#ifndef banana_buffer_hpp
#define banana_buffer_hpp

#include <GLFW/glfw3.h>

class Buffer
{
	GLenum type;
	GLenum usage;
	GLuint handle;
public:
	Buffer(GLenum _type, GLenum _usage);
	~Buffer();

	Buffer(const Buffer&) = delete;
	Buffer& operator=(const Buffer&) = delete;

	Buffer(Buffer&& b);
	Buffer& operator=(Buffer&& b);

	void bind();
	void unbind();
	void data(void* _data, size_t _size);
};

#endif