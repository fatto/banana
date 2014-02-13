//
//  geometry.hpp
//  banana
//
//  Created by Marco Fattorel on 26/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#ifndef banana_geometry_hpp
#define banana_geometry_hpp

#define offsetof_ptr(oggetto, campo) (void*)offsetof(oggetto, campo)

#include <cassert>
#include <iostream>
#include <array>
#include <GLFW/glfw3.h>

#include "buffer.hpp"
#include "mathematics.hpp"

struct vertex
{
	Mathematics::Vector3 pos;
	std::array<GLfloat, 3> norm;
	std::array<GLfloat, 3> colour;
	std::array<GLfloat, 2> text;
};
struct face
{
	std::array<GLuint, 3> triang;
};

template<GLuint rings, GLuint sectors>
struct Sphere
{
	std::array<vertex, rings * sectors> vertices;
	std::array<face, rings * sectors * 2> indices;
	
	Sphere(GLfloat radius)
	{
		using namespace Mathematics;
		GLfloat const R = 1.f/float(rings-1);
		GLfloat const S = 1.f/float(sectors-1);
		
		auto v = vertices.begin();
		auto i = indices.begin();
		for(GLuint r = 0; r < rings; ++r)
		{
			for(GLuint s = 0; s < sectors; ++s)
			{
				float const x = cos(tau * s * S) * sin((tau/2.f) * r * R);
				float const y = sin((-tau/4.f) + ((tau/2.f) * r * R));
				float const z = sin(tau * s * S) * sin((tau/2.f) * r * R);
				v->pos = {{ x * radius, y * radius, z * radius }};
				v->norm = {{ x, y, z }};
				v->text = {{ s * S, r * R }};
				++v;
				
				GLuint cur_row = r * sectors;
				GLuint next_row = (r+1) * sectors;
				i->triang = {{ cur_row + s, next_row + s, next_row + (s+1) }};
				++i;
				i->triang = {{ cur_row + s, next_row + (s+1), cur_row + (s+1) }};
				++i;
			}
		}
	}
};

struct Cube
{
	std::array<vertex, 8> vertices;
	std::array<face, 12> indices;
	Cube(float size)
	{
		vertices[0].pos = {-size, -size, size};
		vertices[1].pos = {size, -size, size};
		vertices[2].pos = {size, size, size};
		vertices[3].pos = {-size, size, size};
		vertices[4].pos = {-size, -size, -size};
		vertices[5].pos = {size, -size, -size};
		vertices[6].pos = {size, size, -size};
		vertices[7].pos = {-size, size, -size};
		
		vertices[0].colour = {0.f, 0.f, 1.f};
		vertices[1].colour = {1.f, 0.f, 1.f};
		vertices[2].colour = {1.f, 1.f, 1.f};
		vertices[3].colour = {0.f, 1.f, 1.f};
		vertices[4].colour = {0.f, 0.f, 0.f};
		vertices[5].colour = {1.f, 0.f, 0.f};
		vertices[6].colour = {1.f, 1.f, 0.f};
		vertices[7].colour = {0.f, 1.f, 0.f};
		
		indices[0] = {0, 1, 2};
		indices[1] = {2, 3, 0};
		indices[2] = {3, 2, 6};
		indices[3] = {6, 7, 3};
		indices[4] = {7, 6, 5};
		indices[5] = {5, 4, 7};
		indices[6] = {4, 5, 1};
		indices[7] = {1, 0, 4};
		indices[8] = {4, 0, 3};
		indices[9] = {3, 7, 4};
		indices[10] = {1, 5, 6};
		indices[11] = {6, 2, 1};
	}
};

class Geometry
{
	Buffer vert, ind;
	GLuint vao;
	GLsizei size;
	bool vert_init = false, ind_init = false, vao_init = false;
public:
	Geometry() : vert(GL_ARRAY_BUFFER, GL_STATIC_DRAW), ind(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW), vao(0), size(0)
	{
		glGenVertexArrays(1, &vao);
	}
	~Geometry()
	{
		glDeleteVertexArrays(1, &vao);
	}
	
	void bind()
	{
#ifdef DEBUG
		if(!vert_init || !ind_init || !vao_init || !size)
		{
			std::cout << "incomplete geometry status" << std::endl;
			return;
		}
#endif
		glBindVertexArray(vao);
	}
	void unbind()
	{
		glBindVertexArray(0);
	}
	void draw()
	{
		bind();
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
		unbind();
	}
	void drawLines()
	{
		bind();
		glDrawElements(GL_LINES, size, GL_UNSIGNED_INT, 0);
		unbind();
	}

	void vertices(void* _data, size_t _byte_size)
	{
		vert.data(_data, _byte_size);
		vert_init = true;
	}
	void indices(void* _data, GLsizei _byte_size)
	{
		size = _byte_size/sizeof(GLuint); // expect gluint array
		ind.data(_data, _byte_size);

		glBindVertexArray(vao);
		ind.bind(); // element array is part of vao state
		glBindVertexArray(0);
		ind.unbind();

		ind_init = true;
	}
	// _index index of vertex attribute, _size number of components(1..4), _stride total vertex size, _offset byte offset into buffer
	void addVertexAttrib(GLuint _index, GLint _size, GLuint _stride, const GLvoid* _offset)
	{
		vert.bind();
		glBindVertexArray(vao);
		glEnableVertexAttribArray(_index);
		glVertexAttribPointer(_index, _size, GL_FLOAT, GL_FALSE, _stride, _offset); // array buffer isn't part of vao state
		glBindVertexArray(0);
		vert.unbind();

		vao_init = true;
	}
};

// class GeometryFile
// {
// public:
// 	static Geometry loadFrom(const std::string& name)
// 	{
// 		std::vector<Collada::ColGeom> v;
		
// 		Collada::readGeometries(v, ("asset/" + name + ".dae").c_str());
		
// 		std::cout << "size " << (std::static_pointer_cast<std::vector<float>>(v[0].map["POSITION"_sid].data)->size()) << std::endl;
// 		std::cout << "size " << (std::static_pointer_cast<std::vector<float>>(v[0].map["NORMAL"_sid].data)->size()) << std::endl;
// 		Geometry g;
		
// 		return g;
// 	}
// };

#endif