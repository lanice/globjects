#pragma once

#include <vector>

#include <globjects/globjects_api.h>
#include <globjects/LocationIdentity.h>

namespace globjects 
{

class Program;

class GLOBJECTS_API UniformBlock
{
    friend class Program;
public:
    UniformBlock();
    UniformBlock(const Program * program, const LocationIdentity & m_identity);

    const LocationIdentity & identity() const;

    void setBinding(binding::GLuint bindingIndex);

    void getActive(binding::GLenum pname, binding::GLint * params) const;
    binding::GLint getActive(binding::GLenum pname) const;
    std::vector<binding::GLint> getActive(binding::GLenum pname, binding::GLint paramCount) const;

    std::vector<binding::GLint> getActiveUniformIndices() const;

    std::string getName() const;

protected:
    const Program * m_program;
    LocationIdentity m_identity;
    binding::GLuint m_bindingIndex;

    binding::GLuint blockIndex() const;
    void updateBinding() const;
};

} // namespace globjects
