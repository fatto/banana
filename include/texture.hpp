#ifndef banana_texture_hpp
#define banana_texture_hpp

#define STBI_HEADER_FILE_ONLY
#include "stb_image.c"

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class Texture2D : counter<Texture2D>
{
	GLuint handle;
	GLuint unit;
public:
	Texture2D(GLuint _unit) : unit(_unit)
	{
		glGenTextures(1, &handle);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, handle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	~Texture2D()
	{
		glDeleteTextures(1, &handle);
	}
	void setFromFile(const std::string& _filename)
	{
		int width, height, n;
		unsigned char* image = stbi_load(_filename.c_str(), &width, &height, &n, 4);
		if (!img)
			std::cout << "Failed to load " << _filename << " - " << stbi_failure_reason() << std::endl;
		
		setFromMemory(GLuint(width), GLuint(height), image);
		stbi_image_free(image);
	}
	void setFromMemory(const GLsizei width, const GLsizei height, GLvoid* data)
	{
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		unbind();
	}
	void bind()
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, handle);
	}
	void unbind()
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	GLuint getUnit()
	{
		return unit;
	}
};

class Texture2DArray : counter<Texture2DArray>
{
	GLuint handle;
	GLuint unit;
public:
	Texture2DArray(GLuint _unit) : unit(_unit)
	{
		glGenTextures(1, &handle);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D_ARRAY, handle);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}
	~Texture2DArray()
	{
		glDeleteTextures(1, &handle);
	}
	void setFromMemory(const GLsizei width, const GLsizei height, const GLsizei layer, GLvoid* data)
	{
		bind();
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, layer, 0, GL_RGBA, GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		unbind();
	}
	void bind()
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D_ARRAY, handle);
	}
	void unbind()
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}
	GLuint getUnit()
	{
		return unit;
	}
};

#endif