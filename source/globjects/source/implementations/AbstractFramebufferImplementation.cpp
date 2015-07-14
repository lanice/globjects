
#include "AbstractFramebufferImplementation.h"

#include <globjects/binding/enum.h>

#include <globjects/globjects.h>

#ifdef GLOBJECTS_GL_BINDING
#include "FramebufferImplementation_DirectStateAccessARB.h"
#include "FramebufferImplementation_DirectStateAccessEXT.h"
#endif
#include "FramebufferImplementation_Legacy.h"


namespace globjects 
{

using namespace binding;
    
GLenum AbstractFramebufferImplementation::s_workingTarget = GL_FRAMEBUFFER;

AbstractFramebufferImplementation::AbstractFramebufferImplementation()
{
}

AbstractFramebufferImplementation::~AbstractFramebufferImplementation()
{
}

AbstractFramebufferImplementation * AbstractFramebufferImplementation::get(const Framebuffer::BindlessImplementation impl)
{
#ifdef GLOBJECTS_GL_BINDING
    if (impl == Framebuffer::BindlessImplementation::DirectStateAccessARB
     && hasExtension(GLextension::GL_ARB_direct_state_access))
    {
        return FramebufferImplementation_DirectStateAccessARB::instance();
    }
    else if (impl == Framebuffer::BindlessImplementation::DirectStateAccessEXT
     && hasExtension(GLextension::GL_EXT_direct_state_access))
    {
        return FramebufferImplementation_DirectStateAccessEXT::instance();
    }
    else
    {
        return FramebufferImplementation_Legacy::instance();
    }
#else
    (void) impl; // unused

    return FramebufferImplementation_Legacy::instance();
#endif
}

} // namespace globjects
