#include <GL/glew.h>
#include <GL/gl.h>

#include "mesh.hpp"
namespace rendering
{

void Vertex2D::attrib(unsigned int vao, unsigned int vbo)
{
	glEnableVertexArrayAttrib(vao, 0);
	glEnableVertexArrayAttrib(vao, 1);
	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribBinding(vao, 1, 0);
	glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, position));
	glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, tex_coords));
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex2D));
}

void SimpleVertex::attrib(unsigned int vao, unsigned int vbo)
{
	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(SimpleVertex, position));
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(SimpleVertex));
}

void UVNormalVertex::attrib(unsigned int vao, unsigned int vbo)
{
	glEnableVertexArrayAttrib(vao, 0);
	glEnableVertexArrayAttrib(vao, 1);
	glEnableVertexArrayAttrib(vao, 2);
	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribBinding(vao, 1, 0);
	glVertexArrayAttribBinding(vao, 2, 0);
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(UVNormalVertex, position));
	glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(UVNormalVertex, normal));
	glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(UVNormalVertex, tex_coords));
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(UVNormalVertex));
}

void FullVertex::attrib(unsigned int vao, unsigned int vbo)
{
	for (int i = 0; i <= 4; i++)
	{
		glEnableVertexArrayAttrib(vao, i);
		glVertexArrayAttribBinding(vao, i, 0);
	}
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(FullVertex, position));
	glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(FullVertex, normal));
	glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(FullVertex, tex_coords));
	glVertexArrayAttribFormat(vao, 3, 3, GL_FLOAT, GL_FALSE, offsetof(FullVertex, tangent));
	glVertexArrayAttribFormat(vao, 4, 3, GL_FLOAT, GL_FALSE, offsetof(FullVertex, bitangent));

	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(FullVertex));

}

template <typename V>
void Mesh<V>::make_buffers()
{
	glCreateVertexArrays(1, &VAO);

	glCreateBuffers(1, &VBO);
	glNamedBufferData(
			VBO,
			vertices.size() * sizeof(V),
			vertices.data(),
			GL_STATIC_DRAW);

	V::attrib(VAO, VBO);

	glCreateBuffers(1, &EBO);
	glNamedBufferData(
			EBO,
			indices.size() * sizeof(unsigned int),
			indices.data(),
			GL_STATIC_DRAW);
	glVertexArrayElementBuffer(VAO, EBO);
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

Mesh2D create_quad()
{
	Mesh2D mesh;
	mesh.vertices = {
		{{-1, -1}, {0, 0}},
		{{-1, 1}, {0, 1}},
		{{1, 1}, {1, 1}},
		{{1, -1}, {1, 0}}
	};
	mesh.indices = {
		0, 2, 1,
		0, 3, 2
	};
	mesh.make_buffers();
	return mesh;
}

SimpleMesh create_skybox()
{
	SimpleMesh mesh;
	mesh.vertices = {
		{{-1, -1, -1}}, // 0       3-----7   
		{{-1, -1,  1}}, // 1     / |   / | 
		{{-1,  1, -1}}, // 2   2---+-6   | 
		{{-1,  1,  1}}, // 3   |   | |   | 
		{{ 1, -1, -1}}, // 4   |   1-+---5 
		{{ 1, -1,  1}}, // 5   | /   | /   
		{{ 1,  1, -1}}, // 6   0-----4    
		{{ 1,  1,  1}}  // 7
	};
	mesh.indices = {
		0, 2, 1,
		1, 2, 3,
		3, 2, 6,
		3, 6, 7,
		7, 6, 4,
		7, 4, 5,
		5, 4, 0,
		5, 0, 1,
		5, 1, 3,
		5, 3, 7,
		2, 0, 4,
		2, 4, 6
	};
	mesh.make_buffers();
	return mesh;
}

template struct Mesh<Vertex2D>;
template struct Mesh<SimpleVertex>;
template struct Mesh<UVNormalVertex>;
template struct Mesh<FullVertex>;

}