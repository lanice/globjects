#pragma once

#include <globjects/binding/types.h>

#include <globjects/base/Singleton.h>

#include <globjects/globjects_api.h>

#include "AbstractVertexAttributeBindingImplementation.h"

namespace globjects {

class VertexAttributeBindingImplementation_VertexAttribBindingARB : public AbstractVertexAttributeBindingImplementation
        , public Singleton<VertexAttributeBindingImplementation_VertexAttribBindingARB>
{
public:
    VertexAttributeBindingImplementation_VertexAttribBindingARB();
    virtual ~VertexAttributeBindingImplementation_VertexAttribBindingARB();

    virtual void enable(const VertexArray * vertexArray, binding::GLint attributeIndex) const override;
    virtual void disable(const VertexArray * vertexArray, binding::GLint attributeIndex) const override;

    virtual void setAttributeDivisor(const VertexAttributeBinding * binding, binding::GLuint divisor) const override;

    virtual void bindAttribute(const VertexAttributeBinding * binding, binding::GLint attributeIndex) const override;
    virtual void bindBuffer(const VertexAttributeBinding * binding, const Buffer * vbo, binding::GLint baseoffset, binding::GLint stride) const override;

    virtual void setFormat(const VertexAttributeBinding * binding, binding::GLint size, binding::GLenum type, binding::GLboolean normalized, binding::GLuint relativeoffset) const override;
    virtual void setIFormat(const VertexAttributeBinding * binding, binding::GLint size, binding::GLenum type, binding::GLuint relativeoffset) const override;
    virtual void setLFormat(const VertexAttributeBinding * binding, binding::GLint size, binding::GLenum type, binding::GLuint relativeoffset) const override;
};

} // namespace globjects
