#include "frame_buffer.hpp"

#include <GL/glew.h>
#include <GL/gl.h>


namespace rendering
{

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_id);
}

void FrameBuffer::attatch(const Texture& texture)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D,
			texture.id(),
			0);
}

void FrameBuffer::attatch(const RenderBuffer& render_buffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	glFramebufferRenderbuffer(
			GL_FRAMEBUFFER,
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
	glClear(bits);
	glEnable(GL_DEPTH_TEST);
}

}