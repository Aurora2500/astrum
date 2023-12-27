//shader vertex
#version 330 core

uniform mat4 view;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec3 o_normal;
out vec2 o_uv;

void main()
{
	gl_Position = view * vec4(position, 1.0);
	o_normal = normal;
	o_uv = uv;
}

//shader fragment
#version 330 core

in vec3 o_normal;
in vec2 o_uv;

out vec4 color;

float random (vec2 st) {
	return fract(sin(dot( st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}


// Based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (vec2 st, float wrap) {
	vec2 i = floor(st);
	vec2 f = fract(st);

	vec2 ai = vec2(mod(i.x, wrap), i.y);
	vec2 bi = vec2(mod(i.x + 1.0, wrap), i.y);
	vec2 ci = vec2(mod(i.x, wrap), i.y + 1.0);
	vec2 di = vec2(mod(i.x + 1.0, wrap), i.y + 1.0);
	float a = random(ai);
	float b = random(bi);
	float c = random(ci);
	float d = random(di);
	
	vec2 u = f * f * (3.0 - 2.0 * f);

	return mix(a, b, u.x) +
		(c - a)* u.y * (1.0 - u.x) +
		(d - b) * u.x * u.y;
}


float fbm (in vec2 p, in float wrap) {
	const int OCTAVES = 100;
	// Initial values
	float value = 0.0;
	float amplitude = .5;
	// Loop of octaves
	for (int i = 0; i < OCTAVES; i++) {
		value += amplitude * noise(p, wrap);
		p *= 2.;
		amplitude *= .5;
	}
	return value;
}


void main()
{
	vec2 p = o_uv * 10.0;
	float n = fbm(p, 10.0);
	vec3 col = n < 0.5 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.7, 0.4) * n;
	vec3 dir = vec3(0.3, 0.4, -0.1);
	float intensity = dot(normalize(o_normal), normalize(dir));
	color = vec4(intensity * col, 1.0);
}
