#pragma once

#include <set>
#include <unordered_map>
#include <vector>

#include <glm/vec3.hpp>

#include <globjects/base/ChangeListener.h>
#include <globjects/base/ref_ptr.h>

#include <globjects/globjects_api.h>

#include <globjects/Object.h>
#include <globjects/LocationIdentity.h>
#include <globjects/UniformBlock.h>

namespace globjects
{

class AbstractUniform;
class ProgramBinary;
class Shader;

template <typename T>
class Uniform;


/** \brief Wraps an OpenGL program.
    
    Therefor it suclasses Object. Programs get attached a set of shaders with 
    attach(). It inherits ChangeListener to react to changes to attached 
    shaders. To use a program for rendering, call use(). During use() the 
    program ensure that all attached shaders are compiled and linked. After 
    that, the program is registered in OpenGL to be used during the upcoming 
    rendering pileline calls.

    Shaders can be detached using detach() and queried with shaders().

    To use a program as a compute program, dispatchCompute() can be used to 
    start the kernel.

    Example code for setting up a program and use it for rendering
    
    \code{.cpp}

        Program * program = new Program();
        program->attach(
            Shader::fromString(binding::GL_VERTEX_SHADER, "...")
          , Shader::fromString(binding::GL_FRAGMENT_SHADER, "...")
          , ...);
        program->use();
    
        // draw calls
    
        program->release();

    \endcode
    
    Example code for using a program as compute program
    \code{.cpp}

        Program * program = new Program();
        program->attach(Shader::fromString(binding::GL_COMPUTE_SHADER, "..."));
    
        program->dispatchCompute(128, 1, 1);
    
        program->release();

        \endcode
    
    \see http://www.opengl.org/wiki/Program_Object
    \see Shader
 */
class GLOBJECTS_API Program : public Object, protected ChangeListener
{
    friend class UniformBlock;
    friend class ProgramBinaryImplementation_GetProgramBinaryARB;
    friend class ProgramBinaryImplementation_None;

public:
    enum class BinaryImplementation
    {
        GetProgramBinaryARB
    ,   None
    };

    static void hintBinaryImplementation(BinaryImplementation impl);

public:
	Program();
    Program(ProgramBinary * binary);

    virtual void accept(ObjectVisitor & visitor) override;

    void use() const;
    void release() const;

	bool isUsed() const;
	bool isLinked() const;

    void attach(Shader * shader);
    template <class ...Shaders> 
    void attach(Shader * shader, Shaders... shaders);

	void detach(Shader * shader);

	std::set<Shader*> shaders() const;

    void link() const;
    void invalidate() const;

    void setBinary(ProgramBinary * binary);
    ProgramBinary * getBinary() const;

	const std::string infoLog() const;
	binding::GLint get(binding::GLenum pname) const;

    void getActiveAttrib(binding::GLuint index, binding::GLsizei bufSize, binding::GLsizei * length, binding::GLint * size, binding::GLenum * type, binding::GLchar * name) const;

    binding::GLint getAttributeLocation(const std::string & name) const;
    binding::GLint getUniformLocation(const std::string & name) const;

    std::vector<binding::GLint> getAttributeLocations(const std::vector<std::string> & names) const;
    std::vector<binding::GLint> getUniformLocations(const std::vector<std::string> & names) const;

    void bindAttributeLocation(binding::GLuint index, const std::string & name) const;
#ifdef GLOBJECTS_GL_BINDING
    void bindFragDataLocation(binding::GLuint index, const std::string & name) const;
#endif

    binding::GLint getFragDataLocation(const std::string & name) const;
#ifdef GLOBJECTS_GL_BINDING
    binding::GLint getFragDataIndex(const std::string & name) const;
#endif

    void getInterface(binding::GLenum programInterface, binding::GLenum pname, binding::GLint * params) const;
    binding::GLuint getResourceIndex(binding::GLenum programInterface, const std::string & name) const;
    void getResourceName(binding::GLenum programInterface, binding::GLuint index, binding::GLsizei bufSize, binding::GLsizei * length, char * name) const;
    void getResource(binding::GLenum programInterface, binding::GLuint index, binding::GLsizei propCount, const binding::GLenum * props, binding::GLsizei bufSize, binding::GLsizei * length, binding::GLint * params) const;
    binding::GLint getResourceLocation(binding::GLenum programInterface, const std::string & name) const;
    binding::GLint getResourceLocationIndex(binding::GLenum programInterface, const std::string & name) const;

    /** Convenience methods for getInterface()
    */
    binding::GLint getInterface(binding::GLenum programInterface, binding::GLenum pname) const;


