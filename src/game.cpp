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

#include "rendering/frame_buffer.hpp"
#include "rendering/texture.hpp"
#include "rendering/render_buffer.hpp"

#include "util/stopwatch.hpp"

#include "core/star.hpp"
#include "core/planet.hpp"

Game::Game()
{
}

void Game::run()
{
	using namespace rendering;

	Window window("Astrum");

	SDL_Event event;

	Camera cam;
	Mesh mesh = rendering::create_sphere(90, 90);
	mesh.make_buffers();

	bool mouse_down = false;

	core::Star star(core::StarType::YellowDwarf, 420, 2.0);

	auto star_shader = m_assets.get_shader("star");
	auto planet_shader = m_assets.get_shader("continental");
	// auto planet_shader2 = m_assets.get_shader("desert");

	FrameBuffer frame_buffer;
	Texture texture;
	texture.store(window.width(), window.height());
	frame_buffer.attatch(texture);
	RenderBuffer render_buffer;
	render_buffer.store(window.width(), window.height());
	frame_buffer.attatch(render_buffer);

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

		frame_buffer.bind_and_clear();

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

		window.bind_and_clear();
		texture.bind();

		screen_shader.use();
		screen_mesh.draw();

		window.update();
	}
}