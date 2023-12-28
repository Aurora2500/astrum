#include "planet.hpp"

#include "core/planet.hpp"

namespace rendering {

static const std::string type_to_shader(core::PlanetType type)
{
	switch (type)
	{
	case core::PlanetType::Continental:
		return "continental";
	case core::PlanetType::Desert:
		return "desert";
	}
}

PlanetRenderer::PlanetRenderer(core::Planet &planet, AssetManager &assets, Mesh &mesh) : m_planet(planet), m_shader(assets.get_shader(type_to_shader(planet.type()))), m_mesh(mesh)
{
}

}