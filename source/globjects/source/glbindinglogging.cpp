
#include <globjects/glbindinglogging.h>

#include <sstream>
#include <iostream>

#include <khrapi/Version.h>
#include <khrapi/Value.h>

#include <globjects/binding/Meta.h>
#include <globjects/binding/typeintegrations.h>


namespace globjects 
{

LogMessageBuilder operator<<(LogMessageBuilder builder, const khrapi::AbstractVersion & version)
{
    builder << "Version " << version.toString();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::GLboolean & value)
{
    builder << binding::Meta::getString(value);

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::GLenum & value)
{
    builder << binding::Meta::getString(value);

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::GLextension & value)
{
    builder << binding::Meta::getString(value);

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::AttribMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::AttribMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::ClearBufferMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::ClearBufferMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::ContextFlagMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::ContextFlagMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::MapBufferUsageMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::MapBufferUsageMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::MemoryBarrierMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::MemoryBarrierMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::PathRenderingMaskNV & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::PathRenderingMaskNV>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::PerformanceQueryCapsMaskINTEL & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::PerformanceQueryCapsMaskINTEL>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::SyncObjectMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::SyncObjectMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::UseProgramStageMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::UseProgramStageMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::PathFontStyle & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::PathFontStyle>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::UnusedMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::UnusedMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::BufferAccessMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::BufferAccessMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

#ifdef GLOBJECTS_GL_BINDING
LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::ClientAttribMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::ClientAttribMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::ContextProfileMask & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::ContextProfileMask>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::FfdMaskSGIX & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::FfdMaskSGIX>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::FragmentShaderColorModMaskATI & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::FragmentShaderColorModMaskATI>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::FragmentShaderDestMaskATI & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::FragmentShaderDestMaskATI>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::FragmentShaderDestModMaskATI & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::FragmentShaderDestModMaskATI>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::TextureStorageMaskAMD & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::TextureStorageMaskAMD>(value).printOn(stream);

    builder << stream.str();

    return builder;
}

LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::VertexHintsMaskPGI & value)
{
    std::ostringstream stream;

    khrapi::Value<binding::VertexHintsMaskPGI>(value).printOn(stream);

    builder << stream.str();

    return builder;
}
#endif

} // namespace globjects
