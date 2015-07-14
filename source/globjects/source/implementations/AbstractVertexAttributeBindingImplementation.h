#pragma once

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>

#include <globjects/VertexArray.h>

namespace globjects {

class VertexArray;
class VertexAttributeBinding;
class Buffer;

class AbstractVertexAttributeBindingImplementation
{
public:
    AbstractVertexAttributeBindingImplementation();
    virtual ~AbstractVertexAttributeBindingImplementation();

    static AbstractVertexAttributeBindingImplementation * get(VertexArray::AttributeImplementation impl =
        VertexArray::AttributeImplementation::VertexAttribBindingARB);

    virtual void enable(const VertexArray * vertexArray, binding::GLint attributeIndex) const = 0;
    virtual void disable(const VertexArray * vertexArray, binding::GLint attributeIndex) const = 0;

    virtual void setAttributeDivisor(const VertexAttributeBinding * binding, binding::GLuint divisor) const = 0;

    virtual void bindAttribute(const VertexAttributeBinding * binding, binding::GLint attributeIndex) const = 0;
    virtual void bindBuffer(const VertexAttributeBinding * binding, const Buffer * vbo, binding::GLint baseoffset, binding::GLint stride) const = 0;

    virtual void setFormat(const VertexAttributeBinding * binding, binding::GLint size, binding::GLenum type, binding::GLboolean normalized, binding::GLuint relativeoffset) const = 0;
    virtual void setIFormat(const VertexAttributeBinding * binding, binding::GLint size, binding::GLenum type, binding::GLuint relativeoffset) const = 0;
#ifdef GLOBJECTS_GL_BINDING
    virtual void setLFormat(const VertexAttributeBinding * binding, binding::GLint size, binding::GLenum type, binding::GLuint relativeoffset) const = 0;
#endif
protected:
    binding::GLint attributeIndex(const VertexAttributeBinding * binding) const;
    binding::GLint bindingIndex(const VertexAttributeBinding * binding) const;

    const VertexArray * vao(const VertexAttributeBinding * binding) const;
    const Buffer * vbo(const VertexAttributeBinding * binding) const;

    void * & bindingData(const VertexAttributeBinding * binding) const;
};

} // namespace globjects
