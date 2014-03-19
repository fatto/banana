#version 330

flat in vec3 v_normal;
in vec2 v_coord;

out vec4 colour;

const vec3 light_dir = vec3(-1, -1, -0.7);

void main()
{
	float factor = max(dot(v_normal, normalize(-light_dir)), 0.1);
	colour = vec4(factor, factor, factor, 1.0);
}