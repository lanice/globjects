#pragma once

#include <globjects/binding/types.h>

#include <globjects/base/ref_ptr.h>

#include <globjects/globjects_api.h>
#include <globjects/FramebufferAttachment.h>

namespace globjects 
{

class Texture;
class Framebuffer;

/** \brief Encapsulates texture attachments of a frame buffer object.
    
    This class is a link between a Texture and the FrameBufferObject it is attached to.
    
    \see Texture
    \see Framebuffer
 */
class GLOBJECTS_API AttachedTexture : public FramebufferAttachment
{
public:
    AttachedTexture(Framebuffer * fbo, binding::GLenum attachment, Texture * texture, binding::GLint level, binding::GLint layer = -1);

    virtual bool isTextureAttachment() const override;

    Texture * texture();
    const Texture * texture() const;

    binding::GLint level() const;

    bool hasLayer() const;
    binding::GLint layer() const;

protected:
    ref_ptr<Texture> m_texture;
    binding::GLint m_level;
    binding::GLint m_layer;
};

} // namespace globjects
