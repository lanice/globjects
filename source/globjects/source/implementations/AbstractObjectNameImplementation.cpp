
#include "AbstractObjectNameImplementation.h"

#include <globjects/binding/enum.h>

#include <globjects/globjects.h>

#include <globjects/Object.h>
#include <globjects/Sync.h>

#ifdef GLOBJECTS_GL_BINDING
#include "ObjectNameImplementation_KHR_debug.h"
#endif
#include "ObjectNameImplementation_Legacy.h"

namespace globjects {

using namespace binding;

AbstractObjectNameImplementation::AbstractObjectNameImplementation()
{
}

AbstractObjectNameImplementation::~AbstractObjectNameImplementation()
{
}

AbstractObjectNameImplementation * AbstractObjectNameImplementation::get(const Object::NameImplementation impl)
{
#ifdef GLOBJECTS_GL_BINDING
    if (impl == Object::NameImplementation::DebugKHR
     && hasExtension(GLextension::GL_KHR_debug))
    {
        return ObjectNameImplementation_KHR_debug::instance();
    }
    else
    {
        return ObjectNameImplementation_Legacy::instance();
    }

#else
    (void) impl; // unused
    return ObjectNameImplementation_Legacy::instance();
#endif
}

void * AbstractObjectNameImplementation::objectLabelState(const Object * object) const
{
    return object->m_objectLabelState;
}

void * AbstractObjectNameImplementation::objectLabelState(const Sync * sync) const
{
    return sync->m_objectLabelState;
}

void AbstractObjectNameImplementation::setObjectLabelState(const Object * object, void * state) const
{
    object->m_objectLabelState = state;
}

void AbstractObjectNameImplementation::setObjectLabelState(const Sync * sync, void * state) const
{
    sync->m_objectLabelState = state;
}

} // namespace globjects
