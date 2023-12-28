#include <GL/glew.h>
#include <GL/gl.h>
#include "window.hpp"

#include <iostream>

Window::Window(const char *title) : m_is_fullscreen(false), m_running(true), m_width(1600), m_height(900)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	constexpr SDL_WindowFlags flags = static_cast<SDL_WindowFlags>(
			SDL_WINDOW_SHOWN |
			SDL_WINDOW_RESIZABLE |
			SDL_WINDOW_OPENGL);
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, flags);
	m_gl_context = SDL_GL_CreateContext(m_window);
	glewExperimental = GL_TRUE;
	auto status = glewInit();
	if (status != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(status) << std::endl;
		exit(1);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	SDL_GL_SetSwapInterval(0);

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

Window::~Window()
{
	SDL_GL_DeleteContext(m_gl_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::clear()
{
	float r = 11.0f / 255.0 / 3.0;
	float g = 77.0f / 255.0 / 3.0;
	float b = 117.0f / 255.0 / 3.0;
	glViewport(0, 0, m_width, m_height);
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
	SDL_GL_SwapWindow(m_window);
}

int Window::width() const
{
	return m_width;
}

int Window::height() const
{
	return m_height;
}

float Window::aspect() const
{
	return static_cast<float>(m_width) / static_cast<float>(m_height);
}

void Window::handle_events(SDL_Event &event)
{
	switch (event.type)
	{
		case SDL_QUIT:
			m_running = false;
			break;
	case SDL_WINDOWEVENT:
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			m_width = event.window.data1;
			m_height = event.window.data2;
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_f:
			m_is_fullscreen = !m_is_fullscreen;
			SDL_SetWindowFullscreen(m_window, m_is_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
			break;
		case SDLK_ESCAPE:
			m_running = false;
			break;
		}
		break;
	}
}