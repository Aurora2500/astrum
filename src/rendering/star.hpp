#pragma once

#include "mesh.hpp"
#include "core/star.hpp"

namespace rendering
{

class StarRenderer
{
private:
	core::Star &star;
	Mesh &mesh;

public:
	StarRenderer(core::Star &star, Mesh &mesh);
};

}
