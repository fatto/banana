#ifndef banana_shader_hpp
#define banana_shader_hpp

#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>

#include "mathematics.hpp"

class Shader
{
private:
	GLuint program;
	GLuint vertex, geometry, fragment;
	std::unordered_map<std::string, GLuint> uniforms;
public:
	Shader();
	~Shader();

	void setVertex(const std::string& _filename);
	void setGeometry(const std::string& _filename);
	void setFragment(const std::string& _filename);
	void link();

	void bind();
	void unbind();
	void load(const std::string& _name, const GLint _data);
	void load(const std::string& _name, const Mathematics::Matrix44& _data);
	GLint attrib(const std::string& _name);
	GLint block(const std::string& _name);
private:
	GLuint compile_shader(const std::string& source, GLenum type) const;
	void load_uniform();
};

#endif