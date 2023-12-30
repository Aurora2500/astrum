#include <GL/glew.h>
#include <GL/gl.h>

#include "mesh.hpp"
namespace rendering
{

void Vertex2D::attrib()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, tex_coords));
}

void SimpleVertex::attrib()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void *)offsetof(SimpleVertex, position));
}

void UVNormalVertex::attrib()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(UVNormalVertex), (void *)offsetof(UVNormalVertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(UVNormalVertex), (void *)offsetof(UVNormalVertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UVNormalVertex), (void *)offsetof(UVNormalVertex, tex_coords));
}

void FullVertex::attrib()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FullVertex), (void *)offsetof(FullVertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FullVertex), (void *)offsetof(FullVertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FullVertex), (void *)offsetof(FullVertex, tex_coords));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(FullVertex), (void *)offsetof(FullVertex, tangent));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(FullVertex), (void *)offsetof(FullVertex, bitangent));
}

template <typename V>
void Mesh<V>::make_buffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(V),
			vertices.data(),
			GL_STATIC_DRAW);

	V::attrib();

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(unsigned int),
			indices.data(),
			GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

template <typename V>
void Mesh<V>::draw() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

FullMesh create_sphere(int rings, int sectors)
{
	FullMesh mesh;
	rings = std::max(rings, 3);
	sectors = std::max(sectors, 3);
	mesh.vertices.reserve(rings * (sectors + 1));
	for (int i = 0; i < rings; i++)
	{
		float const pitch = -M_PI_2 + M_PI * i / (rings - 1);
		for (int j = 0; j <= sectors; j++)
		{
			float const yaw = - 2 * M_PI * j / sectors;
			glm::vec3 const p = {
					cos(yaw) * cos(pitch),
					sin(pitch),
					sin(yaw) * cos(pitch)};
			auto n = p;
			glm::vec2 uv = {(float)j / sectors, (float)i / rings};
			glm::vec3 bitangent = {
					-sin(yaw),
					0,
					cos(yaw)
			};
			auto tangent = glm::cross(n, bitangent);
			mesh.vertices.push_back({p, n, uv, tangent, bitangent});
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
			mesh.indices.push_back(bottom_left);
			mesh.indices.push_back(top_right);

			mesh.indices.push_back(top_right);
			mesh.indices.push_back(bottom_left);
			mesh.indices.push_back(bottom_right);
		}
	}
	return mesh;
}

template struct Mesh<Vertex2D>;
template struct Mesh<SimpleVertex>;
template struct Mesh<UVNormalVertex>;
template struct Mesh<FullVertex>;

}