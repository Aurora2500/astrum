//shader vertex
#version 330 core

uniform mat4 view;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec3 v_normal;
out vec2 v_uv;

void main()
{
	gl_Position = view * vec4(position, 1.0);
	v_normal = normal;
	v_uv = uv;
}

//shader fragment
#version 330 core

in vec3 v_normal;
in vec2 v_uv;

out vec4 color;

const vec3 wavelengths = vec3(700, 530, 440);

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

vec4 atmosphere_tint(float incidence)
{
	float strength = smoothstep(-0.2, 2.0, incidence);
	//vec3 red = vec3(0.63, 0.28, 0.0);
	vec3 blue = vec3(0.25, 0.9, 0.9);
	vec3 red = vec3(0.9, 0.45, 0.3);

	float sunset = 1.0 - abs(incidence);


	return vec4(red, strength);
}


void main()
{
	float s = 10;
	float water = 0.55;
	vec2 p = v_uv * s;
	float n = fbm(p, s);
	vec3 col = n < water ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.7, 0.4) * n;
	vec3 dir = vec3(0.3, 0.4, -0.1);
	float intensity = dot(normalize(v_normal), normalize(dir));
	float min_intensity = 0.3;
	intensity = min_intensity + (1-min_intensity) * smoothstep(0.0, 1.0, intensity);
	color = vec4(intensity * col, 1.0);
}
