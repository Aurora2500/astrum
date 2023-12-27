#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "camera.hpp"

Camera::Camera() : position(0.0f, 0.0f, 0.0f), m_yaw(0.0f), m_pitch(0.0f), m_distance(10.0f)
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::get_view_matrix() const
{
	glm::mat4 view_matrix(1.0f);
	view_matrix = glm::translate(view_matrix, glm::vec3(0.0f, 0.0f, -m_distance));
	view_matrix = glm::rotate(view_matrix, m_pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	view_matrix = glm::rotate(view_matrix, m_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	view_matrix = glm::translate(view_matrix, -position);
	return view_matrix;
}