
#include "DebugImplementation_Legacy.h"

#include <khrapi/callbacks.h>

#include <globjects/binding/Binding.h>


namespace globjects 
{

using namespace binding;

DebugImplementation_Legacy::DebugImplementation_Legacy()
: m_enabled(false)
{
}

bool DebugImplementation_Legacy::isFallback()
{
    return true;
}

void DebugImplementation_Legacy::enable()
{
    m_enabled = true;

    binding::Binding::setCallbackMaskExcept(khrapi::CallbackMask::After, { "glGetError" });
}

void DebugImplementation_Legacy::disable()
{
    m_enabled = false;

    binding::Binding::setCallbackMask(khrapi::CallbackMask::None);
}

void DebugImplementation_Legacy::setSynchronous(bool)
{
    // ignore
}

void DebugImplementation_Legacy::insertMessage(const DebugMessage & message)
{
    if (m_enabled)
    {
        handleMessage(message);
    }
}

void DebugImplementation_Legacy::controlMessages(GLenum , GLenum , GLenum , GLsizei , const GLuint *, GLboolean )
{
    // ignore
    // TODO: emulate OpenGL's filtering functionality
}

} // namespace globjects
