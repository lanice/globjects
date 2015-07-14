#pragma once

#include <globjects/binding/types.h>

namespace globjects 
{

class AbstractResource
{
public:
    AbstractResource(bool hasOwnership);
    virtual ~AbstractResource();

    bool hasOwnership() const;

protected:
    bool m_hasOwnership;
};


class IDTrait
{
public:
    IDTrait(binding::GLuint id);
    virtual ~IDTrait();

    binding::GLuint id() const;

protected:
    binding::GLuint m_id;
};


class IDResource : public AbstractResource, public IDTrait
{
public:
    IDResource(binding::GLuint id);

protected:
    IDResource(binding::GLuint id, bool hasOwnership);
};


class ExternalResource : public IDResource
{
public:
    ExternalResource(binding::GLuint id);
};


class InvalidResource : public IDResource
{
public:
    InvalidResource();
    ~InvalidResource();
};


class BufferResource : public IDResource
{
public:
    BufferResource();
    ~BufferResource();
};


class FrameBufferObjectResource : public IDResource
{
public:
    FrameBufferObjectResource();
    ~FrameBufferObjectResource();
};


class ProgramResource : public IDResource
{
public:
    ProgramResource();
    ~ProgramResource();
};


class QueryResource : public IDResource
{
public:
    QueryResource();
    ~QueryResource();
};


class RenderBufferObjectResource : public IDResource
{
public:
    RenderBufferObjectResource();
    ~RenderBufferObjectResource();
};


class SamplerResource : public IDResource
{
public:
    SamplerResource();
    ~SamplerResource();
};


class ShaderResource : public IDResource
{
public:
    ShaderResource(binding::GLenum type);
    ~ShaderResource();
};


class TextureResource : public IDResource
{
public:
    TextureResource();
    ~TextureResource();
};


class TransformFeedbackResource : public IDResource
{
public:
    TransformFeedbackResource();
    ~TransformFeedbackResource();
};


class VertexArrayObjectResource : public IDResource
{
public:
    VertexArrayObjectResource();
    ~VertexArrayObjectResource();
};

} // namespace globjects
