#include <iostream>
#include <algorithm>
#include <vector>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <glm/ext.hpp>

#include "game.hpp"
#include "windowing/window.hpp"

#include "rendering/camera.hpp"
#include "rendering/mesh.hpp"
#include "rendering/vertex.hpp"
#include "rendering/planet.hpp"
#include "rendering/star.hpp"

#include "util/stopwatch.hpp"

#include "core/star.hpp"
#include "core/planet.hpp"

Game::Game()
{
}

void Game::run()
{
	Window window("Astrum");

	SDL_Event event;

	Camera cam;
	rendering::Mesh mesh = rendering::create_sphere(90, 90);
	mesh.make_buffers();

	bool mouse_down = false;

	core::Star star(core::StarType::YellowDwarf, 420, 2.0);

	// std::vector<core::Planet> planets;
	// planets.emplace_back(core::PlanetType::Continental, 520);
	// planets.emplace_back(core::PlanetType::Desert, 620);

	auto star_shader = m_assets.get_shader("star");
	auto planet_shader = m_assets.get_shader("continental");
	// auto planet_shader2 = m_assets.get_shader("desert");

	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	unsigned int tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			window.width(),
			window.height(),
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_S,
			GL_CLAMP_TO_BORDER);
	glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_T,
			GL_CLAMP_TO_BORDER);
	// set the border color
	glTexParameterfv(
			GL_TEXTURE_2D,
			GL_TEXTURE_BORDER_COLOR,
			glm::value_ptr(glm::vec3(0.0f)));
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(
			GL_RENDERBUFFER,
			GL_DEPTH24_STENCIL8,
			window.width(),
			window.height());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(
			GL_FRAMEBUFFER,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_RENDERBUFFER,
			rbo);
	
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	auto screen_shader = m_assets.get_shader("redraw");

	rendering::Mesh screen_mesh;
	screen_mesh.vertices.push_back({glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)});
	screen_mesh.vertices.push_back({glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f)});
	screen_mesh.vertices.push_back({glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f)});
	screen_mesh.vertices.push_back({glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f)});

	screen_mesh.indices.push_back(0);
	screen_mesh.indices.push_back(1);
	screen_mesh.indices.push_back(2);

	screen_mesh.indices.push_back(0);
	screen_mesh.indices.push_back(2);
	screen_mesh.indices.push_back(3);

	screen_mesh.make_buffers();

	cam.position() = glm::vec3(0.0f, 0.0f, 10.0f);


	while (window.running())
	{
		while (SDL_PollEvent(&event))
		{
			window.handle_events(event);
			cam.update(event, mouse_down);
		}
		glm::mat4 view = cam.get_view_matrix(window.aspect());

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(star.size()));

		star_shader.use();
		star_shader.set_uniform("model", model);
		star_shader.set_uniform("view", view);
		mesh.draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));
		model = glm::scale(model, glm::vec3(0.5f));

		planet_shader.use();
		planet_shader.set_uniform("model", model);
		planet_shader.set_uniform("view", view);
		mesh.draw();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, tex);
		window.clear();
		screen_shader.use();
		screen_mesh.draw();

		window.update();
	}
}