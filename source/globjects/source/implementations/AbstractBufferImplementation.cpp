
#include "AbstractBufferImplementation.h"

#include <globjects/binding/enum.h>

#include <globjects/globjects.h>

#ifdef GLOBJECTS_GL_BINDING
#include "BufferImplementation_DirectStateAccessARB.h"
#include "BufferImplementation_DirectStateAccessEXT.h"
#endif
#include "BufferImplementation_Legacy.h"


namespace globjects 
{

using namespace binding;

AbstractBufferImplementation::AbstractBufferImplementation()
{
}

AbstractBufferImplementation::~AbstractBufferImplementation()
{
}

AbstractBufferImplementation * AbstractBufferImplementation::get(const Buffer::BindlessImplementation impl)
{
#ifdef GLOBJECTS_GL_BINDING
    if (impl == Buffer::BindlessImplementation::DirectStateAccessARB 
     && hasExtension(GLextension::GL_ARB_direct_state_access))
    {
        return BufferImplementation_DirectStateAccessARB::instance();
    }
    else if (impl >= Buffer::BindlessImplementation::DirectStateAccessEXT 
      && hasExtension(GLextension::GL_EXT_direct_state_access))
    {
        return BufferImplementation_DirectStateAccessEXT::instance();
    }
    else
    {
        return BufferImplementation_Legacy::instance();
    }
#else
    (void) impl; // unsued

    return BufferImplementation_Legacy::instance();
#endif
}

} // namespace globjects
