#pragma once

#include <globjects/base/Singleton.h>

#include "AbstractBufferImplementation.h"


namespace globjects
{

class Buffer;

class BufferImplementation_DirectStateAccessEXT : public AbstractBufferImplementation
    , public Singleton<BufferImplementation_DirectStateAccessEXT>
{
public:
    virtual binding::GLuint create() const override;
    virtual void destroy(binding::GLuint id) const override;

    virtual void * map(const Buffer * buffer, binding::GLenum access) const override;
    virtual void * mapRange(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr length, binding::BufferAccessMask access) const override;
    virtual bool unmap(const Buffer * buffer) const override;

    virtual void setData(const Buffer * buffer, binding::GLsizeiptr size, const binding::GLvoid * data, binding::GLenum usage) const override;
    virtual void setSubData(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr size, const binding::GLvoid * data) const override;
    virtual void setStorage(const Buffer * buffer, binding::GLsizeiptr size, const binding::GLvoid * data, binding::BufferStorageMask flags) const override;

    virtual void copySubData(const Buffer * buffer, Buffer * other, binding::GLintptr readOffset, binding::GLintptr writeOffset, binding::GLsizeiptr size) const override;

    virtual binding::GLint getParameter(const Buffer * buffer, binding::GLenum pname) const override;
    virtual binding::GLint64 getParameter64(const Buffer * buffer, binding::GLenum pname) const override;
    virtual void * getPointer(const Buffer * buffer, binding::GLenum pname) const override;

    virtual void clearData(const Buffer * buffer, binding::GLenum internalformat, binding::GLenum format, binding::GLenum type, const void * data) const override;
    virtual void clearSubData(const Buffer * buffer, binding::GLenum internalformat, binding::GLintptr offset, binding::GLsizeiptr size, binding::GLenum format, binding::GLenum type, const void * data) const override;

    virtual void flushMappedRange(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr length) const override;

    virtual void getBufferSubData(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr size, binding::GLvoid * data) const override;

    virtual void invalidateData(const Buffer * buffer) const override;
    virtual void invalidateSubData(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr length) const override;
};

} // namespace globjects
