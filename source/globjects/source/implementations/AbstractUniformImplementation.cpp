
#include "AbstractUniformImplementation.h"

#include <globjects/globjects.h>

#ifdef GLOBJECTS_GL_BINDING
#include "UniformImplementation_SeparateShaderObjectsARB.h"
#endif
#include "UniformImplementation_Legacy.h"


namespace globjects 
{

using namespace binding;

AbstractUniformImplementation::AbstractUniformImplementation()
{
}

AbstractUniformImplementation::~AbstractUniformImplementation()
{
}

AbstractUniformImplementation * AbstractUniformImplementation::get(const AbstractUniform::BindlessImplementation impl)
{
#ifdef GLOBJECTS_GL_BINDING
    if (impl == AbstractUniform::BindlessImplementation::SeparateShaderObjectsARB 
     && hasExtension(GLextension::GL_ARB_separate_shader_objects))
    {
        return UniformImplementation_SeparateShaderObjectsARB::instance();
    }
    else
    {
        return UniformImplementation_Legacy::instance();
    }
#else
    (void) impl; // unused

    return UniformImplementation_Legacy::instance();
#endif
}

} // namespace globjects
