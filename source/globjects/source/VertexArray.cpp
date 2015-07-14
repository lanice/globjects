#include <globjects/VertexArray.h>

#include <cassert>

#include <globjects/binding/functions.h>
#include <globjects/binding/enum.h>

#include <globjects/ObjectVisitor.h>
#include <globjects/VertexAttributeBinding.h>

#include "registry/ImplementationRegistry.h"
#include "implementations/AbstractVertexAttributeBindingImplementation.h"

#include "container_helpers.hpp"
#include "registry/ObjectRegistry.h"

#include "Resource.h"


namespace 
{
    globjects::AbstractVertexAttributeBindingImplementation & implementation()
    {
        return globjects::ImplementationRegistry::current().attributeImplementation();
    }
}

namespace globjects
{

using namespace binding;

VertexArray::VertexArray()
: Object(new VertexArrayObjectResource)
{
}

VertexArray::VertexArray(IDResource * resource)
: Object(resource)
{
}

void VertexArray::hintAttributeImplementation(const AttributeImplementation impl)
{
    ImplementationRegistry::current().initialize(impl);
}

VertexArray * VertexArray::fromId(const GLuint id)
{
    return new VertexArray(new ExternalResource(id));
}

VertexArray * VertexArray::defaultVAO()
{
    return ObjectRegistry::current().defaultVAO();
}

VertexArray::~VertexArray()
{
}

void VertexArray::accept(ObjectVisitor & visitor)
{
    visitor.visitVertexArray(this);
}

void VertexArray::bind() const
{
	glBindVertexArray(id());
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

VertexAttributeBinding * VertexArray::binding(const GLuint bindingIndex)
{
	if (!m_bindings[bindingIndex])
        m_bindings[bindingIndex] = new VertexAttributeBinding(this, bindingIndex);

    return m_bindings[bindingIndex];
}

const VertexAttributeBinding* VertexArray::binding(const GLuint bindingIndex) const
{
    if (m_bindings.count(bindingIndex))
        return m_bindings.at(bindingIndex);

    return nullptr;
}

void VertexArray::enable(GLint attributeIndex)
{
    implementation().enable(this, attributeIndex);
}

void VertexArray::disable(GLint attributeIndex)
{
    implementation().disable(this, attributeIndex);
}

std::vector<VertexAttributeBinding *> VertexArray::bindings()
{
	std::vector<VertexAttributeBinding *> bindings;

    for (std::pair<GLuint, ref_ptr<VertexAttributeBinding>> pair: m_bindings)
		bindings.push_back(pair.second);

	return bindings;
}

std::vector<const VertexAttributeBinding*> VertexArray::bindings() const
{
    std::vector<const VertexAttributeBinding*> bindings;

    for (std::pair<GLuint, ref_ptr<VertexAttributeBinding>> pair: m_bindings)
    {
        bindings.push_back(pair.second);
    }

    return bindings;
}

void VertexArray::drawArrays(const GLenum mode, const GLint first, const GLsizei count) const
{
    bind();
    glDrawArrays(mode, first, count);
}

void VertexArray::drawArraysInstanced(const GLenum mode, const GLint first, const GLsizei count, const GLsizei instanceCount) const
{
    bind();
    glDrawArraysInstanced(mode, first, count, instanceCount);
}

void VertexArray::drawArraysInstancedBaseInstance(const GLenum mode, const GLint first, const GLsizei count, const GLsizei instanceCount, const GLuint baseInstance) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glDrawArraysInstancedBaseInstance(mode, first, count, instanceCount, baseInstance);
#else
    glDrawArraysInstancedBaseInstanceEXT(mode, first, count, instanceCount, baseInstance);
#endif
}

void VertexArray::drawArraysIndirect(const GLenum mode, const void* indirect) const
{
    assert(indirect != nullptr);

    bind();
    glDrawArraysIndirect(mode, indirect);
}

void VertexArray::multiDrawArrays(const GLenum mode, GLint* first, const GLsizei* count, const GLsizei drawCount) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glMultiDrawArrays(mode, first, count, drawCount);
#else
    glMultiDrawArraysEXT(mode, first, count, drawCount);
#endif
}

void VertexArray::multiDrawArraysIndirect(const GLenum mode, const void* indirect, const GLsizei drawCount, const GLsizei stride) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glMultiDrawArraysIndirect(mode, indirect, drawCount, stride);
#else
    glMultiDrawArraysIndirectEXT(mode, indirect, drawCount, stride);
#endif
}

void VertexArray::drawElements(const GLenum mode, const GLsizei count, const GLenum type, const void * indices) const
{
    bind();
    glDrawElements(mode, count, type, indices);
}

void VertexArray::drawElementsBaseVertex(const GLenum mode, const GLsizei count, const GLenum type, const void* indices, const GLint baseVertex) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glDrawElementsBaseVertex(mode, count, type, const_cast<void *>(indices), baseVertex);
#else
    glDrawElementsBaseVertexEXT(mode, count, type, const_cast<void *>(indices), baseVertex);
#endif
}

void VertexArray::drawElementsInstanced(const GLenum mode, const GLsizei count, const GLenum type, const void* indices, const GLsizei primitiveCount) const
{
    bind();
    glDrawElementsInstanced(mode, count, type, indices, primitiveCount);
}

