//
//  shader.hpp
//  banana
//
//  Created by Marco Fattorel on 26/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#ifndef banana_shader_hpp
#define banana_shader_hpp

#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "mathematics.hpp"

class Shader
{
private:
	GLuint program;
	GLuint vertex, geometry, fragment;
	std::unordered_map<std::string, GLuint> uniforms;
public:
	Shader() : vertex(0), fragment(0)
	{
		program = glCreateProgram();
	}
	~Shader()
	{
		glDetachShader(program, vertex);
		if(geometry) glDetachShader(program, geometry);
		glDetachShader(program, fragment);
		glDeleteShader(vertex);
		if(geometry) glDeleteShader(geometry);
		glDeleteShader(fragment);

		glDeleteProgram(program);
	}

	void setVertex(const std::string& _filename)
	{
		std::string source(static_cast<std::stringstream const&>(std::stringstream() << std::ifstream(_filename).rdbuf()).str());
		vertex = compile_shader(source, GL_VERTEX_SHADER);
		if(!vertex)
		{
			std::cout << "failed to compile " << _filename << std::endl;
		}
	}
	void setGeometry(const std::string& _filename)
	{
		std::string source(static_cast<std::stringstream const&>(std::stringstream() << std::ifstream(_filename).rdbuf()).str());
		geometry = compile_shader(source, GL_GEOMETRY_SHADER);
		if(!geometry)
		{
			std::cout << "failed to compile " << _filename << std::endl;
		}
	}
	void setFragment(const std::string& _filename)
	{
		std::string source(static_cast<std::stringstream const&>(std::stringstream() << std::ifstream(_filename).rdbuf()).str());
		fragment = compile_shader(source, GL_FRAGMENT_SHADER);
		if(!fragment)
		{
			std::cout << "failed to compile " << _filename << std::endl;
		}
	}
	void link()
	{
		if(!vertex || !fragment)
		{
			std::cout << "missing shader stage" << std::endl;
			return;
		}
		glAttachShader(program, vertex);
		if(geometry) glAttachShader(program, geometry);
		glAttachShader(program, fragment);
		glLinkProgram(program);

		GLint status = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if(!status)
		{
			std::cout << "failed to link" << std::endl;
			GLchar log[256];
			GLsizei slen = 0;
			glGetProgramInfoLog(program, 256, &slen, log);
			std::cout << log << std::endl;
		}
		else
		{
			load_uniform();
		}
	}

	void bind()
	{
		if(!program)
		{
			std::cout << "incomplete program" << std::endl;
			return;
		}
		glUseProgram(program);
	}
	void unbind()
	{
		glUseProgram(0);
	}
	void load(const std::string& _name, const GLint _data)
	{
		glUniform1i(uniforms.at(_name), _data);
	}
	void load(const std::string& _name, const Mathematics::Matrix44& _data)
	{
		glUniformMatrix4fv(uniforms.at(_name), 1, GL_FALSE, _data.data());
	}
	GLint attrib(const std::string& _name)
	{
		return glGetAttribLocation(program, _name.c_str());
	}
private:
	GLuint compile_shader(const std::string& source, GLenum type) const
	{
		GLuint handle = glCreateShader(type);
		const GLchar* c_str = source.c_str();
		glShaderSource(handle, 1, &c_str, NULL);
		glCompileShader(handle);
		{
			GLchar log[256];
			GLsizei slen = 0;
			glGetShaderInfoLog(handle, 256, &slen, log);
			if(slen)
				std::cout << log << std::endl;
		}

		GLint status = 0;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
		return status? handle : 0;
	}
	void load_uniform()
	{
		GLint uniforms_size = 0;
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniforms_size);
		for(GLint i = 0; i < uniforms_size; ++i)
		{
			std::string name_uniform;
			{
				GLchar name[256];
				GLint array_size = 0, actual_length = 0;
				GLenum type = 0;
				glGetActiveUniform(program, i, 256, &actual_length, &array_size, &type, name);
				name_uniform = std::string{name, size_t(actual_length)};
			}
			GLuint location = glGetUniformLocation(program, name_uniform.c_str());
			if(location != GLuint(-1))
				uniforms[name_uniform] = location;
		}
	}
};

#endif