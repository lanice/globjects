#pragma once

#include <globjects/binding/types.h>

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <globjects/globjects_api.h>
#include <globjects/Object.h>
#include <globjects/TextureHandle.h>

namespace globjects 
{

class Buffer;


/** \brief Wraps OpenGL texture objects.
 * A Texture provides both interfaces to bind them for the OpenGL pipeline:
 * binding and bindless texture. Bindless textures are only available if the
 * graphics driver supports them.
 *
 * \see http://www.opengl.org/wiki/Texture
 * \see http://www.opengl.org/registry/specs/NV/bindless_texture.txt
 */
class GLOBJECTS_API Texture : public Object
{
public:
    Texture();
    Texture(binding::GLenum target);
    static Texture * fromId(binding::GLuint id, binding::GLenum  target);

    static Texture * createDefault();
    static Texture * createDefault(binding::GLenum target);

    virtual void accept(ObjectVisitor & visitor) override;

    void bind() const;
    void unbind() const;
    static void unbind(binding::GLenum target);

    void bindActive(binding::GLenum texture) const;
    void unbindActive(binding::GLenum texture) const;

    void setParameter(binding::GLenum name, binding::GLenum value);
    void setParameter(binding::GLenum name, binding::GLint value);
    void setParameter(binding::GLenum name, binding::GLfloat value);

    binding::GLint getParameter(binding::GLenum pname) const;
    binding::GLint getLevelParameter(binding::GLint level, binding::GLenum pname) const;

#ifdef GLOBJECTS_GL_BINDING
    void getImage(binding::GLint level, binding::GLenum format, binding::GLenum type, binding::GLvoid * image) const;
    std::vector<unsigned char> getImage(binding::GLint level, binding::GLenum format, binding::GLenum type) const;

    void getCompressedImage(binding::GLint lod, binding::GLvoid * image) const;
    std::vector<unsigned char> getCompressedImage(binding::GLint lod = 0) const;
#endif

