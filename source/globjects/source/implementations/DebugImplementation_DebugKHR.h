#pragma once

#include <globjects/binding/types.h>

#include <globjects/base/Singleton.h>

#include "AbstractDebugImplementation.h"


namespace globjects 
{

class DebugImplementation_DebugKHR : public AbstractDebugImplementation
    , public Singleton<DebugImplementation_DebugKHR>
{
public:
    DebugImplementation_DebugKHR();

    virtual void enable() override;
    virtual void disable() override;
    virtual void setSynchronous(bool synchronous) override;
    virtual void insertMessage(const DebugMessage & message) override;
    virtual void controlMessages(binding::GLenum source, binding::GLenum type, binding::GLenum severity, binding::GLsizei count, const binding::GLuint * ids, binding::GLboolean enabled) override;

protected:
    bool m_isRegistered;
    void registerCallback();

    static void GL_APIENTRY debugMessageCallback(binding::GLenum source, binding::GLenum type, binding::GLuint id, binding::GLenum severity, binding::GLsizei length, const char * message, const void * param);
};

} // namespace globjects
