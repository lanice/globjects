#pragma once

#include <array>

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>


namespace globjects
{

class StateSetting;

class GLOBJECTS_API AbstractState
{
public:
    virtual void enable(binding::GLenum capability) = 0;
    virtual void disable(binding::GLenum capability) = 0;
    virtual bool isEnabled(binding::GLenum capability) const = 0;
    virtual void enable(binding::GLenum capability, int index) = 0;
    virtual void disable(binding::GLenum capability, int index) = 0;
    virtual bool isEnabled(binding::GLenum capability, int index) const = 0;

    void setEnabled(binding::GLenum capability, bool enabled);
    void setEnabled(binding::GLenum capability, int index, bool enabled);

    void blendColor(binding::GLfloat red, binding::GLfloat green, binding::GLfloat blue, binding::GLfloat alpha);
    void blendColor(const std::array<binding::GLfloat, 4> & color);
    void blendFunc(binding::GLenum sFactor, binding::GLenum dFactor);
    void blendFuncSeparate(binding::GLenum srcRGB, binding::GLenum dstRGB, binding::GLenum srcAlpha, binding::GLenum dstAlpha);
    void clearColor(binding::GLfloat red, binding::GLfloat green, binding::GLfloat blue, binding::GLfloat alpha);
    void clearColor(const std::array<binding::GLfloat, 4> & color);
    void clearDepth(binding::GLfloat depth);
    void clearStencil(binding::GLint s);
    void colorMask(binding::GLboolean red, binding::GLboolean green, binding::GLboolean blue, binding::GLboolean alpha);
    void colorMask(const std::array<binding::GLboolean, 4> & mask);
    void cullFace(binding::GLenum mode);
    void depthFunc(binding::GLenum func);
    void depthMask(binding::GLboolean flag);

#ifdef GLOBJECTS_GL_BINDING
    void depthRange(binding::GLdouble nearVal, binding::GLdouble farVal);
#endif

    void depthRange(binding::GLfloat nearVal, binding::GLfloat farVal);
    void depthRange(const std::array<binding::GLfloat, 2> & range);
    void frontFace(binding::GLenum winding);

    void pixelStore(binding::GLenum pname, binding::GLint param);

#ifdef GLOBJECTS_GL_BINDING
    void logicOp(binding::GLenum opcode);
    void pointParameter(binding::GLenum pname, binding::GLint param);
    void pointSize(binding::GLfloat size);
#endif

    void polygonMode(binding::GLenum face, binding::GLenum mode);
    void polygonOffset(binding::GLfloat factor, binding::GLfloat units);

#ifdef GLOBJECTS_GL_BINDING
    void primitiveRestartIndex(binding::GLuint index);
    void provokingVertex(binding::GLenum provokeMode);
#endif

    void sampleCoverage(binding::GLfloat value, binding::GLboolean invert);
    void scissor(binding::GLint x, binding::GLint y, binding::GLsizei width, binding::GLsizei height);
    void scissor(const std::array<binding::GLint, 4> & scissorBox);
    void stencilFunc(binding::GLenum func, binding::GLint ref, binding::GLuint mask);
    void stencilMask(binding::GLuint mask);
    void stencilOp(binding::GLenum stencilFail, binding::GLenum depthFail, binding::GLenum depthPass);
    void stencilFuncSeparate(binding::GLenum face, binding::GLenum func, binding::GLint ref, binding::GLuint mask);
    void stencilMaskSeparate(binding::GLenum face, binding::GLuint mask);
    void stencilOpSeparate(binding::GLenum face, binding::GLenum stencilFail, binding::GLenum depthFail, binding::GLenum depthPass);

    virtual void add(StateSetting * setting) = 0;

    template <typename... Arguments>
    void set(void (*function)(Arguments...), Arguments... arguments);
};

} // namespace globjects

#include <globjects/AbstractState.hpp>
