#include "events.hpp"

#include <SDL2/SDL.h>

void EventManager::poll()
{
	m_events.clear();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		//get key
		if (event.type == SDL_KEYDOWN)
		{
			event.key.keysym.sym;
			m_events.push_back(Event{
				EventKind::KeyDown,
				{event.key.keysym.sym}
			});
		}
		else if (event.type == SDL_KEYUP)
		{
			m_events.push_back(Event{
				EventKind::KeyUp,
				{event.key.keysym.sym}
			});
		}
	}
}