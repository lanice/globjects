
#include "FramebufferImplementation_Legacy.h"

#include <globjects/binding/functions.h>
#include <globjects/binding/enum.h>

#include <globjects/Framebuffer.h>
#include <globjects/Texture.h>
#include <globjects/Renderbuffer.h>


namespace globjects 
{

using namespace binding;

GLuint FramebufferImplementation_Legacy::create() const
{
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer); // create a handle to a potentially used framebuffer
    glBindFramebuffer(s_workingTarget, framebuffer); // trigger actual framebuffer creation

    return framebuffer;
}

void FramebufferImplementation_Legacy::destroy(GLuint id) const
{
    glDeleteFramebuffers(1, &id);
}

GLenum FramebufferImplementation_Legacy::checkStatus(const Framebuffer * fbo) const
{
    fbo->bind(s_workingTarget);

    return glCheckFramebufferStatus(s_workingTarget);
}

void FramebufferImplementation_Legacy::setParameter(const Framebuffer * fbo, GLenum pname, GLint param) const
{
    fbo->bind(s_workingTarget);

    glFramebufferParameteri(s_workingTarget, pname, param);
}

GLint FramebufferImplementation_Legacy::getAttachmentParameter(const Framebuffer * fbo, GLenum attachment, GLenum pname) const
{
    fbo->bind(s_workingTarget);

    GLint result = 0;

    glGetFramebufferAttachmentParameteriv(s_workingTarget, attachment, pname, &result);

    return result;
}

void FramebufferImplementation_Legacy::attachTexture(const Framebuffer * fbo, GLenum attachment, Texture * texture, GLint level) const
{
    fbo->bind(s_workingTarget);

#ifdef GLOBJECTS_GL_BINDING
    if (texture == nullptr)
    {
        glFramebufferTexture(s_workingTarget, attachment, 0, level);
    }
    else
#endif
    {
        switch (texture->target())
        {
#ifdef GLOBJECTS_GL_BINDING
        case GL_TEXTURE_1D:
            glFramebufferTexture1D(s_workingTarget, attachment, texture->target(), texture->id(), level);
            break;
#endif
        case GL_TEXTURE_2D:
#ifdef GLOBJECTS_GL_BINDING
        case GL_TEXTURE_RECTANGLE:
#endif
        case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        case GL_TEXTURE_2D_MULTISAMPLE:
            glFramebufferTexture2D(s_workingTarget, attachment, texture->target(), texture->id(), level);
            break;
        default:
#ifdef GLOBJECTS_GL_BINDING
            glFramebufferTexture(s_workingTarget, attachment, texture->id(), level);
#else
            // TODO: not implemented
#endif
            break;
        }
    }
}

void FramebufferImplementation_Legacy::attachTextureLayer(const Framebuffer * fbo, GLenum attachment, Texture * texture, GLint level, GLint layer) const
{
    fbo->bind(s_workingTarget);

    glFramebufferTextureLayer(s_workingTarget, attachment, texture ? texture->id() : 0, level, layer);
}

void FramebufferImplementation_Legacy::attachRenderBuffer(const Framebuffer * fbo, GLenum attachment, Renderbuffer * renderBuffer) const
{
    fbo->bind(s_workingTarget);
    renderBuffer->bind();

    glFramebufferRenderbuffer(s_workingTarget, attachment, GL_RENDERBUFFER, renderBuffer->id());
}

void FramebufferImplementation_Legacy::setReadBuffer(const Framebuffer * fbo, GLenum mode) const
{
    fbo->bind(GL_READ_FRAMEBUFFER);

    glReadBuffer(mode);
}

void FramebufferImplementation_Legacy::setDrawBuffer(const Framebuffer * fbo, GLenum mode) const
{
    fbo->bind(GL_DRAW_FRAMEBUFFER);

#ifdef GLOBJECTS_GL_BINDING
    glDrawBuffer(mode);
#else
    GLenum modes[] = { mode };
    glDrawBuffers(1, modes);
#endif
}

void FramebufferImplementation_Legacy::setDrawBuffers(const Framebuffer * fbo, GLsizei n, const GLenum * modes) const
{
    fbo->bind(GL_DRAW_FRAMEBUFFER);

    glDrawBuffers(n, modes);
}

} // namespace globjects
