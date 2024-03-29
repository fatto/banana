#version 330

in vec3 v_normal;
in vec2 v_coord;

out vec4 colour;

// uniform sampler2D tex;
// uniform bool enable_texture;

const vec3 light_dir = vec3(-1, -1, -0.7);

void main()
{
	float factor = max(dot(v_normal, normalize(-light_dir)), 0.1);
	colour = vec4(factor, factor, factor, 1.0);
	// color = vec4(v_coord, 0, 1) * factor;
	// if(enable_texture)
	// 	color = texture(tex, v_coord) * factor;
}