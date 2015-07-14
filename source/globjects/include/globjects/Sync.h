#pragma once

#include <globjects/binding/types.h>

#include <globjects/base/Referenced.h>

#include <globjects/globjects_api.h>

namespace globjects
{

class GLOBJECTS_API Sync : public Referenced
{
    friend class AbstractObjectNameImplementation;

public:
    static Sync * fence(binding::GLenum condition);

    virtual ~Sync();

    binding::GLenum clientWait(binding::SyncObjectMask flags, binding::GLuint64 timeout);
    void wait(binding::GLuint64 timeout);

    void get(binding::GLenum pname, binding::GLsizei bufsize, binding::GLsizei * length, binding::GLint * values);
    binding::GLint get(binding::GLenum pname);

    binding::GLsync sync() const;

protected:
    Sync(binding::GLsync sync);

    void wait(binding::UnusedMask flags, binding::GLuint64 timeout);

    static binding::GLsync fenceSync(binding::GLenum condition, binding::UnusedMask flags);
    static Sync * fence(binding::GLenum condition, binding::UnusedMask flags);

protected:
    binding::GLsync m_sync;
    mutable void * m_objectLabelState;
};

} // namespace globjects
