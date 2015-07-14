#pragma once

#include <globjects/base/Singleton.h>

#include "AbstractFramebufferImplementation.h"


namespace globjects
{

class FramebufferImplementation_Legacy : public AbstractFramebufferImplementation
    , public Singleton<FramebufferImplementation_Legacy>
{
public:
    virtual binding::GLuint create() const override;
    virtual void destroy(binding::GLuint id) const override;

    virtual binding::GLenum checkStatus(const Framebuffer * fbo) const override;
    virtual void setParameter(const Framebuffer * fbo, binding::GLenum pname, binding::GLint param) const override;
    virtual binding::GLint getAttachmentParameter(const Framebuffer * fbo, binding::GLenum attachment, binding::GLenum pname) const override;
    virtual void attachTexture(const Framebuffer * fbo, binding::GLenum attachment, Texture * texture, binding::GLint level) const override;
    virtual void attachTextureLayer(const Framebuffer * fbo, binding::GLenum attachment, Texture * texture, binding::GLint level, binding::GLint layer) const override;
    virtual void attachRenderBuffer(const Framebuffer * fbo, binding::GLenum attachment, Renderbuffer * renderBuffer) const override;
    virtual void setReadBuffer(const Framebuffer * fbo, binding::GLenum mode) const override;
    virtual void setDrawBuffer(const Framebuffer * fbo, binding::GLenum mode) const override;
    virtual void setDrawBuffers(const Framebuffer * fbo, binding::GLsizei n, const binding::GLenum * modes) const override;
};

} // namespace globjects
