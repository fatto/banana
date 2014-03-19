#ifndef banana_material_hpp
#define banana_material_hpp

#include "shader.hpp"

template <class T>
struct Material
{
	void updateUniform()
	{
		static_cast<T*>(this)->uniform_update();
	}
	
	GLint attrib(const std::string& _name)
	{
		return shader.attrib(_name);
	}
	template <class D>
	void load(const std::string& _name, D data)
	{
		shader.load(_name, data);
	}
	void bind()
	{
		shader.bind();
	}
	void unbind()
	{
		shader.unbind();
	}

	static T& instance()
	{
		static T inst;
		return inst;
	}
protected:
	void uniform_update() { }
	Shader shader;
};

struct BaseMaterial : public Material<BaseMaterial>
{
	BaseMaterial()
	{
		shader.setVertex("shader/base.vert");
		shader.setFragment("shader/base.frag");
		shader.link();
	}
	// static BaseMaterial& instance()
	// {
	// 	static BaseMaterial inst;
	// 	return inst;
	// }
};
#endif
