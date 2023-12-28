#pragma once

#include "mesh.hpp"
#include "shaders.hpp"

#include "core/planet.hpp"
#include "util/asset_manager.hpp"

namespace rendering {

class PlanetRenderer
{
private:
	core::Planet &m_planet;

	Shader &m_shader;
	Mesh &m_mesh;

public:
	PlanetRenderer(core::Planet &planet, AssetManager &assets, Mesh &mesh);
};

}