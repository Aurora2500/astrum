#include <iostream>
#include <algorithm>
#include <vector>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <glm/ext.hpp>

#include "game.hpp"
#include "windowing/window.hpp"
#include "windowing/events.hpp"

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

#include "appstate.hpp"

void run_game()
{
	using namespace rendering;

	auto assets = AssetManager();
	Locator::provide(&assets);

	Window window("Astrum");
	EventManager event_manager;

	AppStateManager appstate = AppStateManager();

	Camera cam(window.aspect());
	
	while (window.running())
	{
		event_manager.poll();
		assets.poll();
		window.clear();

		if (event_manager.test_flag(EventKind::Quit)) break;

		bool should_continue = appstate.update();
		window.update();

		if (!should_continue) break;
	}
}