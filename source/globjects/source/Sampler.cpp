#include <globjects/Sampler.h>

#include <globjects/binding/functions.h>
#include <globjects/binding/enum.h>

#include <globjects/ObjectVisitor.h>

#include "Resource.h"


namespace globjects
{

using namespace binding;

Sampler::Sampler()
: Object(new SamplerResource)
{
}

Sampler::Sampler(IDResource * resource)
: Object(resource)
{
}

Sampler * Sampler::fromId(const GLuint id)
{
    return new Sampler(new ExternalResource(id));
}

Sampler::~Sampler()
{
}

void Sampler::accept(ObjectVisitor & visitor)
{
    visitor.visitSampler(this);
}

void Sampler::bind(const GLuint unit) const
{
    glBindSampler(unit, id());
}

void Sampler::unbind(const GLuint unit)
{
    glBindSampler(unit, 0);
}

void Sampler::setParameter(const GLenum name, const GLint value)
{
    glSamplerParameteri(id(), name, value);
}

void Sampler::setParameter(const GLenum name, const GLfloat value)
{
    glSamplerParameterf(id(), name, value);
}

GLint Sampler::getParameteri(const GLenum pname) const
{
    GLint value = 0;
    glGetSamplerParameteriv(id(), pname, &value);

	return value;
}

GLfloat Sampler::getParameterf(const GLenum pname) const
{
    GLfloat value = 0;
    glGetSamplerParameterfv(id(), pname, &value);

	return value;
}

#ifdef GLOBJECTS_GL_BINDING
GLenum Sampler::objectType() const
{
    return GL_SAMPLER;
}
#endif

} // namespace globjects
