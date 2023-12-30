#pragma once

#include "mesh.hpp"
#include "camera.hpp"

#include "core/star.hpp"
#include "core/planet.hpp"

#include "util/asset_manager.hpp"

namespace rendering
{

class StarSystemRenderer
{
private:
	const core::Star &m_star;
	AssetManager &m_assets;
	FullMesh m_sphere_mesh;

public:
	StarSystemRenderer(AssetManager &assets, const core::Star &star);

	void draw(Camera const&cam);
};

}