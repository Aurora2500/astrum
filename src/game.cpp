#include <array>
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

Game::Game()
{
}

void Game::run()
{
	Window window("Astrum");

	SDL_Event event;
	bool running = true;

	Camera cam;

	glEnable(GL_CULL_FACE);

	Shader &shader = m_assets.get_shader("planet");
	shader.use();

	int viewLoc = glGetUniformLocation(shader.id(), "view");

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window.width() / (float)window.height(), 0.1f, 100.0f);

	Mesh mesh = create_sphere(30, 30);
	mesh.make_buffers();

	bool mouse_down = false;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				running = false;
			window.handle_events(event);

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				mouse_down = true;
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				mouse_down = false;
			}

			if (event.type == SDL_MOUSEMOTION && mouse_down)
			{
				cam.yaw() += event.motion.xrel * 0.01f;
				cam.pitch() += event.motion.yrel * 0.01f;

				float max_pitch = M_PI_2 - 0.01f;
				cam.pitch() = std::clamp(cam.pitch(), -max_pitch, max_pitch);

				cam.yaw() = fmod(cam.yaw(), 2 * M_PI);
			}

			if (event.type == SDL_MOUSEWHEEL)
			{
				cam.distance() -= event.wheel.y * 0.1f;
				cam.distance() = std::clamp(cam.distance(), 1.0f, 100.0f);
			}
		}
		window.clear();
		glm::mat4 view = cam.get_view_matrix();
		glm::mat4 pv = projection * view;
		// set the uniform
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(pv));
		mesh.draw();
		window.update();
	}
}