#pragma once

#include <globjects/binding/types.h>

#include <globjects/Framebuffer.h>


namespace globjects
{

class Framebuffer;
class Texture;
class Renderbuffer;

class AbstractFramebufferImplementation
{
public:
    AbstractFramebufferImplementation();
    virtual ~AbstractFramebufferImplementation();

    static AbstractFramebufferImplementation * get(Framebuffer::BindlessImplementation impl = 
        Framebuffer::BindlessImplementation::DirectStateAccessARB);


    virtual binding::GLuint create() const = 0;
    virtual void destroy(binding::GLuint id) const = 0;

    virtual binding::GLenum checkStatus(const Framebuffer * fbo) const = 0;
    virtual void setParameter(const Framebuffer * fbo, binding::GLenum pname, binding::GLint param) const = 0;
    virtual binding::GLint getAttachmentParameter(const Framebuffer * fbo, binding::GLenum attachment, binding::GLenum pname) const = 0;
    virtual void attachTexture(const Framebuffer * fbo, binding::GLenum attachment, Texture * texture, binding::GLint level) const = 0;
    virtual void attachTextureLayer(const Framebuffer * fbo, binding::GLenum attachment, Texture * texture, binding::GLint level, binding::GLint layer) const = 0;
    virtual void attachRenderBuffer(const Framebuffer * fbo, binding::GLenum attachment, Renderbuffer * renderBuffer) const = 0;
    virtual void setReadBuffer(const Framebuffer * fbo, binding::GLenum mode) const = 0;
    virtual void setDrawBuffer(const Framebuffer * fbo, binding::GLenum mode) const = 0;
    virtual void setDrawBuffers(const Framebuffer * fbo, binding::GLsizei n, const binding::GLenum * modes) const = 0;

public:
    static binding::GLenum s_workingTarget;
};

} // namespace globjects
