#include "geometry.hpp"

Geometry::Geometry() : vert(GL_ARRAY_BUFFER, GL_STATIC_DRAW), ind(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW), vao(0), size(0)
{
	glGenVertexArrays(1, &vao);
}
Geometry::~Geometry()
{
	glDeleteVertexArrays(1, &vao);
}

void Geometry::bind()
{
	glBindVertexArray(vao);
}
void Geometry::unbind()
{
	glBindVertexArray(0);
}
void Geometry::draw()
{
	bind();
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	unbind();
}
void Geometry::drawLines()
{
	bind();
	glDrawElements(GL_LINES, size, GL_UNSIGNED_INT, 0);
	unbind();
}

void Geometry::vertices(void* _data, size_t _byte_size)
{
	vert.data(_data, _byte_size);
}
void Geometry::indices(void* _data, GLsizei _byte_size)
{
	size = _byte_size/sizeof(GLuint); // expect gluint array
	ind.data(_data, _byte_size);

	glBindVertexArray(vao);
	ind.bind(); // element array is part of vao state
	glBindVertexArray(0);
	ind.unbind();
}
// _index index of vertex attribute, _size number of components(1..4), _stride total vertex size, _offset byte offset into buffer
void Geometry::addVertexAttrib(GLuint _index, GLint _size, GLuint _stride, const GLvoid* _offset)
{
	vert.bind();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(_index);
	glVertexAttribPointer(_index, _size, GL_FLOAT, GL_FALSE, _stride, _offset); // array buffer isn't part of vao state
	glBindVertexArray(0);
	vert.unbind();
}