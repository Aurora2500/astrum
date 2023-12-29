#pragma once

#include <glm/glm.hpp>

#include "mesh.hpp"
#include "core/star.hpp"
#include "camera.hpp"
#include "util/asset_manager.hpp"

namespace rendering
{

class StarRenderer
{
private:
	core::Star &m_star;
	Mesh &m_mesh;
	Shader &m_shader;

public:
	StarRenderer(core::Star &star, Mesh &mesh, AssetManager &manager);

	void draw(Camera &camera) const;
};

}
