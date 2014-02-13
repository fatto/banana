#version 330

flat in vec3 v_normal;
in vec2 v_coord;

out vec4 color;

uniform sampler2D tex;
uniform bool enable_texture;

const vec3 light_dir = vec3(-1, -1, -0.7);

void main()
{
	float factor = max(dot(v_normal, normalize(-light_dir)), 0.1);
	color = vec4(v_coord, 0, 1) * factor;
	if(enable_texture)
		color = texture(tex, v_coord) * factor;
}