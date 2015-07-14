#pragma once

#include <string>

#include <globjects/binding/types.h>

#include <globjects/base/Referenced.h>

#include <globjects/globjects_api.h>

namespace globjects 
{

class AttachedTexture;
class AttachedRenderbuffer;
class Framebuffer;

/** \brief Wraps attachments to a FrameBufferObject.
    
    Normally, FrameBufferAttachments are created using the API of FrameBufferObject.
    
    \see FrameBufferObject
    \see TextureAttachment
    \see RenderBufferAttachment
*/
class GLOBJECTS_API FramebufferAttachment : public Referenced
{
public:
    FramebufferAttachment(Framebuffer * fbo, binding::GLenum attachment);

	binding::GLenum attachment() const;

    binding::GLint getParameter(binding::GLenum pname) const;

	virtual bool isTextureAttachment() const;
	virtual bool isRenderBufferAttachment() const;

    AttachedTexture * asTextureAttachment();
    const AttachedTexture * asTextureAttachment() const;
    AttachedRenderbuffer * asRenderBufferAttachment();
    const AttachedRenderbuffer * asRenderBufferAttachment() const;

	std::string attachmentString() const;

protected:
    Framebuffer * m_fbo; // TODO: weak pointer?
	binding::GLenum m_attachment;
};

} // namespace globjects
