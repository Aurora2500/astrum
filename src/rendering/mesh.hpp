#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace rendering
{

struct Vertex2D
{
	glm::vec2 position;
	glm::vec2 tex_coords;

	static void attrib();
};

struct SimpleVertex
{
	glm::vec3 position;

	static void attrib();
};

struct UVNormalVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;

	static void attrib();
};

struct FullVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	static void attrib();
};

template <typename V>
struct Mesh
{
	std::vector<V> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;

	void make_buffers();

	void draw() const;
};

using Mesh2D = Mesh<Vertex2D>;
using SimpleMesh = Mesh<SimpleVertex>;
using UVNormalMesh = Mesh<UVNormalVertex>;
using FullMesh = Mesh<FullVertex>;

FullMesh create_sphere(int rings, int sectors);
}