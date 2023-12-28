#pragma once

#include <vector>

#include "vertex.hpp"

namespace rendering
{

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;

	void make_buffers();

	void draw() const;
};

Mesh create_sphere(int rings, int sectors);

}