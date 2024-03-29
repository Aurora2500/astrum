#include "starsystem.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/ext.hpp>

#include <iostream>

#include "core/star.hpp"
#include "core/planet.hpp"

#include "util/locator.hpp"

#include "camera.hpp"

namespace rendering {

static glm::mat4 planet_model(const core::Planet &p)
{
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, p.pos());
	model = glm::scale(model, glm::vec3(p.size()));
	return model;
}

static glm::mat4 star_model(const core::Star &s)
{
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, s.pos());
	model = glm::scale(model, glm::vec3(s.size()));
	return model;
}

StarSystemRenderer::StarSystemRenderer(const core::Star &star)
	: m_star(star)
	, m_sphere_mesh(rendering::create_sphere(90, 90))
	, m_quad_mesh(create_quad())
	, m_cube_mesh(create_skybox())
	// , m_star_texture(TextureSampling::Linear, TextureWrapping::Wrap)
{
	auto &assets = Locator::assets();
	m_sphere_mesh.make_buffers();

	m_bloom_color_texture.store(1600, 900);
	m_bloom_color_rbo.store(1600, 900);
	m_bloom_color_fbo.attatch(m_bloom_color_texture);
	m_bloom_color_fbo.attatch(m_bloom_color_rbo);

	m_bloom_light_texture.store(1600, 900);
	m_bloom_light_rbo.store(1600, 900);
	m_bloom_light_fbo.attatch(m_bloom_light_texture);
	m_bloom_light_fbo.attatch(m_bloom_light_rbo);

	m_bloom_blur_texture.store(1600, 900);
	m_bloom_blur_fbo.attatch(m_bloom_blur_texture);

	m_star_texture = assets.get_cubemap("milkyway");
	m_text_atlas.load();
}

void StarSystemRenderer::draw(Camera const&cam)
{

	auto &assets = Locator::assets();

	auto screen = glm::uvec2(1600, 900);
	auto view = cam.get_view_matrix();
	auto cam_pos = cam.pos();


	m_bloom_light_fbo.bind_and_clear();
	auto &star_bloom_shader = assets.get_shader("star_bloom");
	auto &planet_bloom_shader = assets.get_shader("planet_bloom");

	star_bloom_shader.use();
	{
		auto model = star_model(m_star);
		star_bloom_shader.set_uniform("model", model);
		star_bloom_shader.set_uniform("view", view);
		m_sphere_mesh.draw();
	}
	
	planet_bloom_shader.use();
	{
		planet_bloom_shader.set_uniform("view", view);
		for (auto &p : m_star.planets())
		{
			auto model = planet_model(p);
			planet_bloom_shader.set_uniform("model", model);
			m_sphere_mesh.draw();
		}
	}

	m_bloom_color_fbo.bind_and_clear();

	glDepthFunc(GL_LEQUAL);
	auto &skybox = assets.get_shader("skybox");
	auto skyview = cam.get_untranslated_view_matrix();
	skybox.use();
	m_star_texture->bind(0);
	skybox.set_uniform("skybox", 0);
	skybox.set_uniform("view", skyview);
	m_cube_mesh.draw();
	glDepthFunc(GL_LESS);

	auto &star_shader = assets.get_shader("star");
	auto &planet_shader = assets.get_shader("rock_planet");

	star_shader.use();
	star_shader.set_uniform("view", view);
	{
		auto model = star_model(m_star);
		star_shader.set_uniform("model", model);
		m_sphere_mesh.draw();
	}


	planet_shader.use();
	{
		planet_shader.set_uniform("view", view);
		planet_shader.set_uniform("view_pos", cam_pos);
		for (auto &p : m_star.planets())
		{
			auto model = planet_model(p);
			auto light_dir = glm::normalize(m_star.pos() - p.pos());
			planet_shader.set_uniform("model", model);
			planet_shader.set_uniform("light", light_dir);
			m_sphere_mesh.draw();
		}
	}

	auto &blur = assets.get_shader("blur");

	m_bloom_blur_fbo.bind_and_clear();
	m_bloom_light_texture.bind(0);
	blur.use();
	blur.set_uniform("tex", 0);
	blur.set_uniform("sc_size", screen);
	blur.set_uniform("horizontal", true);

	m_quad_mesh.draw();

	m_bloom_light_fbo.bind_and_clear();
	m_bloom_blur_texture.bind(0);
	blur.use();
	blur.set_uniform("tex", 0);
	blur.set_uniform("sc_size", screen);
	blur.set_uniform("horizontal", false);
	m_quad_mesh.draw();

	FrameBuffer::bind_default();

	auto &add = assets.get_shader("add");
	add.use();
	m_bloom_color_texture.bind(0);
	m_bloom_light_texture.bind(1);
	add.set_uniform("tex", 0);
	add.set_uniform("light", 1);
	m_quad_mesh.draw();

	auto &text_shader = assets.get_shader("text");
	auto text_proj = glm::ortho(0.0f, (float)screen.x, 0.0f, (float)screen.y);

	text_shader.use();
	text_shader.set_uniform("projection", text_proj);

	m_text_atlas.texture().bind(0);
	text_shader.set_uniform("atlas", 0);

	glDepthFunc(GL_ALWAYS);
	text_shader.set_uniform("col", glm::vec3(1.0f, 1.0f, 1.0f));
	m_text_atlas.draw_text("Hello, world!", 200.0, 500.0, 1.0f);
	glDepthFunc(GL_LESS);
}
}