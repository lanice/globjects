#pragma once

#include <set>
#include <string>

#include <globjects/binding/extension.h>
#include <globjects/binding/VersionFwd.h>

namespace globjects
{

class ExtensionRegistry
{
public:
    ExtensionRegistry();
    static ExtensionRegistry & current();

    std::set<binding::GLextension>::iterator begin();
    std::set<binding::GLextension>::iterator end();

    const std::set<binding::GLextension> & availableExtensions();
    const std::set<std::string> & unknownAvailableExtensions();

    bool hasExtension(binding::GLextension extension);
    bool hasExtension(const std::string & extensionName);

#ifdef GLOBJECTS_GL_BINDING
    bool isInCoreProfile(binding::GLextension extension);
    bool isInCoreProfile(binding::GLextension extension, const binding::Version & version);
#endif
protected:
    bool m_initialized;
    std::set<binding::GLextension> m_availableExtensions;
    std::set<std::string> m_unknownAvailableExtensions;

    void initialize();
};

} // namespace globjects
