#version 330

in vec3 position;
in vec3 normal;
in vec2 coord;

flat out vec3 v_normal;
out vec2 v_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	v_normal = mat3(view * model) * normal;
	v_coord = vec2(coord.x, 1.0 - coord.y);
}