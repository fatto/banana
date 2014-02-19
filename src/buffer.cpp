#include "buffer.hpp"

Buffer::Buffer(GLenum _type, GLenum _usage) : type(_type), usage(_usage)
{
	glGenBuffers(1, &handle);
}
Buffer::~Buffer()
{
	glDeleteBuffers(1, &handle);
}

Buffer::Buffer(Buffer&& b) : type(b.type), usage(b.usage), handle(b.handle)
{
	b.handle = 0;
}
Buffer& Buffer::operator=(Buffer&& b)
{
	assert(this != &b);
	type = b.type;
	usage = b.usage;
	handle = b.handle;
	b.handle = 0;
	return *this;
}

void Buffer::bind()
{
	glBindBuffer(type, handle);
}
void Buffer::unbind()
{
	glBindBuffer(type, 0);
}
void Buffer::data(void* _data, size_t _size)
{
	bind();
	glBufferData(type, _size, _data, usage);
	unbind();
}