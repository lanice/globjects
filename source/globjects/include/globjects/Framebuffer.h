#pragma once

#include <map>
#include <string>
#include <vector>
#include <array>

#include <glm/vec4.hpp>

#include <globjects/base/ref_ptr.h>

#include <globjects/globjects_api.h>
#include <globjects/Object.h>


namespace globjects 
{

class FramebufferAttachment;
class Renderbuffer;
class Texture;
class Buffer;

/** \brief Enables creation of arbitrary render targets that are not directly drawn on the screen.
    
    Different attachments can be added with attachTexture(), attachTexture1D(), 
    attachTexture2D, attachTextureLayer() and attachRenderBuffer() and queried 
    using attachment() and attachments().
    
    To access the default FBO (e.g. if you want to blit an FBO to it), call 
    defaultFBO(). To blit between two FBOs, prepare them with setReadBuffer()
    and setDrawBuffer() and blit with blit(). 

    Draw restrictions can be done with setDrawBuffers(). To read pixels from 
    an FBO direct into RAM, use readPixels() and to read into an OpenGL buffer 
    use readPixelsToBuffer(). To check if an FBO is setup correctly, the status
    can be checked using checkStatus(), statusString() and printStatus().

    \see http://www.opengl.org/wiki/Framebuffer_Object
    \see FrameBufferAttachment
    \see TextureAttachment
    \see RenderBufferAttachment
 */
class GLOBJECTS_API Framebuffer : public Object
{
public:
    enum class BindlessImplementation
    {
        DirectStateAccessARB
    ,   DirectStateAccessEXT
    ,   Legacy
    };

    static void hintBindlessImplementation(BindlessImplementation impl);

public:
    Framebuffer();
    static Framebuffer * fromId(binding::GLuint id);

    static Framebuffer * defaultFBO();

    virtual void accept(ObjectVisitor& visitor) override;

    /** uses GL_FRAMEBUFFER as target
    */
    void bind() const;
    void bind(binding::GLenum target) const;

    /** uses GL_FRAMEBUFFER as target
    */
    static void unbind();
    static void unbind(binding::GLenum target);

    void setParameter(binding::GLenum pname, binding::GLint param);
    binding::GLint getAttachmentParameter(binding::GLenum attachment, binding::GLenum pname) const;

    void attachTexture(binding::GLenum attachment, Texture * texture, binding::GLint level = 0);
    void attachTextureLayer(binding::GLenum attachment, Texture * texture, binding::GLint level = 0, binding::GLint layer = 0);
    void attachRenderBuffer(binding::GLenum attachment, Renderbuffer * renderBuffer);

    bool detach(binding::GLenum attachment);

    void setReadBuffer(binding::GLenum mode) const;
    void setDrawBuffer(binding::GLenum mode) const;
    void setDrawBuffers(binding::GLsizei n, const binding::GLenum * modes) const;
    void setDrawBuffers(const std::vector<binding::GLenum> & modes) const;

    void clear(binding::ClearBufferMask mask);

    void clearBufferiv(binding::GLenum buffer, binding::GLint drawBuffer, const binding::GLint * value);
    void clearBufferuiv(binding::GLenum buffer, binding::GLint drawBuffer, const binding::GLuint * value);
    void clearBufferfv(binding::GLenum buffer, binding::GLint drawBuffer, const binding::GLfloat * value);
    void clearBufferfi(binding::GLenum buffer, binding::GLint drawBuffer, binding::GLfloat depth, binding::GLint stencil);

    void clearBuffer(binding::GLenum buffer, binding::GLint drawBuffer, const glm::ivec4 & value);
    void clearBuffer(binding::GLenum buffer, binding::GLint drawBuffer, const glm::uvec4 & value);
    void clearBuffer(binding::GLenum buffer, binding::GLint drawBuffer, const glm::vec4 & value);

    static void colorMask(binding::GLboolean red, binding::GLboolean green, binding::GLboolean blue, binding::GLboolean alpha);
    static void colorMask(const glm::bvec4 & mask);
    static void colorMaski(binding::GLuint buffer, binding::GLboolean red, binding::GLboolean green, binding::GLboolean blue, binding::GLboolean alpha);
    static void colorMaski(binding::GLuint buffer, const glm::bvec4 & mask);
    static void clearColor(binding::GLfloat red, binding::GLfloat green, binding::GLfloat blue, binding::GLfloat alpha);
    static void clearColor(const glm::vec4 & color);
    static void clearDepth(binding::GLclampd depth);

    void readPixels(binding::GLint x, binding::GLint y, binding::GLsizei width, binding::GLsizei height, binding::GLenum format, binding::GLenum type, binding::GLvoid * data = nullptr) const;
    void readPixels(const std::array<binding::GLint, 4> & rect, binding::GLenum format, binding::GLenum type, binding::GLvoid * data = nullptr) const;
    void readPixels(binding::GLenum readBuffer, const std::array<binding::GLint, 4> & rect, binding::GLenum format, binding::GLenum type, binding::GLvoid * data = nullptr) const;
    std::vector<unsigned char> readPixelsToByteArray(const std::array<binding::GLint, 4> & rect, binding::GLenum format, binding::GLenum type) const;
    std::vector<unsigned char> readPixelsToByteArray(binding::GLenum readBuffer, const std::array<binding::GLint, 4> & rect, binding::GLenum format, binding::GLenum type) const;
    void readPixelsToBuffer(const std::array<binding::GLint, 4> & rect, binding::GLenum format, binding::GLenum type, Buffer * pbo) const;

    binding::GLenum checkStatus() const;
    std::string statusString() const;
    void printStatus(bool onlyErrors = false) const;

    FramebufferAttachment * getAttachment(binding::GLenum attachment);
    std::vector<FramebufferAttachment*> attachments();

    void blit(binding::GLenum readBuffer, const std::array<binding::GLint, 4> & srcRect, Framebuffer * destFbo, binding::GLenum drawBuffer, const std::array<binding::GLint, 4> & destRect, binding::ClearBufferMask mask, binding::GLenum filter) const;
    void blit(binding::GLenum readBuffer, const std::array<binding::GLint, 4> & srcRect, Framebuffer * destFbo, const std::vector<binding::GLenum> & drawBuffers, const std::array<binding::GLint, 4> & destRect, binding::ClearBufferMask mask, binding::GLenum filter) const;

#ifdef GLOBJECTS_GL_BINDING
    virtual binding::GLenum objectType() const override;
#endif

protected:
    Framebuffer(IDResource * resource);
    virtual ~Framebuffer();

    void addAttachment(FramebufferAttachment * attachment);

    static void blit(binding::GLint srcX0, binding::GLint srcY0, binding::GLint srcX1, binding::GLint srcY1, binding::GLint destX0, binding::GLint destY0, binding::GLint destX1, binding::GLint destY1, binding::ClearBufferMask mask, binding::GLenum filter);
    static void blit(const std::array<binding::GLint, 4> & srcRect, const std::array<binding::GLint, 4> & destRect, binding::ClearBufferMask mask, binding::GLenum filter);

protected:
	std::map<binding::GLenum, ref_ptr<FramebufferAttachment>> m_attachments;
};

} // namespace globjects
