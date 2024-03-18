//shader vertex
#version 330 core

uniform mat4 projection;

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 coords;

out vec2 uv;

void main()
{
	gl_Position = projection * vec4(pos, 0.0, 1.0);
	uv = coords;
}

//shader fragment
#version 330 core

uniform sampler2D atlas;
uniform vec3 col;

in vec2 uv;

out vec4 color;

void main()
{
	float shape = texture(atlas, uv).r;
	color = vec4(col, shape);
}
