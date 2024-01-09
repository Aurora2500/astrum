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

#include "rendering/starsystem.hpp"

#include "rendering/frame_buffer.hpp"
#include "rendering/texture.hpp"
#include "rendering/render_buffer.hpp"

#include "util/stopwatch.hpp"
#include "util/locator.hpp"

#include "core/star.hpp"
#include "core/planet.hpp"

void run_game()
{
	using namespace rendering;

	auto assets = AssetManager();
	Locator::provide(&assets);

	Window window("Astrum");

	int n;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &n);
	std::cout << "Max uniform size: " << n << std::endl;

	SDL_Event event;

	Camera cam(window.aspect());
	bool mouse_down = false;

	core::Star star(core::StarType::YellowDwarf, 420, 2.0, glm::vec3(0.0f));

	star.planets().emplace_back(
		core::PlanetType::Continental,
		30, glm::vec3(0.0f, 0.0f, 10.0f));
	star.planets().emplace_back(
		core::PlanetType::Continental,
		30, glm::vec3(7.0f, -3.0f, 2.0f));
	star.planets().emplace_back(
		core::PlanetType::Continental,
		30, glm::vec3(1.0f, 4.0f, -5.0f));

	StarSystemRenderer renderer(star);

	cam.focus() = glm::vec3(0.0f, 0.0f, 10.0f);
	
	while (window.running())
	{
		while (SDL_PollEvent(&event))
		{
			window.handle_events(event);
			cam.update(event, mouse_down);
		}
		assets.poll();
		window.clear();
		renderer.draw(cam);
		window.update();
	}
}