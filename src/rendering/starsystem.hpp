#pragma once

#include "mesh.hpp"
#include "camera.hpp"
#include "frame_buffer.hpp"
#include "render_buffer.hpp"

#include "core/star.hpp"
#include "core/planet.hpp"

#include "util/asset_manager.hpp"

namespace rendering
{

class StarSystemRenderer
{
private:
	const core::Star &m_star;
	FullMesh m_sphere_mesh;
	Mesh2D m_quad_mesh;
	SimpleMesh m_cube_mesh;

	FrameBuffer m_bloom_color_fbo;
	RenderBuffer m_bloom_color_rbo;
	Texture m_bloom_color_texture;
	
	FrameBuffer m_bloom_light_fbo;
	RenderBuffer m_bloom_light_rbo;
	Texture m_bloom_light_texture;

	FrameBuffer m_bloom_blur_fbo;
	Texture m_bloom_blur_texture;

	Cubemap m_star_texture;


public:
	StarSystemRenderer(const core::Star &star);

	void draw(Camera const&cam);
};

}