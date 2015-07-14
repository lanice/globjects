#pragma once

#include <globjects/base/Singleton.h>

#include "AbstractDebugImplementation.h"


namespace globjects 
{

class DebugImplementation_Legacy : public AbstractDebugImplementation
    , public Singleton<DebugImplementation_Legacy>
{
public:
    DebugImplementation_Legacy();

    virtual bool isFallback() override;

    virtual void enable() override;
    virtual void disable() override;
    virtual void setSynchronous(bool synchronous) override;
    virtual void insertMessage(const DebugMessage & message) override;
    virtual void controlMessages(binding::GLenum source, binding::GLenum type, binding::GLenum severity, binding::GLsizei count, const binding::GLuint * ids, binding::GLboolean enabled) override;
protected:
    bool m_enabled;
};

} // namespace globjects
