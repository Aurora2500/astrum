#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Window
{
	SDL_Window *m_window;
	SDL_GLContext m_gl_context;

	bool m_is_fullscreen;
	int m_width, m_height;

public:
	Window(const char *title);
	~Window();

	void clear();
	void update();

	int width() const;
	int height() const;

	void handle_events(SDL_Event &event);
};