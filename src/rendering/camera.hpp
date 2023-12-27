#pragma once
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

class Camera
{
private:
	glm::vec3 position;
	float m_yaw;
	float m_pitch;
	float m_distance;
	float m_fov;
	float m_near, m_far;

public:
	Camera();
	~Camera();

	void update(SDL_Event &event, bool &mouse_down);

	glm::mat4 get_view_matrix(float aspect) const;

	inline float &yaw() { return m_yaw; }
	inline float &pitch() { return m_pitch; }
	inline float &distance() { return m_distance; }
};