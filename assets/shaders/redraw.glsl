//shader vertex
#version 330 core

layout(location = 0) in vec2 pos;

out vec2 uv;

void main()
{
	gl_Position = vec4(pos, 0.0, 1.0);
	uv = pos * 0.5 + 0.5;
}

//shader fragment
#version 330 core

uniform sampler2D tex;

in vec2 uv;

out vec4 color;

void main()
{
	color =  texture(tex, uv);
}
