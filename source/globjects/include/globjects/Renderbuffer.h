#pragma once

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>
#include <globjects/Object.h>

namespace globjects 
{

/** \brief Encapsulates OpenGL render buffer objects.
 
    \see http://www.opengl.org/wiki/Renderbuffer_Objects
 */
class GLOBJECTS_API Renderbuffer : public Object
{
public:
    Renderbuffer();

    virtual void accept(ObjectVisitor & visitor) override;

    void bind() const;
    static void unbind();

    void storage(binding::GLenum internalformat, binding::GLsizei width, binding::GLsizei height);
    void storageMultisample(binding::GLsizei samples, binding::GLenum internalformat, binding::GLsizei width, binding::GLsizei height);

    binding::GLint getParameter(binding::GLenum pname) const;

#ifdef GLOBJECTS_GL_BINDING
    virtual binding::GLenum objectType() const override;
#endif

protected:
    virtual ~Renderbuffer();

    void bind(binding::GLenum target) const;
    static void unbind(binding::GLenum target);
};

} // namespace globjects
