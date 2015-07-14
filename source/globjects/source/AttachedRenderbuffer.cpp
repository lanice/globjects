#include <globjects/AttachedRenderbuffer.h>

#include <cassert>

#include <globjects/Renderbuffer.h>


namespace globjects
{

using namespace binding;

AttachedRenderbuffer::AttachedRenderbuffer(Framebuffer * fbo,  const GLenum attachment, Renderbuffer * renderBuffer)
: FramebufferAttachment(fbo, attachment)
, m_renderBuffer(renderBuffer)
{
}

bool AttachedRenderbuffer::isRenderBufferAttachment() const
{
	return true;
}

Renderbuffer * AttachedRenderbuffer::renderBuffer()
{
	return m_renderBuffer;
}

const Renderbuffer * AttachedRenderbuffer::renderBuffer() const
{
    return m_renderBuffer;
}

} // namespace globjects
