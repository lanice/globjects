#pragma once

#include <string>
#include <vector>

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>


namespace globjects
{

class GLOBJECTS_API DebugMessage
{
public:
    enum class Implementation
    {
        DebugKHR
    ,   Legacy
    };

    static void hintImplementation(Implementation impl);

public:
    using Callback = std::function<void(const DebugMessage &)>;

    DebugMessage(binding::GLenum source, binding::GLenum type, binding::GLuint id, binding::GLenum severity, const std::string & message);

    binding::GLenum source() const;
    binding::GLenum type() const;
    binding::GLuint id() const;
    binding::GLenum severity() const;
    const std::string & message() const;

    virtual std::string toString() const;

protected:
    binding::GLenum m_source;
    binding::GLenum m_type;
    binding::GLuint m_id;
    binding::GLenum m_severity;
    std::string m_message;

    std::string severityString() const;
    std::string sourceString() const;
    std::string typeString() const;

public:
    static void enable(bool synchronous = true);
    static void disable();

    static void setCallback(Callback callback);

    static void setSynchronous(bool synchronous);

    static void insertMessage(binding::GLenum source, binding::GLenum type, binding::GLuint id, binding::GLenum severity, binding::GLsizei length, const char * message);
    static void insertMessage(binding::GLenum source, binding::GLenum type, binding::GLuint id, binding::GLenum severity, const std::string & message);
    static void insertMessage(const DebugMessage & message);

    static void enableMessage(binding::GLenum source, binding::GLenum type, binding::GLenum severity, binding::GLuint id);
    static void enableMessages(binding::GLenum source, binding::GLenum type, binding::GLenum severity, binding::GLsizei count, const binding::GLuint * ids);
    static void enableMessages(binding::GLenum source, binding::GLenum type, binding::GLenum severity, const std::vector<binding::GLuint> & ids);

    static void disableMessage(binding::GLenum source, binding::GLenum type, binding::GLenum severity, binding::GLuint id);
    static void disableMessages(binding::GLenum source, binding::GLenum type, binding::GLenum severity, binding::GLsizei count, const binding::GLuint * ids);
    static void disableMessages(binding::GLenum source, binding::GLenum type, binding::GLenum severity, const std::vector<binding::GLuint> & ids);

    static void controlMessages(binding::GLenum source, binding::GLenum type, binding::GLenum severity, binding::GLsizei count, const binding::GLuint * ids, binding::GLboolean enabled);

    static bool isFallbackImplementation();
};

} // namespace globjects
