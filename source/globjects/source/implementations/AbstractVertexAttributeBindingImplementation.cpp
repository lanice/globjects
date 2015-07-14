#include "AbstractVertexAttributeBindingImplementation.h"

#include <globjects/binding/functions.h>
#include <globjects/binding/extension.h>

#include <globjects/globjects.h>

#ifdef GLOBJECTS_GL_BINDING
#include "VertexAttributeBindingImplementation_DirectStateAccessARB.h"
#include "VertexAttributeBindingImplementation_VertexAttribBindingARB.h"
#endif
#include "VertexAttributeBindingImplementation_Legacy.h"

#include <globjects/VertexAttributeBinding.h>

namespace globjects 
{

using namespace binding;

AbstractVertexAttributeBindingImplementation::AbstractVertexAttributeBindingImplementation()
{
}

AbstractVertexAttributeBindingImplementation::~AbstractVertexAttributeBindingImplementation()
{
}

AbstractVertexAttributeBindingImplementation * AbstractVertexAttributeBindingImplementation::get(const VertexArray::AttributeImplementation impl)
{
#ifdef GLOBJECTS_GL_BINDING
    if (impl == VertexArray::AttributeImplementation::DirectStateAccessARB
     && hasExtension(GLextension::GL_ARB_direct_state_access))
    {
        return VertexAttributeBindingImplementation_DirectStateAccessARB::instance();
    }
    else if (impl == VertexArray::AttributeImplementation::VertexAttribBindingARB
     && hasExtension(GLextension::GL_ARB_vertex_attrib_binding))
    {
        return VertexAttributeBindingImplementation_VertexAttribBindingARB::instance();
    }
    else
    {
        return VertexAttributeBindingImplementation_Legacy::instance();
    }
#else
    (void) impl; // unused

    return VertexAttributeBindingImplementation_Legacy::instance();
#endif
}

GLint AbstractVertexAttributeBindingImplementation::attributeIndex(const VertexAttributeBinding * binding) const
{
    return binding->attributeIndex();
}

GLint AbstractVertexAttributeBindingImplementation::bindingIndex(const VertexAttributeBinding * binding) const
{
    return binding->bindingIndex();
}

const VertexArray * AbstractVertexAttributeBindingImplementation::vao(const VertexAttributeBinding * binding) const
{
    return binding->vao();
}

const Buffer * AbstractVertexAttributeBindingImplementation::vbo(const VertexAttributeBinding * binding) const
{
    return binding->buffer();
}

void * & AbstractVertexAttributeBindingImplementation::bindingData(const VertexAttributeBinding * binding) const
{
    return binding->m_bindingData;
}

} // namespace globjects
