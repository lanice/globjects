#include "ExtensionRegistry.h"
#include "Registry.h"

#include <globjects/binding/Meta.h>
#include <globjects/binding/ContextInfo.h>
#include <globjects/binding/Version.h>

#include <globjects/globjects.h>

namespace globjects 
{

using namespace binding;

ExtensionRegistry::ExtensionRegistry()
: m_initialized(false)
{
}

ExtensionRegistry & ExtensionRegistry::current()
{
    return Registry::current().extensions();
}


std::set<GLextension>::iterator ExtensionRegistry::begin()
{
    return availableExtensions().begin();
}

std::set<GLextension>::iterator ExtensionRegistry::end()
{
    return availableExtensions().end();
}

const std::set<GLextension> & ExtensionRegistry::availableExtensions()
{
    initialize();
    return m_availableExtensions;
}

const std::set<std::string> & ExtensionRegistry::unknownAvailableExtensions()
{
    initialize();
    return m_unknownAvailableExtensions;
}

void ExtensionRegistry::initialize()
{
    if (m_initialized)
        return;

    m_availableExtensions = binding::ContextInfo::extensions(&m_unknownAvailableExtensions);

    m_initialized = true;
}

bool ExtensionRegistry::hasExtension(GLextension extension)
{
    initialize();

#ifdef GLOBJECTS_GL_BINDING
    if (isInCoreProfile(extension))
        return true;
#endif

    return m_availableExtensions.find(extension) != m_availableExtensions.end();
}

bool ExtensionRegistry::hasExtension(const std::string & extensionName)
{
    initialize();

    GLextension extension = binding::Meta::getExtension(extensionName);

    if (extension != GLextension::UNKNOWN)
    {
        return hasExtension(extension);
    }
    else
    {
        return m_unknownAvailableExtensions.find(extensionName) != m_unknownAvailableExtensions.end();
    }
}

#ifdef GLOBJECTS_GL_BINDING
binding::Version getCoreVersion(GLextension extension)
{
    return binding::Meta::getRequiringVersion(extension);
}

bool ExtensionRegistry::isInCoreProfile(GLextension extension, const binding::Version & version)
{
    binding::Version coreVersion = getCoreVersion(extension);

    if (!coreVersion.isValid())
        return false;

    return coreVersion <= version;
}


bool ExtensionRegistry::isInCoreProfile(GLextension extension)
{
    return isInCoreProfile(extension, globjects::version());
}
#endif

} // namespace globjects

