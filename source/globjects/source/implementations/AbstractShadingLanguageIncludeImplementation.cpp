
#include "AbstractShadingLanguageIncludeImplementation.h"

#include <globjects/globjects.h>

#include <globjects/binding/extension.h>

#ifdef GLOBJECTS_GL_BINDING
#include "ShadingLanguageIncludeImplementation_ARB.h"
#endif
#include "ShadingLanguageIncludeImplementation_Fallback.h"


namespace globjects 
{

using namespace binding;

AbstractShadingLanguageIncludeImplementation::AbstractShadingLanguageIncludeImplementation()
{
}

AbstractShadingLanguageIncludeImplementation::~AbstractShadingLanguageIncludeImplementation()
{
}

AbstractShadingLanguageIncludeImplementation * AbstractShadingLanguageIncludeImplementation::get(const Shader::IncludeImplementation impl)
{
#ifdef GLOBJECTS_GL_BINDING
    if (impl == Shader::IncludeImplementation::ShadingLanguageIncludeARB 
     && hasExtension(GLextension::GL_ARB_shading_language_include))
    {
        return ShadingLanguageIncludeImplementation_ARB::instance();
    }
    else
    {
        return ShadingLanguageIncludeImplementation_Fallback::instance();
    }
#else
    (void) impl; // unused

    return ShadingLanguageIncludeImplementation_Fallback::instance();
#endif
}

std::vector<const char *> AbstractShadingLanguageIncludeImplementation::collectCStrings(const std::vector<std::string> & strings)
{
    std::vector<const char *> cStrings;

    for (const std::string & str : strings)
    {
        cStrings.push_back(str.c_str());
    }

    return cStrings;
}

} // namespace globjects
