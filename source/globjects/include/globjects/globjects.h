#pragma once

#include <string>
#include <vector>
#include <array>
#include <set>

#include <globjects/binding/types.h>
#include <globjects/binding/extension.h>
#include <globjects/binding/VersionFwd.h>
#include <globjects/binding/ContextHandle.h>

#include <globjects/globjects_api.h>

#include <globjects/AbstractUniform.h>
#include <globjects/Buffer.h>
#include <globjects/Framebuffer.h>
#include <globjects/DebugMessage.h>
#include <globjects/Program.h>
#include <globjects/Shader.h>
#include <globjects/Object.h>
#include <globjects/VertexArray.h>

namespace globjects 
{

GLOBJECTS_API void init();
GLOBJECTS_API void init(binding::ContextHandle sharedContextId);

/** \brief calls detach on every registered object
    
    This only releases the GPU counterparts of all  objects, 
    while leaving the ref_ptred objects in memory, invalidated.
*/
GLOBJECTS_API void detachAllObjects();

template <typename T, typename... Args>
void init(T strategy, Args... args);

template <typename T, typename... Args>
void init(binding::ContextHandle sharedContextId, T strategy, Args... args);

GLOBJECTS_API void registerCurrentContext();
GLOBJECTS_API void registerCurrentContext(binding::ContextHandle sharedContextId);
GLOBJECTS_API void setContext(binding::ContextHandle contextId);
GLOBJECTS_API void setCurrentContext();

GLOBJECTS_API std::string getString(binding::GLenum pname);
GLOBJECTS_API std::string getString(binding::GLenum pname, binding::GLuint index);

GLOBJECTS_API binding::GLint getInteger(binding::GLenum pname);
GLOBJECTS_API binding::GLenum getEnum(binding::GLenum pname);
GLOBJECTS_API binding::GLfloat getFloat(binding::GLenum pname);

#ifdef GLOBJECTS_GL_BINDING
GLOBJECTS_API binding::GLdouble getDouble(binding::GLenum pname);
#endif

GLOBJECTS_API binding::GLboolean getBoolean(binding::GLenum pname);

GLOBJECTS_API binding::GLint getInteger(binding::GLenum pname, binding::GLuint index);
GLOBJECTS_API binding::GLenum getEnum(binding::GLenum pname, binding::GLuint index);
GLOBJECTS_API binding::GLfloat getFloat(binding::GLenum pname, binding::GLuint index);

#ifdef GLOBJECTS_GL_BINDING
GLOBJECTS_API binding::GLdouble getDouble(binding::GLenum pname, binding::GLuint index);
#endif
GLOBJECTS_API binding::GLboolean getBoolean(binding::GLenum pname, binding::GLuint index);

GLOBJECTS_API std::string vendor();
GLOBJECTS_API std::string renderer();
GLOBJECTS_API std::string versionString();
GLOBJECTS_API binding::Version version();
GLOBJECTS_API bool isCoreProfile();
GLOBJECTS_API bool isGL();
GLOBJECTS_API bool isGLES();

template <int Count>
std::array<binding::GLint, Count> getIntegers(binding::GLenum pname);
template <int Count>
std::array<binding::GLenum, Count> getEnums(binding::GLenum pname);
template <int Count>
std::array<binding::GLfloat, Count> getFloats(binding::GLenum pname);
template <int Count>
std::array<binding::GLdouble, Count> getDoubles(binding::GLenum pname);
template <int Count>
std::array<binding::GLboolean, Count> getBooleans(binding::GLenum pname);

GLOBJECTS_API const std::set<binding::GLextension> & availableExtensions();
GLOBJECTS_API const std::set<std::string> & unknownAvailableExtensions();

GLOBJECTS_API bool hasExtension(binding::GLextension extension);
GLOBJECTS_API bool hasExtension(const std::string & extensionName);

#ifdef GLOBJECTS_GL_API
GLOBJECTS_API bool isInCoreProfile(binding::GLextension extension, const binding::Version & version);
GLOBJECTS_API bool isInCoreProfile(binding::GLextension extension);
#endif

GLOBJECTS_API void enable(binding::GLenum capability);
GLOBJECTS_API void disable(binding::GLenum capability);
GLOBJECTS_API bool isEnabled(binding::GLenum capability);
GLOBJECTS_API void setEnabled(binding::GLenum capability, bool enabled);
GLOBJECTS_API void enable(binding::GLenum capability, int index);
GLOBJECTS_API void disable(binding::GLenum capability, int index);
GLOBJECTS_API bool isEnabled(binding::GLenum capability, int index);
GLOBJECTS_API void setEnabled(binding::GLenum capability, int index, bool enabled);

GLOBJECTS_API void initializeStrategy(AbstractUniform::BindlessImplementation impl);
GLOBJECTS_API void initializeStrategy(Buffer::BindlessImplementation impl);
GLOBJECTS_API void initializeStrategy(Framebuffer::BindlessImplementation impl);
GLOBJECTS_API void initializeStrategy(DebugMessage::Implementation impl);
GLOBJECTS_API void initializeStrategy(Program::BinaryImplementation impl);
GLOBJECTS_API void initializeStrategy(Shader::IncludeImplementation impl);
GLOBJECTS_API void initializeStrategy(Object::NameImplementation impl);
GLOBJECTS_API void initializeStrategy(VertexArray::AttributeImplementation impl);

} // namespace globjects

#include <globjects/globjects.hpp>
