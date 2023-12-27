//shader vertex
#version 330

layout (location = 0) in vec4 pos;

void main()
{
gl_Position = pos;
}

//shader fragment
#version 330 core

in vec4 gl_FragCoord;
out vec4 col;

void main()
{
col = vec4(gl_FragCoord.xy / 1000.0, 0.0, 1.0);
}