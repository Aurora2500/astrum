#include "render_buffer.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

namespace rendering
{

RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &m_id);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &m_id);
}

void RenderBuffer::store(
		unsigned int width,
		unsigned int height)
{
	if (m_width == width && m_height == height) return;
	glBindRenderbuffer(GL_RENDERBUFFER, m_id);
	glRenderbufferStorage(
			GL_RENDERBUFFER,
			GL_DEPTH24_STENCIL8,
			width,
			height);
	m_width = width;
	m_height = height;
}

}