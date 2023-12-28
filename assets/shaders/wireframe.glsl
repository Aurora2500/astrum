//shader vertex
#version 330 core

uniform mat4 view;

layout(location = 0) in vec3 position;

void main()
{
	gl_Position = view * vec4(position, 1.0);
}

//shader fragment
#version 330 core

out vec4 color;

void main()
{
	color = vec4(0.0, 1.0, 1.0, 1.0);
}
