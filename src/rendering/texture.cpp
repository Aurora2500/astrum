#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/ext.hpp>

#include "texture.hpp"

#include <iostream>

#include "util/locator.hpp"

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
		case TextureWrapping::Wrap:
			return GL_WRAP_BORDER;
		case TextureWrapping::Border:
			return GL_CLAMP_TO_BORDER;
	}
}

Texture::Texture(TextureSampling sampling, TextureWrapping wrapping, glm::vec3 &&col)
	: m_sampling(sampling), m_wrapping(wrapping)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

	GLenum sampling_gl = texture_sampling_to_gl(sampling);
	glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, sampling_gl);
	glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, sampling_gl);

	GLenum wrapping_gl = GL_REPEAT;
	glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrapping_gl);
	glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrapping_gl);

	if (wrapping == TextureWrapping::Border)
	{
		glTextureParameterfv(
				m_id,
				GL_TEXTURE_BORDER_COLOR,
				glm::value_ptr(col));
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind(int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
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
	if (m_width == width && m_height == height) return;
	glTextureStorage2D(
			m_id,
			1,
			GL_RGB8,
			width,
			height);
	m_width = width;
	m_height = height;
}

void Texture::load(const std::string &path) {
	auto &asset_manager = Locator::assets();
	int width, height, channels;
	auto data = asset_manager.load_image(path, width, height, channels);
	std::cout << width << " width " << height << " height " << channels << " channels" << std::endl;
	glTextureStorage2D(
			m_id,
			1,
			GL_RGB8,
			width,
			height);
	glTextureSubImage2D(
		m_id,
		0,
		0,
		0,
		width,
		height,
		GL_RGB,
		GL_BYTE,
		data.data()
	);
	m_width = width;
	m_height = height;
}

Cubemap::Cubemap(TextureSampling sampling, TextureWrapping wrapping)
	: m_sampling(TextureSampling::Linear), m_wrapping(TextureWrapping::Border)
{
	glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_id);

	GLenum sampling_gl = texture_sampling_to_gl(sampling);
	glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, sampling_gl);
	glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, sampling_gl);

	GLenum wrapping_gl = texture_wrapping_to_gl(wrapping);
	glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrapping_gl);
	glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrapping_gl);
	glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, wrapping_gl);
}

Cubemap::~Cubemap()
{
	glDeleteTextures(1, &m_id);
}

void Cubemap::bind(int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}

void Cubemap::unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::load(const std::string &path)
{
	auto &asset = Locator::assets();
	std::array<std::string, 6> faces = {
		"px.png",
		"nx.png",
		"py.png",
		"ny.png",
		"pz.png",
		"nz.png",
	};

	for (int i = 0; i < 6; i++)
	{
		int width, height, channels;
		auto data = asset.load_image(path + "_" + faces[i], width, height, channels, false);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
		glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				channels == 4 ? GL_RGBA : GL_RGB,
				GL_UNSIGNED_BYTE,
				data.data());
	}
}

}