#pragma once

#include <globjects/binding/types.h>

#include <globjects/Buffer.h>


namespace globjects
{

class Buffer;

class AbstractBufferImplementation
{
public:
    AbstractBufferImplementation();
    virtual ~AbstractBufferImplementation();

    static AbstractBufferImplementation * get(Buffer::BindlessImplementation impl = 
        Buffer::BindlessImplementation::DirectStateAccessARB);

    virtual binding::GLuint create() const = 0;
    virtual void destroy(binding::GLuint id) const = 0;

    virtual void * map(const Buffer * buffer, binding::GLenum access) const = 0;
    virtual void * mapRange(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr length, binding::BufferAccessMask access) const = 0;
    virtual bool unmap(const Buffer * buffer) const = 0;

    virtual void setData(const Buffer * buffer, binding::GLsizeiptr size, const binding::GLvoid * data, binding::GLenum usage) const = 0;
    virtual void setSubData(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr size, const binding::GLvoid * data) const = 0;
    virtual void setStorage(const Buffer * buffer, binding::GLsizeiptr size, const binding::GLvoid * data, binding::BufferStorageMask flags) const = 0;

    virtual void copySubData(const Buffer * buffer, Buffer * other, binding::GLintptr readOffset, binding::GLintptr writeOffset, binding::GLsizeiptr size) const = 0;

    virtual binding::GLint getParameter(const Buffer * buffer, binding::GLenum pname) const = 0;
    virtual binding::GLint64 getParameter64(const Buffer * buffer, binding::GLenum pname) const = 0;
    virtual void * getPointer(const Buffer * buffer, binding::GLenum pname) const = 0;

    virtual void clearData(const Buffer * buffer, binding::GLenum internalformat, binding::GLenum format, binding::GLenum type, const void * data) const = 0;
    virtual void clearSubData(const Buffer * buffer, binding::GLenum internalformat, binding::GLintptr offset, binding::GLsizeiptr size, binding::GLenum format, binding::GLenum type, const void * data) const = 0;

    virtual void flushMappedRange(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr length) const = 0;

    virtual void getBufferSubData(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr size, binding::GLvoid * data) const = 0;

    virtual void invalidateData(const Buffer * buffer) const = 0;
    virtual void invalidateSubData(const Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr length) const = 0;
};

} // namespace globjects
