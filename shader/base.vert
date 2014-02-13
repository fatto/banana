#version 330

in vec3 position;
in vec3 colour;

out vec3 v_colour;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(position, 1.0);
	v_colour = colour;
}