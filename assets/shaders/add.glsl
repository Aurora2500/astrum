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
uniform sampler2D light;

in vec2 uv;

out vec4 color;

void main()
{
	vec4 tex_color = texture(tex, uv);
	vec4 light_color = texture(light, uv);
	color = tex_color + light_color;
}
