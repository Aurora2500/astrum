#include <SDL2/SDL.h>

#include "game.hpp"
#include "window.hpp"

void Game::run()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Window window("Astrum");

	SDL_Event event;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				running = false;
		}
		window.clear();
		window.update();
	}

	SDL_Quit();
}