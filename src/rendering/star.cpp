#include "star.hpp"

#include <glm/ext.hpp>

namespace rendering
{

StarRenderer::StarRenderer(core::Star &star, Mesh &mesh, AssetManager &manager)
	: m_star(star), m_mesh(mesh), m_shader(manager.get_shader("star")) {}

void StarRenderer::draw(Camera &camera) const
{
	glm::mat4 view = camera.get_view_matrix();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_star.pos());
	model = glm::scale(model, glm::vec3(m_star.size()));

	m_shader.use();
	m_shader.set_uniform("view", view);
	m_shader.set_uniform("model", model);
	m_mesh.draw();
}

}