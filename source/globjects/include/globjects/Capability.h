#pragma once

#include <map>

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>

namespace globjects
{

class GLOBJECTS_API Capability
{
public:
    Capability(binding::GLenum capability);
    Capability(binding::GLenum capability, bool enabled);

    binding::GLenum capability() const;

    void enable();
    void disable();
    bool isEnabled() const;

    void enable(int index);
    void disable(int index);
    bool isEnabled(int index) const;

    void apply();

protected:
    binding::GLenum m_capability;

    bool m_enabled;
    std::map<int, bool> m_indexEnabled;
};

} // namespace globjects
