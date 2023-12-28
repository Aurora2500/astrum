#pragma once

#include <glm/glm.hpp>

namespace rendering {

enum class TextureSampling
{
	Linear,
};

enum class TextureWrapping
{
	Clamp,
	Border,
};

class Texture
{
private:
	unsigned int m_id;
	TextureSampling m_sampling;
	TextureWrapping m_wrapping;

public:
	Texture(TextureSampling sampling = TextureSampling::Linear, TextureWrapping wrapping = TextureWrapping::Border, glm::vec3 &&col = glm::vec3(0.0f, 0.0f, 0.0f));
	~Texture();

	void bind() const;
	void unbind() const;

	void store(
			unsigned int width,
			unsigned int height);

	inline unsigned int id() const { return m_id; }

};

}