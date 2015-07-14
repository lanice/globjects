#include <globjects/globjects.h>

#include <unordered_map>
#include <mutex>

#include <khrapi/AbstractFunction.h>
#include <khrapi/callbacks.h>

#include <globjects/binding/functions.h>
#include <globjects/binding/enum.h>
#include <globjects/binding/Binding.h>
#include <globjects/binding/ContextInfo.h>
#include <globjects/binding/boolean.h>
#include <globjects/binding/Version.h>
#include <globjects/binding/bitfield.h>
#include <globjects/Error.h>
#include <globjects/logging.h>

#include "registry/Registry.h"
#include "registry/ObjectRegistry.h"
#include "registry/ExtensionRegistry.h"
#include "registry/ImplementationRegistry.h"

#include <globjects/DebugMessage.h>
#include <globjects/logging.h>

#include <globjects/NamedString.h>


namespace
{
    bool g_globjectsIsInitialized = false;
    std::mutex g_mutex;
}

namespace globjects
{

using namespace binding;

void manualErrorCheckAfter(const khrapi::AbstractFunction & function)
{
    Error error = Error::get();

    if (!error)
        return;

    if (!Registry::current().isInitialized())
    {
        debug() << "Error during initialization: " << error.name();
        return;
    }

    if (!DebugMessage::isFallbackImplementation())
        return;

    std::stringstream stream;
    stream << function.name() << " generated " << error.name();

#ifdef GLOBJECTS_GL_BINDING
    DebugMessage::insertMessage(GL_DEBUG_SOURCE_API_ARB, GL_DEBUG_TYPE_ERROR_ARB, static_cast<unsigned int>(error.code()), GL_DEBUG_SEVERITY_HIGH_ARB, stream.str());
#else
    DebugMessage::insertMessage(GL_DEBUG_SOURCE_API_KHR, GL_DEBUG_TYPE_ERROR_KHR, static_cast<unsigned int>(error.code()), GL_DEBUG_SEVERITY_HIGH_KHR, stream.str());
#endif
}

void init()
{
    g_mutex.lock();
    if (!g_globjectsIsInitialized)
    {
        khrapi::setAfterCallback([](const khrapi::FunctionCall & functionCall) {
            manualErrorCheckAfter(*functionCall.function); });

        g_globjectsIsInitialized = true;
    }

    g_mutex.unlock();

    registerCurrentContext();
}

void init(const binding::ContextHandle sharedContextId)
{
    g_mutex.lock();
    if (g_globjectsIsInitialized)
    {
        binding::Binding::setCallbackMaskExcept(khrapi::CallbackMask::After, { "glGetError" });

        khrapi::setAfterCallback([](const khrapi::FunctionCall & functionCall) {
            manualErrorCheckAfter(*functionCall.function); });

        g_globjectsIsInitialized = true;
    }
    g_mutex.unlock();

    registerCurrentContext(sharedContextId);
}

void detachAllObjects()
{
    for (Object * object : Registry::current().objects().objects())
        object->detach();
}

void registerCurrentContext()
{
    binding::ContextHandle contextId = binding::getCurrentContext();

    binding::Binding::useContext(contextId);
    Registry::registerContext(contextId);
}

void registerCurrentContext(const binding::ContextHandle sharedContextId)
{
    binding::ContextHandle contextId = binding::getCurrentContext();

    binding::Binding::useContext(contextId);
    Registry::registerContext(contextId, sharedContextId);
}

void setContext(const binding::ContextHandle contextId)
{
    binding::Binding::useContext(contextId);
    Registry::setCurrentContext(contextId);
}

void setCurrentContext()
{
    binding::ContextHandle contextId = binding::getCurrentContext();
    setContext(contextId);
}

std::string getString(const GLenum pname)
{
    const GLubyte* result = glGetString(pname);

	return reinterpret_cast<const char*>(result);
}

std::string getString(const GLenum pname, const GLuint index)
{
    const GLubyte* result = glGetStringi(pname, index);

    return reinterpret_cast<const char*>(result);
}

GLint getInteger(const GLenum pname)
{
	GLint value;

    glGetIntegerv(pname, &value);

	return value;
}

GLenum getEnum(const GLenum pname)
{
    return static_cast<GLenum>(getInteger(pname));
}

GLfloat getFloat(const GLenum pname)
{
	GLfloat value;

    glGetFloatv(pname, &value);

	return value;
}

#ifdef GLOBJECTS_GL_BINDING
GLdouble getDouble(const GLenum pname)
{
	GLdouble value;

    glGetDoublev(pname, &value);

	return value;
}
#endif

GLboolean getBoolean(const GLenum pname)
{
	GLboolean value;

    glGetBooleanv(pname, &value);

	return value;
}

GLint getInteger(const GLenum pname, const GLuint index)
{
	GLint value;

    glGetIntegeri_v(pname, index, &value);

	return value;
}

GLenum getEnum(const GLenum pname, const GLuint index)
{
    return static_cast<GLenum>(getInteger(pname, index));
}


GLfloat getFloat(const GLenum pname, const GLuint index)
{
    GLfloat value;

#ifdef GLOBJECTS_GL_BINDING
    glGetFloati_v(pname, index, &value);
#else
    glGetFloati_vNV(pname, index, &value);
#endif

    return value;
}

#ifdef GLOBJECTS_GL_BINDING
GLdouble getDouble(const GLenum pname, const GLuint index)
{
    GLdouble value;

    glGetDoublei_v(pname, index, &value);

    return value;
}
#endif

GLboolean getBoolean(const GLenum pname, const GLuint index)
{
    GLboolean value;

    glGetBooleani_v(pname, index, &value);

    return value;
}

std::string vendor()
{
    return binding::ContextInfo::vendor();
}

std::string renderer()
{
    return binding::ContextInfo::renderer();
}

std::string versionString()
{
    return getString(GL_VERSION);
}

binding::Version version()
{
    return binding::ContextInfo::version();
}

bool isCoreProfile()
{
#ifdef GLOBJECTS_GL_BINDING
    if (version()<binding::Version(3,2))
    {
        return false;
    }

    return (getInteger(GL_CONTEXT_PROFILE_MASK) & static_cast<unsigned>(GL_CONTEXT_CORE_PROFILE_BIT)) > 0;
#else
    return false;
#endif
}

bool isGL()
{
#ifdef GLOBJECTS_GL_BINDING
    return true;
#else
    return false;
#endif
}

bool isGLES()
{
#ifdef GLOBJECTS_GL_BINDING
    return false;
#else
    return true;
#endif
}

const std::set<GLextension> & availableExtensions()
{
    return ExtensionRegistry::current().availableExtensions();
}

const std::set<std::string> & unknownAvailableExtensions()
{
    return ExtensionRegistry::current().unknownAvailableExtensions();
}

bool hasExtension(const GLextension extension)
{
    return ExtensionRegistry::current().hasExtension(extension);
}

bool hasExtension(const std::string & extensionName)
{
    return ExtensionRegistry::current().hasExtension(extensionName);
}

#ifdef GLOBJECTS_GL_API
bool isInCoreProfile(const GLextension extension, const binding::Version & version)
{
    return ExtensionRegistry::current().isInCoreProfile(extension, version);
}

bool isInCoreProfile(const GLextension extension)
{
    return ExtensionRegistry::current().isInCoreProfile(extension);
}
#endif

void enable(const GLenum capability)
{
    glEnable(capability);
}

void disable(const GLenum capability)
{
    glDisable(capability);
}

bool isEnabled(const GLenum capability)
{
    GLboolean value = glIsEnabled(capability);

    return value == GL_TRUE;
}

void setEnabled(const GLenum capability, const bool enabled)
{
    enabled ? enable(capability) : disable(capability);
}

void enable(const GLenum capability, const int index)
{
#ifdef GLOBJECTS_GL_BINDING
    glEnablei(capability, index);
#else
    glEnableiEXT(capability, index);
#endif
}

void disable(const GLenum capability, const int index)
{
#ifdef GLOBJECTS_GL_BINDING
    glDisablei(capability, index);
#else
    glDisableiEXT(capability, index);
#endif
}

bool isEnabled(const GLenum capability, const int index)
{
#ifdef GLOBJECTS_GL_BINDING
    GLboolean value = glIsEnabledi(capability, index);
#else
    GLboolean value = glIsEnablediEXT(capability, index);
#endif

    return value == GL_TRUE;
}

void setEnabled(const GLenum capability, const int index, const bool enabled)
{
    enabled ? enable(capability, index) : disable(capability, index);
}

void initializeStrategy(const AbstractUniform::BindlessImplementation impl)
{
    Registry::current().implementations().initialize(impl);
}

void initializeStrategy(const Buffer::BindlessImplementation impl)
{
    Registry::current().implementations().initialize(impl);
}

void initializeStrategy(const Framebuffer::BindlessImplementation impl)
{
    Registry::current().implementations().initialize(impl);
}

void initializeStrategy(const DebugMessage::Implementation impl)
{
    Registry::current().implementations().initialize(impl);
}

void initializeStrategy(const Program::BinaryImplementation impl)
{
    Registry::current().implementations().initialize(impl);
}

void initializeStrategy(const Shader::IncludeImplementation impl)
{
    Registry::current().implementations().initialize(impl);
}

void initializeStrategy(const Object::NameImplementation impl)
{
    Registry::current().implementations().initialize(impl);
}

void initializeStrategy(const VertexArray::AttributeImplementation impl)
{
    Registry::current().implementations().initialize(impl);
}

} // namespace globjects
