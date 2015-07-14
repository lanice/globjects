#pragma once

#include <string>
#include <functional>

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>

namespace globjects 
{

class GLOBJECTS_API LocationIdentity
{
public:
    LocationIdentity();
    LocationIdentity(binding::GLint location);
    LocationIdentity(const std::string & name);

    bool isLocation() const;
    bool isName() const;

    binding::GLint location() const;
    const std::string & name() const;

    bool operator==(const LocationIdentity & identity) const;
    bool operator!=(const LocationIdentity & identity) const;

    bool operator<(const LocationIdentity & identity) const;

    std::size_t hash() const;

protected:
    bool m_invalid;

    binding::GLint m_location;

    std::string m_name;
    bool m_hasName;
};

} // namespace globjects


namespace std 
{

template <>
struct hash<globjects::LocationIdentity>
{
    std::size_t operator()(const globjects::LocationIdentity & identity) const
    {
        return identity.hash();
    }
};

} // namespace globjects