	/** Convenience methods for getResource()
	*/
    binding::GLint getResource(binding::GLenum programInterface, binding::GLuint index, binding::GLenum prop, binding::GLsizei * length = nullptr) const;
    std::vector<binding::GLint> getResource(binding::GLenum programInterface, binding::GLuint index, const std::vector<binding::GLenum> & props, binding::GLsizei * length = nullptr) const;
    void getResource(binding::GLenum programInterface, binding::GLuint index, const std::vector<binding::GLenum> & props, binding::GLsizei bufSize, binding::GLsizei * length, binding::GLint * params) const;

    binding::GLuint getUniformBlockIndex(const std::string& name) const;
    UniformBlock * uniformBlock(binding::GLuint uniformBlockIndex);
    const UniformBlock * uniformBlock(binding::GLuint uniformBlockIndex) const;
    UniformBlock * uniformBlock(const std::string& name);
    const UniformBlock * uniformBlock(const std::string& name) const;
    void getActiveUniforms(binding::GLsizei uniformCount, const binding::GLuint * uniformIndices, binding::GLenum pname, binding::GLint * params) const;
    std::vector<binding::GLint> getActiveUniforms(const std::vector<binding::GLuint> & uniformIndices, binding::GLenum pname) const;
    std::vector<binding::GLint> getActiveUniforms(const std::vector<binding::GLint> & uniformIndices, binding::GLenum pname) const;
    binding::GLint getActiveUniform(binding::GLuint uniformIndex, binding::GLenum pname) const;
    std::string getActiveUniformName(binding::GLuint uniformIndex) const;

	template<typename T>
	void setUniform(const std::string & name, const T & value);
    template<typename T>
    void setUniform(binding::GLint location, const T & value);

	/** Retrieves the existing or creates a new typed uniform, named <name>.
	*/
	template<typename T>
	Uniform<T> * getUniform(const std::string & name);
    template<typename T>
    const Uniform<T> * getUniform(const std::string & name) const;
    template<typename T>
    Uniform<T> * getUniform(binding::GLint location);
    template<typename T>
    const Uniform<T> * getUniform(binding::GLint location) const;

	/** Adds the uniform to the internal list of named uniforms. If an equally
		named uniform already exists, this program derigisters itself and the uniform
		gets replaced (and by this the old one gets dereferenced). If the current
		program is linked, the uniforms value will be passed to the program object.
	*/
	void addUniform(AbstractUniform * uniform);

#ifdef GLOBJECTS_GL_BINDING
    void setShaderStorageBlockBinding(binding::GLuint storageBlockIndex, binding::GLuint storageBlockBinding) const;
#endif

	void dispatchCompute(binding::GLuint numGroupsX, binding::GLuint numGroupsY, binding::GLuint numGroupsZ);
    void dispatchCompute(const glm::uvec3 & numGroups);

#ifdef GLOBJECTS_GL_BINDING
    void dispatchComputeGroupSize(binding::GLuint numGroupsX, binding::GLuint numGroupsY, binding::GLuint numGroupsZ, binding::GLuint groupSizeX, binding::GLuint groupSizeY, binding::GLuint groupSizeZ);
    void dispatchComputeGroupSize(const glm::uvec3 & numGroups, const glm::uvec3 & groupSizes);

    virtual binding::GLenum objectType() const override;
#endif

protected:
    virtual ~Program();

    bool checkLinkStatus() const;
    void checkDirty() const;

    bool compileAttachedShaders() const;
    void updateUniforms() const;
    void updateUniformBlockBindings() const;

	// ChangeListener Interface

    virtual void notifyChanged(const Changeable * sender) override;

protected:
	static binding::GLuint createProgram();

    template<typename T>
    void setUniformByIdentity(const LocationIdentity & identity, const T & value);
    template<typename T>
    Uniform<T> * getUniformByIdentity(const LocationIdentity & identity);
    template<typename T>
    const Uniform<T> * getUniformByIdentity(const LocationIdentity & identity) const;

    UniformBlock * getUniformBlockByIdentity(const LocationIdentity & identity);
    const UniformBlock * getUniformBlockByIdentity(const LocationIdentity & identity) const;

protected:
    std::set<ref_ptr<Shader>> m_shaders;
    ref_ptr<ProgramBinary> m_binary;

    std::unordered_map<LocationIdentity, ref_ptr<AbstractUniform>> m_uniforms;
    std::unordered_map<LocationIdentity, UniformBlock> m_uniformBlocks;

    mutable bool m_linked;
    mutable bool m_dirty;
};

} // namespace globjects

#include <globjects/Program.hpp>
