#include <GL/glew.h>
#include <GL/gl.h>

#include "mesh.hpp"
#include "vertex.hpp"
namespace rendering
{

void Mesh::make_buffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(Vertex),
			vertices.data(),
			GL_STATIC_DRAW);

	Vertex::attrib();

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

void Mesh::draw() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

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
			int top_left = i * s_1 + (j + 1);
			int top_right = i * s_1 + j;
			int bottom_left = (i - 1) * s_1 + (j + 1);
			int bottom_right = (i - 1) * s_1 + j;

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

}