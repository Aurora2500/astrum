#pragma once
#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 position;
	float m_yaw;
	float m_pitch;
	float m_distance;

public:
	Camera();
	~Camera();

	glm::mat4 get_view_matrix() const;

	inline float &yaw() { return m_yaw; }
	inline float &pitch() { return m_pitch; }
	inline float &distance() { return m_distance; }
};