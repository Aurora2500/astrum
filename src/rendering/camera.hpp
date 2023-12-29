#pragma once

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

class Camera
{
private:
	glm::vec3 m_pos;
	float m_yaw;
	float m_pitch;
	float m_distance;
	float m_fov;
	float m_near, m_far;
	float m_aspect;

public:
	Camera(float aspect);
	~Camera();

	void update(SDL_Event &event, bool &mouse_down);

	glm::mat4 get_view_matrix() const;

	inline float &yaw() { return m_yaw; }
	inline float &pitch() { return m_pitch; }
	inline float &distance() { return m_distance; }
	inline float &aspect() { return m_aspect; }
	inline glm::vec3 &position() { return m_pos; }
};