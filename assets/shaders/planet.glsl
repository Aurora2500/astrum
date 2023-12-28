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

float rand3(vec3 p) {
	return fract(sin(dot(p, vec3(12.9898, 78.233, 45.5432))) * 43758.5453);
}

float noise3(vec3 p)
{
	vec3 i = floor(p);
	vec3 fr = fract(p);

	float a = rand3(i);
	float b = rand3(i + vec3(1.0, 0.0, 0.0));
	float c = rand3(i + vec3(0.0, 1.0, 0.0));
	float d = rand3(i + vec3(1.0, 1.0, 0.0));
	float e = rand3(i + vec3(0.0, 0.0, 1.0));
	float f = rand3(i + vec3(1.0, 0.0, 1.0));
	float g = rand3(i + vec3(0.0, 1.0, 1.0));
	float h = rand3(i + vec3(1.0, 1.0, 1.0));

	vec3 u = fr * fr * (3.0 - 2.0 * fr);

	float x1 = mix(a, b, u.x);
	float x2 = mix(c, d, u.x);
	float x3 = mix(e, f, u.x);
	float x4 = mix(g, h, u.x);

	float y1 = mix(x1, x2, u.y);
	float y2 = mix(x3, x4, u.y);

	return mix(y1, y2, u.z);
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
	float water = 0.48;
	vec3 p = v_normal * s;
	float n = fbm3(p);
	float in_water = smoothstep(water, water + 0.005, n);
	vec3 terrain_col = vec3(1.0, 0.7, 0.4) * n;
	vec3 water_col = vec3(0.0, 0.0, 1.0) * n;
	vec3 col = mix(water_col, terrain_col, in_water);
	vec3 dir = vec3(0.3, 0.4, -0.1);
	float intensity = dot(normalize(v_normal), normalize(dir));
	float min_intensity = 0.3;
	intensity = min_intensity + (1-min_intensity) * smoothstep(0.0, 1.0, intensity);
	color = vec4(intensity * col, 1.0);
}
