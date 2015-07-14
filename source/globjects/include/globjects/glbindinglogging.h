#pragma once

#include <globjects/globjects_api.h>

#include <globjects/base/LogMessageBuilder.h>

#include <globjects/binding/types.h>

namespace khrapi
{

class AbstractVersion;

}

namespace globjects 
{

GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const khrapi::AbstractVersion & version);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::GLboolean & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::GLenum & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::GLextension & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::AttribMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::ClearBufferMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::ContextFlagMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::MapBufferUsageMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::MemoryBarrierMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::PathRenderingMaskNV & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::PerformanceQueryCapsMaskINTEL & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::SyncObjectMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::UseProgramStageMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::PathFontStyle & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::UnusedMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::BufferAccessMask & value);

#ifdef GLOBJECTS_GL_BINDING
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::ClientAttribMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::ContextProfileMask & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::FfdMaskSGIX & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::FragmentShaderColorModMaskATI & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::FragmentShaderDestMaskATI & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::FragmentShaderDestModMaskATI & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::TextureStorageMaskAMD & value);
GLOBJECTS_API LogMessageBuilder operator<<(LogMessageBuilder builder, const binding::VertexHintsMaskPGI & value);
#endif

} // namespace globjects
