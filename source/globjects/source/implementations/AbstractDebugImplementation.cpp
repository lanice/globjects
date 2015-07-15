
#include "AbstractDebugImplementation.h"

#include <globjects/globjects.h>
#include <globjects/logging.h>

#include <globjects/binding/enum.h>

#ifdef GLOBJECTS_GL_BINDING
#include "DebugImplementation_DebugKHR.h"
#endif

#include "DebugImplementation_Legacy.h"

#ifdef GLOBJECTS_GL_ERROR_RAISE_EXCEPTION
#include <stdexcept>
#endif


namespace globjects 
{

using namespace binding;

DebugMessage::Callback AbstractDebugImplementation::s_defaultCallback = [](const DebugMessage & message) 
{
#ifdef GLOBJECTS_GL_BINDING
    if (message.type() == GL_DEBUG_TYPE_ERROR_ARB)
#else
    if (message.type() == GL_DEBUG_TYPE_ERROR_KHR)
#endif
    {
#ifdef GLOBJECTS_GL_ERROR_RAISE_EXCEPTION
        throw std::runtime_error(message.toString());
#else
        fatal() << message.toString();
#endif
    }
#ifdef GLOBJECTS_GL_BINDING
    else if (message.type() != GL_DEBUG_TYPE_OTHER)
#else
    else if (message.type() != GL_DEBUG_TYPE_OTHER_KHR)
#endif
    {
        debug() << message.toString();
    }
};

AbstractDebugImplementation::AbstractDebugImplementation()
: m_messageCallback(s_defaultCallback)
{
}

AbstractDebugImplementation::~AbstractDebugImplementation()
{
}

AbstractDebugImplementation * AbstractDebugImplementation::get(const DebugMessage::Implementation impl)
{
#ifdef GLOBJECTS_GL_BINDING
    if (impl == DebugMessage::Implementation::DebugKHR 
     && hasExtension(GLextension::GL_KHR_debug))
    {
        return DebugImplementation_DebugKHR::instance();
    }
    else
    {
        return DebugImplementation_Legacy::instance();
    }
#else
    (void) impl; // unused
    return DebugImplementation_Legacy::instance();
#endif
}

bool AbstractDebugImplementation::isFallback()
{
    return false;
}

void AbstractDebugImplementation::setCallback(DebugMessage::Callback callback)
{
    m_messageCallback = callback;
}

void AbstractDebugImplementation::handleMessage(const DebugMessage & message) const
{
    m_messageCallback(message);
}

} // namespace globjects
