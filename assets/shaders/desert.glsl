//shader vertex
#version 330 core

uniform mat4 view;
uniform mat4 model;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec3 v_normal;
out vec2 v_uv;

void main()
{
	gl_Position = view * model * vec4(position, 1.0);
	v_normal = normal;
	v_uv = uv;
}

//shader fragment
#version 330 core

in vec3 v_normal;
in vec2 v_uv;

out vec4 color;

const vec3 wavelengths = vec3(700, 530, 440);

float rand3(vec3 p) {
	return fract(sin(dot(p, vec3(12.9898, 78.233, 45.5432))) * 43758.5453);
}

float noise3(vec3 p)
{
	vec3 i = floor(p);
	vec3 fr = fract(p);

	float a000 = rand3(i);
	float a100 = rand3(i + vec3(1.0, 0.0, 0.0));
	float a010 = rand3(i + vec3(0.0, 1.0, 0.0));
	float a110 = rand3(i + vec3(1.0, 1.0, 0.0));
	float a001 = rand3(i + vec3(0.0, 0.0, 1.0));
	float a101 = rand3(i + vec3(1.0, 0.0, 1.0));
	float a011 = rand3(i + vec3(0.0, 1.0, 1.0));
	float a111 = rand3(i + vec3(1.0, 1.0, 1.0));

	vec3 u = fr * fr * (3.0 - 2.0 * fr);

	float x00 = mix(a000, a100, u.x);
	float x10 = mix(a010, a110, u.x);
	float x01 = mix(a001, a101, u.x);
	float x11 = mix(a011, a111, u.x);

	float y0 = mix(x00, x10, u.y);
	float y1 = mix(x01, x11, u.y);

	return mix(y0, y1, u.z);
}

float fbm3(vec3 p)
{
	const int OCTAVES = 10;
	// Initial values
	float value = 0.0;
	float amplitude = .5;
	// Loop of octaves
	for (int i = 0; i < OCTAVES; i++) {
		value += amplitude * noise3(p);
		p *= 2.;
		amplitude *= .5;
	}
	return value;
}

void main()
{
	float s = 3;
	vec3 p = v_normal * s;
	float n = fbm3(p);
	vec3 col = vec3(1.0, 0.8, 0.6) * n;
	vec3 dir = vec3(0.3, 0.4, -0.1);
	float intensity = dot(normalize(v_normal), normalize(dir));
	float min_intensity = 0.1;
	intensity = min_intensity + (1-min_intensity) * smoothstep(0.0, 1.0, intensity);
	color = vec4(intensity * col, 1.0);
}
