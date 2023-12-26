#include <SDL2/SDL.h>

class Window
{
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

public:
	Window(const char *title);
	~Window();

	void clear();
	void update();
};