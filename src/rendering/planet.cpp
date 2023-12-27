#include "planet.hpp"

Mesh create_sphere(int rings, int sectors)
{
	Mesh mesh;
	rings = std::max(rings, 3);
	sectors = std::max(sectors, 3);
	mesh.vertices.reserve(rings * (sectors + 1));
	for (int i = 0; i < rings; i++)
	{
		float const pitch = -M_PI_2 + M_PI * i / (rings - 1);
		for (int j = 0; j <= sectors; j++)
		{
			float const yaw = 2 * M_PI * j / sectors;
			glm::vec3 const p = {
					cos(yaw) * cos(pitch),
					sin(pitch),
					sin(yaw) * cos(pitch)};
			mesh.vertices.push_back({p, p, glm::vec2((float)j / sectors, (float)i / rings)});
		}
	}
	mesh.indices.reserve((rings - 1) * (sectors) * 6);
	for (int i = 1; i < rings; i++)
	{
		for (int j = 0; j < sectors; j++)
		{
			int s_1 = sectors + 1;
			int top_left = i * s_1 + j;
			int top_right = i * s_1 + (j + 1);
			int bottom_left = (i - 1) * s_1 + j;
			int bottom_right = (i - 1) * s_1 + (j + 1);

			mesh.indices.push_back(top_left);
			mesh.indices.push_back(top_right);
			mesh.indices.push_back(bottom_left);

			mesh.indices.push_back(top_right);
			mesh.indices.push_back(bottom_right);
			mesh.indices.push_back(bottom_left);
		}
	}
	return mesh;
}
