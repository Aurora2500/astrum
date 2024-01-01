//shader vertex
#version 330 core

uniform mat4 view;
uniform mat4 model;

layout(location = 0) in vec3 position;

void main()
{
	gl_Position = view * model * vec4(position, 1.0);
}

//shader fragment
#version 330 core

out vec4 color;

void main()
{
	color = vec4(vec3(0.0), 1.0);
}
