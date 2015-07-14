#pragma once

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>
#include <globjects/Object.h>

namespace globjects 
{

/** \brief Wraps OpenGL sampler objects.
        
    \see http://www.opengl.org/wiki/Sampler_Object
 */
class GLOBJECTS_API Sampler : public Object
{
public:
    Sampler();
    static Sampler * fromId(binding::GLuint id);

    virtual void accept(ObjectVisitor & visitor) override;

    void bind(binding::GLuint unit) const;
    static void unbind(binding::GLuint unit);

    void setParameter(binding::GLenum name, binding::GLint value);
    void setParameter(binding::GLenum name, binding::GLfloat value);

    binding::GLint getParameteri(binding::GLenum pname) const;
    binding::GLfloat getParameterf(binding::GLenum pname) const;

#ifdef GLOBJECTS_GL_BINDING
    virtual binding::GLenum objectType() const override;
#endif

protected:
    Sampler(IDResource * resource);
    virtual ~Sampler();
};

} // namespace globjects
