#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/ext.hpp>

#include "texture.hpp"

namespace rendering
{

static GLenum texture_sampling_to_gl(TextureSampling sampling)
{
	switch (sampling)
	{
		case TextureSampling::Linear:
			return GL_LINEAR;
	}
}

static GLenum texture_wrapping_to_gl(TextureWrapping wrapping)
{
	switch (wrapping)
	{
		case TextureWrapping::Clamp:
			return GL_CLAMP_TO_EDGE;
		case TextureWrapping::Border:
			return GL_CLAMP_TO_BORDER;
	}
}


Texture::Texture(TextureSampling sampling, TextureWrapping wrapping, glm::vec3 &&col)
	: m_sampling(sampling), m_wrapping(wrapping)
{
	glGenTextures(1, &m_id);

	glBindTexture(GL_TEXTURE_2D, m_id);

	GLenum sampling_gl = texture_sampling_to_gl(sampling);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sampling_gl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sampling_gl);

	GLenum wrapping_gl = GL_REPEAT;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping_gl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping_gl);

	if (wrapping == TextureWrapping::Border)
	{
		// set the border color
		glTexParameterfv(
				GL_TEXTURE_2D,
				GL_TEXTURE_BORDER_COLOR,
				glm::value_ptr(col));
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::store(
		unsigned int width,
		unsigned int height)
{
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			nullptr);
}

}