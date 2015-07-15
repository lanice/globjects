#pragma once

#include <vector>
#include <array>
#include <string>

#include <globjects/binding/boolean.h>
#include <globjects/binding/enum.h>

#include <globjects/base/ref_ptr.h>
#include <globjects/base/Referenced.h>

#include <globjects/VertexArray.h>
#include <globjects/Buffer.h>

namespace globjects
{

class VertexAttributeBinding;

}


class VertexDrawable : public globjects::Referenced
{
public:
    class AttributeFormat
    {
    public:
        enum FormatType
        {
            Float
            , Integer
#ifdef GLOBJECTS_GL_BINDING
            , Long
#endif
        };

        AttributeFormat();
        AttributeFormat(globjects::binding::GLint size, globjects::binding::GLenum type, globjects::binding::GLboolean normalized, globjects::binding::GLuint relativeOffset, FormatType formatType);

        void setTo(globjects::VertexAttributeBinding * binding) const;

    protected:
        globjects::binding::GLint size;
        globjects::binding::GLenum type;
        globjects::binding::GLboolean normalized;
        globjects::binding::GLuint relativeOffset;

        FormatType formatType;
    };

    VertexDrawable(globjects::binding::GLenum primitiveMode = globjects::binding::GL_TRIANGLES);
    VertexDrawable(globjects::binding::GLint baseOffset, globjects::binding::GLint stride, globjects::binding::GLenum primitiveMode = globjects::binding::GL_TRIANGLES);
    VertexDrawable(globjects::Buffer* vbo, globjects::binding::GLint baseOffset, globjects::binding::GLint stride, globjects::binding::GLint size, globjects::binding::GLenum primitiveMode = globjects::binding::GL_TRIANGLES);
    template <typename T>
    VertexDrawable(const std::vector<T> & vertices, globjects::binding::GLenum primitiveMode = globjects::binding::GL_TRIANGLES);
    template <typename T, std::size_t Count>
    VertexDrawable(const std::array<T, Count> & vertices, globjects::binding::GLenum primitiveMode = globjects::binding::GL_TRIANGLES);

    void setBuffer(globjects::Buffer* vbo, globjects::binding::GLint size);
    void setBuffer(globjects::Buffer* vbo, globjects::binding::GLint baseOffset, globjects::binding::GLint stride, globjects::binding::GLint size);
    void setPrimitiveMode(globjects::binding::GLenum primitiveMode);

    template <typename T>
    void setVertices(const std::vector<T> & vertices);

    void setFormats(const std::vector<AttributeFormat> & formats);
    void bindAttributes(const std::vector<globjects::binding::GLint> & attributeIndices);

    void enableAll();

    void draw() const;

protected:
    globjects::ref_ptr<globjects::VertexArray> m_vao;
    globjects::ref_ptr<globjects::Buffer> m_vbo;

    std::vector<globjects::binding::GLint> m_attributeIndices;
    std::vector<AttributeFormat> m_formats;

    globjects::binding::GLint m_baseOffset;
    globjects::binding::GLint m_stride;
    globjects::binding::GLint m_size;
    globjects::binding::GLenum m_primitiveMode;
};

VertexDrawable::AttributeFormat Format(globjects::binding::GLint size, globjects::binding::GLenum type, globjects::binding::GLuint relativeOffset, globjects::binding::GLboolean normalized = globjects::binding::GL_FALSE);
VertexDrawable::AttributeFormat FormatI(globjects::binding::GLint size, globjects::binding::GLenum type, globjects::binding::GLuint relativeOffset);

#ifdef GLOBJECTS_GL_BINDING
VertexDrawable::AttributeFormat FormatL(globjects::binding::GLint size, globjects::binding::GLenum type, globjects::binding::GLuint relativeOffset);
#endif

template <typename T>
VertexDrawable::VertexDrawable(const std::vector<T> & vertices, globjects::binding::GLenum primitiveMode)
: m_vao(new globjects::VertexArray)
, m_vbo(new globjects::Buffer)
, m_baseOffset(0)
, m_stride(sizeof(T))
, m_size(static_cast<globjects::binding::GLint>(vertices.size()))
, m_primitiveMode(primitiveMode)
{
    m_vbo->setData(vertices);
}

template <typename T, std::size_t Count>
VertexDrawable::VertexDrawable(const std::array<T, Count> & vertices, globjects::binding::GLenum primitiveMode)
: m_vao(new globjects::VertexArray)
, m_vbo(new globjects::Buffer)
, m_baseOffset(0)
, m_stride(sizeof(T))
, m_size(static_cast<globjects::binding::GLint>(vertices.size()))
, m_primitiveMode(primitiveMode)
{
    m_vbo->setData(vertices, globjects::binding::GL_STATIC_DRAW);
}

template <typename T>
void VertexDrawable::setVertices(const std::vector<T> & vertices)
{
    m_vbo->setData(vertices, globjects::binding::GL_STATIC_DRAW);
}
