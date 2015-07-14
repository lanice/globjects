#pragma once

#include <map>
#include <vector>

#include <globjects/binding/types.h>

#include <globjects/base/ref_ptr.h>

#include <globjects/globjects_api.h>
#include <globjects/Object.h>

namespace globjects 
{

class VertexAttributeBinding;


// http://www.opengl.org/wiki/Vertex_Array_Object
class GLOBJECTS_API VertexArray : public Object
{
public:
    enum class AttributeImplementation
    {
        DirectStateAccessARB
    ,   VertexAttribBindingARB
    ,   Legacy
    };

    static void hintAttributeImplementation(AttributeImplementation impl);

public:
    VertexArray();

    static VertexArray * fromId(binding::GLuint id);
    static VertexArray * defaultVAO();

    virtual void accept(ObjectVisitor & visitor) override;

    void bind() const;
    static void unbind();

    VertexAttributeBinding * binding(binding::GLuint bindingIndex);
    const VertexAttributeBinding * binding(binding::GLuint bindingIndex) const;

    void enable(binding::GLint attributeIndex);
    void disable(binding::GLint attributeIndex);

    std::vector<VertexAttributeBinding *> bindings();
    std::vector<const VertexAttributeBinding *> bindings() const;

    // drawing

    void drawArrays(binding::GLenum mode, binding::GLint first, binding::GLsizei count) const;
    void drawArraysInstanced(binding::GLenum mode, binding::GLint first, binding::GLsizei count, binding::GLsizei instanceCount) const;
    void drawArraysInstancedBaseInstance(binding::GLenum mode, binding::GLint first, binding::GLsizei count, binding::GLsizei instanceCount, binding::GLuint baseInstance) const;
    void drawArraysIndirect(binding::GLenum mode, const void * indirect = nullptr) const;

    void multiDrawArrays(binding::GLenum mode, binding::GLint * first, const binding::GLsizei * count, binding::GLsizei drawCount) const;
    void multiDrawArraysIndirect(binding::GLenum mode, const void * indirect, binding::GLsizei drawCount, binding::GLsizei stride) const;

    void drawElements(binding::GLenum mode, binding::GLsizei count, binding::GLenum type, const void * indices = nullptr) const;
    void drawElementsBaseVertex(binding::GLenum mode, binding::GLsizei count, binding::GLenum type, const void * indices, binding::GLint baseVertex) const;
    void drawElementsInstanced(binding::GLenum mode, binding::GLsizei count, binding::GLenum type, const void * indices, binding::GLsizei primitiveCount) const;
    void drawElementsInstancedBaseInstance(binding::GLenum mode, binding::GLsizei count, binding::GLenum type, const void * indices, binding::GLsizei instanceCount, binding::GLuint baseInstance) const;
    void drawElementsInstancedBaseVertex(binding::GLenum mode, binding::GLsizei count, binding::GLenum type, const void * indices, binding::GLsizei instanceCount, binding::GLint baseVertex) const;
    void drawElementsInstancedBaseVertexBaseInstance(binding::GLenum mode, binding::GLsizei count, binding::GLenum type, const void * indices, binding::GLsizei instanceCount, binding::GLint baseVertex, binding::GLuint baseInstance) const;

    void multiDrawElements(binding::GLenum mode, const binding::GLsizei * count, binding::GLenum type, const void ** indices, binding::GLsizei drawCount) const;
    void multiDrawElementsBaseVertex(binding::GLenum mode, const binding::GLsizei * count, binding::GLenum type, const void ** indices, binding::GLsizei drawCount, binding::GLint * baseVertex) const;
    void multiDrawElementsIndirect(binding::GLenum mode, binding::GLenum type, const void * indirect, binding::GLsizei drawCount, binding::GLsizei stride) const;

    void drawRangeElements(binding::GLenum mode, binding::GLuint start, binding::GLuint end, binding::GLsizei count, binding::GLenum type, const void * indices = nullptr) const;
    void drawRangeElementsBaseVertex(binding::GLenum mode, binding::GLuint start, binding::GLuint end, binding::GLsizei count, binding::GLenum type, const void * indices, binding::GLint baseVertex) const;

    // convenience
    struct MultiDrawArraysRange 
    { 
        binding::GLint first; 
        binding::GLsizei count; 
    };

    struct MultiDrawElementsRange 
    { 
        binding::GLsizei count; 
        void * indices; 
    };

    struct MultiDrawElementsBaseVertexRange 
    { 
        binding::GLsizei count;
        void * indices; 
        binding::GLint baseVertex; 
    };

    void multiDrawArrays(binding::GLenum mode, const std::vector<MultiDrawArraysRange> & ranges) const;
    void multiDrawElements(binding::GLenum mode, binding::GLenum type, const std::vector<MultiDrawElementsRange> & ranges) const;
    void multiDrawElementsBaseVertex(binding::GLenum mode, binding::GLenum type, const std::vector<MultiDrawElementsBaseVertexRange> & ranges) const;

#ifdef GLOBJECTS_GL_BINDING
    virtual binding::GLenum objectType() const override;
#endif

protected:
    VertexArray(IDResource * resource);
    virtual ~VertexArray();

protected:
    std::map<binding::GLuint, ref_ptr<VertexAttributeBinding>> m_bindings;

};

} // namespace globjects