    binding::GLenum target() const;

#ifdef GLOBJECTS_GL_BINDING
    void image1D(binding::GLint level, binding::GLenum internalFormat, binding::GLsizei width, binding::GLint border, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
    void compressedImage1D(binding::GLint level, binding::GLenum internalFormat, binding::GLsizei width, binding::GLint border, binding::GLsizei imageSize, const binding::GLvoid * data);
    void subImage1D(binding::GLint level, binding::GLint xOffset, binding::GLsizei width, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
#endif

    void image2D(binding::GLint level, binding::GLenum internalFormat, binding::GLsizei width, binding::GLsizei height, binding::GLint border, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
    void image2D(binding::GLint level, binding::GLenum internalFormat, const glm::ivec2 & size, binding::GLint border, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
    void image2D(binding::GLenum target, binding::GLint level, binding::GLenum internalFormat, binding::GLsizei width, binding::GLsizei height, binding::GLint border, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
    void image2D(binding::GLenum target, binding::GLint level, binding::GLenum internalFormat, const glm::ivec2 & size, binding::GLint border, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
    void compressedImage2D(binding::GLint level, binding::GLenum internalFormat, binding::GLsizei width, binding::GLsizei height, binding::GLint border, binding::GLsizei imageSize, const binding::GLvoid * data);
    void compressedImage2D(binding::GLint level, binding::GLenum internalFormat, const glm::ivec2 & size, binding::GLint border, binding::GLsizei imageSize, const binding::GLvoid * data);
    void subImage2D(binding::GLint level, binding::GLint xOffset, binding::GLint yOffset, binding::GLsizei width, binding::GLsizei height, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
    void subImage2D(binding::GLint level, const glm::ivec2& offset, const glm::ivec2& size, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);

    void image3D(binding::GLint level, binding::GLenum internalFormat, binding::GLsizei width, binding::GLsizei height, binding::GLsizei depth, binding::GLint border, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
    void image3D(binding::GLint level, binding::GLenum internalFormat, const glm::ivec3 & size, binding::GLint border, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
    void compressedImage3D(binding::GLint level, binding::GLenum internalFormat, binding::GLsizei width, binding::GLsizei height, binding::GLsizei depth, binding::GLint border, binding::GLsizei imageSize, const binding::GLvoid * data);
    void compressedImage3D(binding::GLint level, binding::GLenum internalFormat, const glm::ivec3 & size, binding::GLint border, binding::GLsizei imageSize, const binding::GLvoid * data);
    void subImage3D(binding::GLint level, binding::GLint xOffset, binding::GLint yOffset, binding::GLint zOffset, binding::GLsizei width, binding::GLsizei height, binding::GLsizei depth, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);
    void subImage3D(binding::GLint level, const glm::ivec3& offset, const glm::ivec3& size, binding::GLenum format, binding::GLenum type, const binding::GLvoid * data);

#ifdef GLOBJECTS_GL_BINDING
    void image2DMultisample(binding::GLsizei samples, binding::GLenum internalFormat, binding::GLsizei width, binding::GLsizei height, binding::GLboolean fixedSamplesLocations);
    void image2DMultisample(binding::GLsizei samples, binding::GLenum internalFormat, const glm::ivec2 & size, binding::GLboolean fixedSamplesLocations);
    void image3DMultisample(binding::GLsizei samples, binding::GLenum internalFormat, binding::GLsizei width, binding::GLsizei height, binding::GLsizei depth, binding::GLboolean fixedSamplesLocations);
    void image3DMultisample(binding::GLsizei samples, binding::GLenum internalFormat, const glm::ivec3 & size, binding::GLboolean fixedSamplesLocations);

    void storage1D(binding::GLsizei levels, binding::GLenum internalFormat, binding::GLsizei width);
#endif

    void storage2D(binding::GLsizei levels, binding::GLenum internalFormat, binding::GLsizei width, binding::GLsizei height);
    void storage2D(binding::GLsizei levels, binding::GLenum internalFormat, const glm::ivec2 & size);
    void storage3D(binding::GLsizei levels, binding::GLenum internalFormat, binding::GLsizei width, binding::GLsizei height, binding::GLsizei depth);
    void storage3D(binding::GLsizei levels, binding::GLenum internalFormat, const glm::ivec3 & size);

    void textureView(binding::GLuint originalTexture, binding::GLenum internalFormat, binding::GLuint minLevel, binding::GLuint numLevels, binding::GLuint minLayer, binding::GLuint numLayers);

    void texBuffer(binding::GLenum internalFormat, Buffer * buffer);
    void texBuffer(binding::GLenum activeTexture, binding::GLenum internalFormat, Buffer * buffer);
    void texBufferRange(binding::GLenum internalFormat, Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr size);
    void texBufferRange(binding::GLenum activeTexture, binding::GLenum internalFormat, Buffer * buffer, binding::GLintptr offset, binding::GLsizeiptr size);

#ifdef GLOBJECTS_GL_BINDING
    void clearImage(binding::GLint level, binding::GLenum format, binding::GLenum type, const void * data);
    void clearImage(binding::GLint level, binding::GLenum format, binding::GLenum type, const glm::vec4 & value);
    void clearImage(binding::GLint level, binding::GLenum format, binding::GLenum type, const glm::ivec4 & value);
    void clearImage(binding::GLint level, binding::GLenum format, binding::GLenum type, const glm::uvec4 & value);

    void clearSubImage(binding::GLint level, binding::GLint xOffset, binding::GLint yOffset, binding::GLint zOffset, binding::GLsizei width, binding::GLsizei height, binding::GLsizei depth, binding::GLenum format, binding::GLenum type, const void * data);
    void clearSubImage(binding::GLint level, const glm::ivec3 & offset, const glm::ivec3 & size, binding::GLenum format, binding::GLenum type, const void * data);
    void clearSubImage(binding::GLint level, const glm::ivec3 & offset, const glm::ivec3 & size, binding::GLenum format, binding::GLenum type, const glm::vec4 & value);
    void clearSubImage(binding::GLint level, const glm::ivec3 & offset, const glm::ivec3 & size, binding::GLenum format, binding::GLenum type, const glm::ivec4 & value);
    void clearSubImage(binding::GLint level, const glm::ivec3 & offset, const glm::ivec3 & size, binding::GLenum format, binding::GLenum type, const glm::uvec4 & value);

    void invalidateImage(binding::GLint level) const;
    void invalidateSubImage(binding::GLint level, binding::GLint xoffset, binding::GLint yoffset, binding::GLint zoffset, binding::GLsizei width, binding::GLsizei height, binding::GLsizei depth);
    void invalidateSubImage(binding::GLint level, const glm::ivec3& offset, const glm::ivec3 size);
#endif

    void bindImageTexture(binding::GLuint unit, binding::GLint level, binding::GLboolean layered, binding::GLint layer, binding::GLenum access, binding::GLenum format) const;
    static void unbindImageTexture(binding::GLuint unit);

    void generateMipmap();

    TextureHandle textureHandle() const;
    bool isResident() const;
    TextureHandle makeResident() const;
    void makeNonResident() const;

    void pageCommitment(binding::GLint level, binding::GLint xOffset, binding::GLint yOffset, binding::GLint zOffset, binding::GLsizei width, binding::GLsizei height, binding::GLsizei depth, binding::GLboolean commit) const;
    void pageCommitment(binding::GLint level, const glm::ivec3& offset, const glm::ivec3& size, binding::GLboolean commit) const;

#ifdef GLOBJECTS_GL_BINDING
    virtual binding::GLenum objectType() const override;
#endif

protected:
    Texture(IDResource * resource, binding::GLenum target);
    virtual ~Texture();

protected:
    binding::GLenum m_target;
};

} // namespace globjects
