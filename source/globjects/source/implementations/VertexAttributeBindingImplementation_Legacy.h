#pragma once

#include <globjects/binding/types.h>

#include <globjects/base/Singleton.h>

#include <globjects/globjects_api.h>

#include "AbstractVertexAttributeBindingImplementation.h"


namespace globjects 
{

class VertexAttributeBindingImplementation_Legacy : public AbstractVertexAttributeBindingImplementation
        , public Singleton<VertexAttributeBindingImplementation_Legacy>
{
public:
    VertexAttributeBindingImplementation_Legacy();
    virtual ~VertexAttributeBindingImplementation_Legacy();

    virtual void enable(const VertexArray * vertexArray, binding::GLint attributeIndex) const override;
    virtual void disable(const VertexArray * vertexArray, binding::GLint attributeIndex) const override;

    virtual void setAttributeDivisor(const VertexAttributeBinding * binding, binding::GLuint divisor) const override;

    virtual void bindAttribute(const VertexAttributeBinding * binding, binding::GLint attributeIndex) const override;
    virtual void bindBuffer(const VertexAttributeBinding * binding, const Buffer * vbo, binding::GLint baseoffset, binding::GLint stride) const override;

    virtual void setFormat(const VertexAttributeBinding * binding, binding::GLint size, binding::GLenum type, binding::GLboolean normalized, binding::GLuint relativeoffset) const override;
    virtual void setIFormat(const VertexAttributeBinding * binding, binding::GLint size, binding::GLenum type, binding::GLuint relativeoffset) const override;
#ifdef GLOBJECTS_GL_BINDING
    virtual void setLFormat(const VertexAttributeBinding * binding, binding::GLint size, binding::GLenum type, binding::GLuint relativeoffset) const override;
#endif

protected:

    struct Format
    {
        enum class Method
        {
            O = 0
        ,   I = 1
#ifdef GLOBJECTS_GL_BINDING
        ,   L = 2
#endif
        };

        Format();
        Format(Method method, binding::GLint size, binding::GLenum type, binding::GLboolean normalized, binding::GLuint relativeoffset);

        Method        method;
        binding::GLint     size;
        binding::GLenum    type;
        binding::GLboolean normalized;
        binding::GLuint    relativeoffset;
    };

    struct BindingData
    {
        BindingData();

        Format    format;
        binding::GLint baseoffset;
        binding::GLint stride;
        bool      hasFormat;
        bool      hasBuffer;
        bool      hasAttribute;
    };

    BindingData * & bindingData(const VertexAttributeBinding * binding) const;

    void finishIfComplete(const VertexAttributeBinding * binding) const;
    void finish(const VertexAttributeBinding * binding) const;
};

} // namespace globjects
