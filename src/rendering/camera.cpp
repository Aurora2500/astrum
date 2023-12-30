#include <algorithm>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "camera.hpp"

Camera::Camera(float aspect)
	: m_pos(0.0f, 0.0f, 0.0f)
	, m_yaw(0.0f)
	, m_pitch(0.0f)
	, m_distance(10.0f)
	, m_fov(25.0f)
	, m_near(0.1f)
	, m_far(300.0f)
	, m_aspect(aspect)
{
}

Camera::~Camera()
{
}

void Camera::update(SDL_Event &event, bool &mouse_down)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		mouse_down = true;
	}

	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
	{
		mouse_down = false;
	}

	if (event.type == SDL_MOUSEMOTION && mouse_down)
	{
		m_yaw += event.motion.xrel * 0.01f;
		m_pitch += event.motion.yrel * 0.01f;

		float max_pitch = M_PI_2 - 0.01f;
		m_pitch = std::clamp(m_pitch, -max_pitch, max_pitch);

		m_yaw = fmod(m_yaw, 2 * M_PI);

		std::cout << this->pos().x << ", " << this->pos().y << ", " << this->pos().z << std::endl;
	}

	if (event.type == SDL_MOUSEWHEEL)
	{
		m_distance *= std::pow(1.1f, -event.wheel.y);
		m_distance = std::clamp(m_distance, 1.0f, 100.0f);
	}
}

glm::mat4 Camera::get_view_matrix() const
{
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -m_distance));
	view = glm::rotate(view, m_pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, m_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::translate(view, -m_pos);

	glm::mat4 projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
	return projection * view;
}

glm::vec3 Camera::pos() const
{
	return m_pos + glm::vec3(
		- m_distance * std::cos(m_pitch) * std::sin(m_yaw),
		m_distance * std::sin(m_pitch),
		- m_distance * std::cos(m_pitch) * std::cos(m_yaw));
}