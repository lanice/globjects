#pragma once

#include <globjects/globjects.h>

#include <utility>

#include <globjects/binding/types.h>
#include <globjects/binding/functions.h>

namespace globjects 
{

template <int Count>
std::array<binding::GLint, Count> getIntegers(const binding::GLenum pname)
{
    std::array<binding::GLint, Count> values;

    binding::glGetIntegerv(pname, reinterpret_cast<binding::GLint*>(&values));

    return values;
}

template <int Count>
std::array<binding::GLenum, Count> getEnums(const binding::GLenum pname)
{
    std::array<binding::GLenum, Count> values;

    binding::glGetIntegerv(pname, reinterpret_cast<binding::GLint*>(&values));

    return values;
}

template <int Count>
std::array<binding::GLfloat, Count> getFloats(const binding::GLenum pname)
{
    std::array<binding::GLfloat, Count> values;

    binding::glGetFloatv(pname, reinterpret_cast<binding::GLfloat*>(&values));

    return values;
}

#ifdef GLOBJECTS_GL_BINDING
template <int Count>
std::array<binding::GLdouble, Count> getDoubles(const binding::GLenum pname)
{
    std::array<binding::GLdouble, Count> values;

    binding::glGetDoublev(pname, reinterpret_cast<binding::GLdouble*>(&values));

    return values;
}
#endif

template <int Count>
std::array<binding::GLboolean, Count> getBooleans(const binding::GLenum pname)
{
    std::array<binding::GLboolean, Count> values;

    binding::glGetBooleanv(pname, reinterpret_cast<binding::GLboolean*>(&values));

    return values;
}

template <typename T, typename... Args>
void init(T strategy, Args... args)
{
    init(args...);

    initializeStrategy(strategy);
}

template <typename T, typename... Args>
void init(const binding::ContextHandle sharedContextId, T strategy, Args... args)
{
    init(sharedContextId, args...);

    initializeStrategy(strategy);
}

} // namespace globjects
