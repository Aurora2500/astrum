//shader vertex
#version 330 core

in vec3 pos;

out vec3 coords;

uniform mat4 view;

void main()
{
	vec4 p = view * vec4(pos, 1.0);
	gl_Position = vec4(p.x, p.y, p.w, p.w);
	coords = vec3(pos.x, pos.y, -pos.z);
}

//shader fragment
#version 330 core

in vec3 coords;

out vec4 color;

uniform samplerCube skybox;

void main()
{
	color = texture(skybox, coords);
}
