#include "frame_buffer.hpp"

#include <GL/glew.h>
#include <GL/gl.h>


namespace rendering
{

FrameBuffer::FrameBuffer()
{
	glCreateFramebuffers(1, &m_id);
}

void FrameBuffer::attatch(const Texture& texture)
{
	glNamedFramebufferTexture(m_id, GL_COLOR_ATTACHMENT0, texture.id(), 0);
}

void FrameBuffer::attatch(const RenderBuffer& render_buffer)
{
	glNamedFramebufferRenderbuffer(
			m_id,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_RENDERBUFFER,
			render_buffer.id());
}

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void FrameBuffer::bind_and_clear(GLbitfield bits) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(bits);
	glEnable(GL_DEPTH_TEST);
}

}