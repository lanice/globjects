#pragma once

#include <globjects/binding/types.h>
#include <globjects/binding/boolean.h>

#include <globjects/base/Referenced.h>

#include <globjects/globjects_api.h>

namespace globjects 
{

class Buffer;
class VertexArray;


class GLOBJECTS_API VertexAttributeBinding : public Referenced
{
    friend class AbstractVertexAttributeBindingImplementation;

public:
	VertexAttributeBinding(
        VertexArray * vao
    ,   const binding::GLint bindingIndex);

    const VertexArray * vao() const;
    VertexArray * vao();

    void setDivisor(binding::GLint divisor);

	void setAttribute(binding::GLint attributeIndex);
	void setBuffer(
        const Buffer * vbo
    ,   binding::GLint baseoffset
    ,   binding::GLint stride);

	void setFormat(
        binding::GLint size
    ,   binding::GLenum type
    ,   binding::GLboolean normalized = binding::GL_FALSE
    ,   binding::GLuint relativeoffset = 0);
	void setIFormat(
        binding::GLint size
    ,   binding::GLenum type
    ,   binding::GLuint relativeoffset = 0);
#ifdef GLOBJECTS_GL_BINDING
	void setLFormat(
        binding::GLint size
    ,   binding::GLenum type
    ,   binding::GLuint relativeoffset = 0);
#endif

    binding::GLint attributeIndex() const;
    binding::GLint bindingIndex() const;
    const Buffer * buffer() const;

protected:
    virtual ~VertexAttributeBinding();

protected:
    VertexArray * m_vao; // TODO: weak_ptr?
   
    binding::GLint m_bindingIndex;
    binding::GLint m_attributeIndex;
    
    const Buffer * m_vbo;

    mutable void * m_bindingData;
};

} // namespace globjects
