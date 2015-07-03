
#include <globjects/glbindinglogging.h>

#include <sstream>
#include <iostream>

#include <khrapi/Value.h>

#include <glbinding/Version.h>
#include <glbinding/Meta.h>


namespace globjects 
{

LogMessageBuilder operator<<(LogMessageBuilder builder, const glbinding::Version & version)
{
    builder << "Version " << version.toString();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::GLboolean & value)
{
    builder << glbinding::Meta::getString(value);

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::GLenum & value)
{
    builder << glbinding::Meta::getString(value);

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::GLextension & value)
{
    builder << glbinding::Meta::getString(value);

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::AttribMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::AttribMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::ClearBufferMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::ClearBufferMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::ClientAttribMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::ClientAttribMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::ContextFlagMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::ContextFlagMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::ContextProfileMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::ContextProfileMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::FfdMaskSGIX & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::FfdMaskSGIX>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::FragmentShaderColorModMaskATI & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::FragmentShaderColorModMaskATI>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::FragmentShaderDestMaskATI & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::FragmentShaderDestMaskATI>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::FragmentShaderDestModMaskATI & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::FragmentShaderDestModMaskATI>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::MapBufferUsageMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::MapBufferUsageMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::MemoryBarrierMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::MemoryBarrierMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::PathRenderingMaskNV & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::PathRenderingMaskNV>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::PerformanceQueryCapsMaskINTEL & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::PerformanceQueryCapsMaskINTEL>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::SyncObjectMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::SyncObjectMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::TextureStorageMaskAMD & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::TextureStorageMaskAMD>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::UseProgramStageMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::UseProgramStageMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::VertexHintsMaskPGI & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::VertexHintsMaskPGI>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::PathFontStyle & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::PathFontStyle>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::UnusedMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::UnusedMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const gl::BufferAccessMask & value)
{
    std::ostringstream stream;

    khrapi::Value<gl::BufferAccessMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

} // namespace globjects
