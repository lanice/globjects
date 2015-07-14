
#include "ShadingLanguageIncludeImplementation_ARB.h"

#include <globjects/binding/functions.h>

#include <globjects/Shader.h>

#include <globjects/base/AbstractStringSource.h>


namespace globjects 
{

using namespace binding;

void ShadingLanguageIncludeImplementation_ARB::updateSources(const Shader * shader) const
{
    std::vector<std::string> sources;

    if (shader->source())
        sources = shader->source()->strings();

    std::vector<const char*> cStrings = collectCStrings(sources);

    glShaderSource(shader->id(), static_cast<GLint>(cStrings.size()), cStrings.data(), nullptr);
}

void ShadingLanguageIncludeImplementation_ARB::compile(const Shader * shader) const
{
    std::vector<const char*> cStrings = collectCStrings(shader->includePaths());
    glCompileShaderIncludeARB(shader->id(), static_cast<GLint>(cStrings.size()), cStrings.data(), nullptr);
}

} // namespace globjects
