//shader vertex
#version 330 core

uniform mat4 view;
uniform mat4 model;

uniform vec3 light;
uniform vec3 view_pos;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec2 v_uv;
out vec3 v_normal;
out vec3 v_light;
out vec3 v_view_dir;
out vec3 v_world_view_dir;
out vec3 v_world_light;

void main()
{
	vec4 world_pos = model * vec4(position, 1.0);
	gl_Position = view * world_pos;
	v_uv = uv;

	v_normal = normal;
	mat3 tbn = mat3(tangent, bitangent, normal);
	tbn = transpose(tbn);
	v_light = tbn * (light);
	vec3 view_dir = normalize(view_pos - world_pos.xyz);
	v_view_dir = tbn * (view_dir);

	v_world_view_dir = view_dir;
	v_world_light = light;
}

//shader fragment
#version 330 core

uniform vec3 light;

in vec3 v_normal;
in vec2 v_uv;
in vec3 v_light;
in vec3 v_view_dir;

in vec3 v_world_view_dir;
in vec3 v_world_light;

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
	vec3 norm = vec3(0.0, 0.0, 1.0);
	float s = 3;
	float water = 0.6;
	vec3 p = v_normal * s;
	float n = fbm3(p);

 float cloud_s = 2.5;
	vec3 cloud_p = v_normal * cloud_s + 420;

	float cloud_n = fbm3(cloud_p);
	float in_cloud = smoothstep(0.4, 0.8, cloud_n);

	float in_water = 1 - smoothstep(water, water + 0.005, n);
	vec3 terrain_col = vec3(1.0, 0.7, 0.4) * n;
	vec3 water_col = vec3(0.0, 0.0, 1.0) * mix(0.3, 1.0, n);
	vec3 col = mix(terrain_col, water_col, in_water);
	col = mix(col, vec3(1.0, 1.0, 1.0), in_cloud);

	float cloud_elevation;
	float cloud_turn_u = asin(v_light.x);
	float cloud_turn_v = asin(v_light.y);

	mat3 cloud_rot = mat3(
		vec3(cos(cloud_turn_u), 0, sin(cloud_turn_u)),
		vec3(0, 1, 0),
		vec3(-sin(cloud_turn_u), 0, cos(cloud_turn_u))
	);

	cloud_rot = mat3(
		vec3(1, 0, 0),
		vec3(0, cos(cloud_turn_v), -sin(cloud_turn_v)),
		vec3(0, sin(cloud_turn_v), cos(cloud_turn_v))
	) * cloud_rot;

	vec3 cloud_dir = cloud_rot * v_normal;

	float cloud_shadow_n = fbm3(cloud_dir * cloud_s + 420);

	float cloud_shadow = smoothstep(0.4, 0.8, cloud_shadow_n);

	float ambient = 0.2;

	float diffuse = dot(normalize(v_light), norm);
	diffuse = max(diffuse, 0.0);

	vec3 half_dir = normalize(v_light + v_view_dir);
	float spec = pow(max(dot(norm, half_dir), 0.0), 32.0);

	float intensity = ambient + (diffuse + (spec * in_water * (1- in_cloud)));
	color = vec4(col * intensity, 1.0);
}
