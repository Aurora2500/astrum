#include <array>
#include <iostream>
#include <algorithm>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <glm/ext.hpp>

#include "game.hpp"
#include "windowing/window.hpp"

#include "rendering/camera.hpp"
#include "rendering/mesh.hpp"
#include "rendering/vertex.hpp"
#include "rendering/planet.hpp"

#include "util/stopwatch.hpp"

Game::Game()
{
}

void Game::run()
{
	Window window("Astrum");

	SDL_Event event;

	Camera cam;
	Shader &shader = m_assets.get_shader("planet");
	shader.use();
	Mesh mesh = create_sphere(30, 30);
	mesh.make_buffers();

	bool mouse_down = false;

	while (window.running())
	{
		while (SDL_PollEvent(&event))
		{
			window.handle_events(event);
			cam.update(event, mouse_down);
		}
		window.clear();
		glm::mat4 view = cam.get_view_matrix(window.aspect());
		shader.set_uniform("view", view);
		mesh.draw();
		window.update();
	}
}