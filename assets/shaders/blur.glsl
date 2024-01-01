//shader vertex
#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 uv_in;

out vec2 uv;

void main()
{
	gl_Position = vec4(pos, 0.0, 1.0);
	uv = uv_in;
}

//shader fragment
#version 330 core

uniform sampler2D tex;
uniform bool horizontal;
uniform uvec2 sc_size;

in vec2 uv;

out vec4 color;

const int kernel_radius = 48;

void main()
{
	vec2 texel = 1.0/sc_size;
	const int sum_total = (kernel_radius) * (kernel_radius + 2) + 1;
	vec3 blur_color = texture(tex, uv).rgb;
	if (horizontal)
	{
		for (int i = -kernel_radius; i <= kernel_radius; i++)
		{
			vec2 offset = vec2(texel.x * i, 0.0);
			if (uv.x + offset.x < 0.0 || uv.x + offset.x > 1.0)
			{
				continue;
			}
			int weight = kernel_radius + 1 - abs(i);
			blur_color += texture(tex, uv + offset).rgb * float(weight);
		}
	}
	else
	{
		for (int i = -kernel_radius; i <= kernel_radius; i++)
		{
			vec2 offset = vec2(0.0, texel.y * i);
			if (uv.y + offset.y < 0.0 || uv.y + offset.y > 1.0)
			{
				continue;
			}
			int weight = kernel_radius + 1 - abs(i);
			blur_color += texture(tex, uv + offset).rgb * float(weight);
		}
	}
	blur_color /= sum_total;
	color = vec4(blur_color, 1.0);
}
