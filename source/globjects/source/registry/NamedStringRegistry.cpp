#include "NamedStringRegistry.h"
#include "Registry.h"

#include <globjects/logging.h>
#include <globjects/NamedString.h>

#include <globjects/globjects.h>


namespace globjects 
{

using namespace binding;

NamedStringRegistry::NamedStringRegistry()
{
}

NamedStringRegistry & NamedStringRegistry::current()
{
    return Registry::current().namedStrings();
}

bool NamedStringRegistry::hasNamedString(const std::string & name)
{
    return m_namedStrings.find(name) != m_namedStrings.end();
}

NamedString * NamedStringRegistry::namedString(const std::string & name)
{
    auto it = m_namedStrings.find(name);

    return it == m_namedStrings.end() ? nullptr : it->second;
}

void NamedStringRegistry::registerNamedString(NamedString * namedString)
{
    if (hasNamedString(namedString->name()))
    {
        warning() << "Registering NamedString with existing name " << namedString->name();
    }

    m_namedStrings[namedString->name()] = namedString;
}

void NamedStringRegistry::deregisterNamedString(NamedString * namedString)
{
    m_namedStrings.erase(namedString->name());
}

bool NamedStringRegistry::hasNativeSupport()
{
#ifdef GLOBJECTS_GL_BINDING
    return hasExtension(GLextension::GL_ARB_shading_language_include);
#else
    return false;
#endif
}

} // namespace globjects