void VertexArray::drawElementsInstancedBaseInstance(const GLenum mode, const GLsizei count, const GLenum type, const void* indices, const GLsizei instanceCount, const GLuint baseInstance) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glDrawElementsInstancedBaseInstance(mode, count, type, indices, instanceCount, baseInstance);
#else
    glDrawElementsInstancedBaseInstanceEXT(mode, count, type, indices, instanceCount, baseInstance);
#endif
}

void VertexArray::drawElementsInstancedBaseVertex(const GLenum mode, const GLsizei count, const GLenum type, const void* indices, const GLsizei instanceCount, const GLint baseVertex) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glDrawElementsInstancedBaseVertex(mode, count, type, indices, instanceCount, baseVertex);
#else
    glDrawElementsInstancedBaseVertexEXT(mode, count, type, indices, instanceCount, baseVertex);
#endif
}

void VertexArray::drawElementsInstancedBaseVertexBaseInstance(const GLenum mode, const GLsizei count, const GLenum type, const void* indices, const GLsizei instanceCount, const GLint baseVertex, const GLuint baseInstance) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instanceCount, baseVertex, baseInstance);
#else
    glDrawElementsInstancedBaseVertexBaseInstanceEXT(mode, count, type, indices, instanceCount, baseVertex, baseInstance);
#endif
}

void VertexArray::multiDrawElements(const GLenum mode, const GLsizei* count, const GLenum type, const void** indices, const GLsizei drawCount) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glMultiDrawElements(mode, count, type, indices, drawCount);
#else
    glMultiDrawElementsEXT(mode, count, type, indices, drawCount);
#endif
}

void VertexArray::multiDrawElementsBaseVertex(const GLenum mode, const GLsizei* count, const GLenum type, const void** indices, const GLsizei drawCount, GLint* baseVertex) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glMultiDrawElementsBaseVertex(mode, const_cast<GLsizei*>(count), type, const_cast<void**>(indices), drawCount, baseVertex);
#else
    glMultiDrawElementsBaseVertexEXT(mode, count, type, indices, drawCount, baseVertex);
#endif
}

void VertexArray::multiDrawElementsIndirect(const GLenum mode, const GLenum type, const void* indirect, const GLsizei drawCount, const GLsizei stride) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glMultiDrawElementsIndirect(mode, type, indirect, drawCount, stride);
#else
    glMultiDrawElementsIndirectEXT(mode, type, indirect, drawCount, stride);
#endif
}

void VertexArray::drawRangeElements(const GLenum mode, const GLuint start, const GLuint end, const GLsizei count, const GLenum type, const void* indices) const
{
    bind();
    glDrawRangeElements(mode, start, end, count, type, indices);
}

void VertexArray::drawRangeElementsBaseVertex(const GLenum mode, const GLuint start, const GLuint end, const GLsizei count, const GLenum type, const void* indices, const GLint baseVertex) const
{
    bind();

#ifdef GLOBJECTS_GL_BINDING
    glDrawRangeElementsBaseVertex(mode, start, end, count, type, const_cast<void*>(indices), baseVertex);
#else
    glDrawRangeElementsBaseVertexEXT(mode, start, end, count, type, indices, baseVertex);
#endif
}

void VertexArray::multiDrawArrays(const GLenum mode, const std::vector<VertexArray::MultiDrawArraysRange> & ranges) const
{
    std::vector<GLint> firsts = collect_member(ranges, MultiDrawArraysRange, first);
    std::vector<GLsizei> counts = collect_member(ranges, MultiDrawArraysRange, count);

    multiDrawArrays(mode, firsts.data(), counts.data(), static_cast<GLsizei>(ranges.size()));
}

void VertexArray::multiDrawElements(const GLenum mode, const GLenum type, const std::vector<VertexArray::MultiDrawElementsRange> & ranges) const
{
    std::vector<GLsizei> counts = collect_member(ranges, MultiDrawElementsRange, count);
    std::vector<const void*> indices = collect_type_member(const void*, ranges, MultiDrawElementsRange, indices);

    multiDrawElements(mode, counts.data(), type, indices.data(), static_cast<GLsizei>(ranges.size()));
}

void VertexArray::multiDrawElementsBaseVertex(const GLenum mode, const GLenum type, const std::vector<VertexArray::MultiDrawElementsBaseVertexRange> & ranges) const
{
    std::vector<GLsizei> counts = collect_member(ranges, MultiDrawElementsBaseVertexRange, count);
    std::vector<const void*> indices = collect_type_member(const void*, ranges, MultiDrawElementsBaseVertexRange, indices);
    std::vector<GLint> baseVertices = collect_member(ranges, MultiDrawElementsBaseVertexRange, baseVertex);

    multiDrawElementsBaseVertex(mode, counts.data(), type, indices.data(), static_cast<GLsizei>(ranges.size()), baseVertices.data());
}

#ifdef GLOBJECTS_GL_BINDING
GLenum VertexArray::objectType() const
{
    return GL_VERTEX_ARRAY;
}
#endif

} // namespace globjects
