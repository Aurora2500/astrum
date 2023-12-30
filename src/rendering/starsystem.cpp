#include "starsystem.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/ext.hpp>

#include "core/star.hpp"
#include "core/planet.hpp"

#include "camera.hpp"

namespace rendering {

static glm::mat4 planet_model(const core::Planet &p)
{
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, p.pos());
	model = glm::scale(model, glm::vec3(p.size()));
	return model;
}

StarSystemRenderer::StarSystemRenderer(AssetManager &assets, const core::Star &star)
	: m_star(star)
	, m_assets(assets)
	, m_sphere_mesh(rendering::create_sphere(90, 90))
{
	m_sphere_mesh.make_buffers();

}

void StarSystemRenderer::draw(Camera const&cam)
{
	auto &star_shader = m_assets.get_shader("star");
	auto &planet_shader = m_assets.get_shader("continental");
	auto view = cam.get_view_matrix();

	star_shader.use();
	{
		auto model = glm::mat4(1.0f);
		model = glm::translate(model, m_star.pos());
		model = glm::scale(model, glm::vec3(m_star.size()));
		star_shader.set_uniform("model", model);
		star_shader.set_uniform("view", view);
		m_sphere_mesh.draw();
	}

	auto cam_pos = cam.pos();

	{
		for (auto &p : m_star.planets())
		{
	planet_shader.use();
			auto model = planet_model(p);
			auto light_dir = glm::normalize(m_star.pos() - p.pos());
			planet_shader.set_uniform("model", model);
			planet_shader.set_uniform("view", view);
			planet_shader.set_uniform("light", light_dir);
			planet_shader.set_uniform("view_pos", cam_pos);
			m_sphere_mesh.draw();
		}
	}
}

}