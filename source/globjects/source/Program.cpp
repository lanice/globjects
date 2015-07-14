
#include <globjects/Program.h>

#include <cassert>

#include <globjects/binding/functions.h>
#include <globjects/binding/extension.h>
#include <globjects/binding/boolean.h>
#include <globjects/binding/enum.h>

#include <globjects/globjects.h>

#include <globjects/Uniform.h>
#include <globjects/ObjectVisitor.h>
#include <globjects/ProgramBinary.h>
#include <globjects/Shader.h>
#include <globjects/AbstractUniform.h>

#include "Resource.h"
#include "registry/ImplementationRegistry.h"
#include "implementations/AbstractProgramBinaryImplementation.h"


namespace
{

const globjects::AbstractProgramBinaryImplementation & binaryImplementation()
{
    return globjects::ImplementationRegistry::current().programBinaryImplementation();
}

}

namespace globjects
{

using namespace binding;

void Program::hintBinaryImplementation(const BinaryImplementation impl)
{
    ImplementationRegistry::current().initialize(impl);
}


Program::Program()
: Object(new ProgramResource)
, m_linked(false)
, m_dirty(true)
{
}

Program::Program(ProgramBinary * binary)
: Program()
{
    setBinary(binary);
}

Program::~Program()
{
    for (std::pair<LocationIdentity, ref_ptr<AbstractUniform>> uniformPair : m_uniforms)
        uniformPair.second->deregisterProgram(this);

    if (0 == id())
    {
        for (auto & shader : m_shaders)
            shader->deregisterListener(this);
    }
    else
    {
        for (ref_ptr<Shader> shader : std::set<ref_ptr<Shader>>(m_shaders))
            detach(shader);
    }
}

void Program::accept(ObjectVisitor & visitor)
{
	visitor.visitProgram(this);
}

void Program::use() const
{
	checkDirty();

    if (!isLinked())
        return;

    glUseProgram(id());
}

void Program::release() const
{
    if (!isLinked())
        return;

    glUseProgram(0);
}

bool Program::isUsed() const
{
    GLuint currentProgram = static_cast<GLuint>(getInteger(GL_CURRENT_PROGRAM));

    return currentProgram > 0 && currentProgram == id();
}

bool Program::isLinked() const
{
	return m_linked;
}

void Program::invalidate() const
{
	m_dirty = true;
}

void Program::notifyChanged(const Changeable *)
{
	invalidate();
}

void Program::checkDirty() const
{
    if (m_dirty)
        link();
}

void Program::attach(Shader * shader)
{
    assert(shader != nullptr);

    binding::glAttachShader(id(), shader->id());

    shader->registerListener(this);
    m_shaders.insert(shader);

    invalidate();
}

void Program::detach(Shader * shader)
{
    assert(shader != nullptr);

    glDetachShader(id(), shader->id());

	shader->deregisterListener(this);
	m_shaders.erase(shader);

	invalidate();
}

std::set<Shader *> Program::shaders() const
{
	std::set<Shader *> shaders;
    for (ref_ptr<Shader> shader: m_shaders)
		shaders.insert(shader);
	return shaders;
}

void Program::link() const
{
    m_linked = false;

    if (!binaryImplementation().updateProgramLinkSource(this))
        return;

    glLinkProgram(id());

    m_linked = checkLinkStatus();
	m_dirty = false;

    updateUniforms();
    updateUniformBlockBindings();
}

bool Program::compileAttachedShaders() const
{
    for (Shader * shader : shaders())
    {
        if (shader->isCompiled())
            continue;

        // Some drivers (e.g. nvidia-331 on Ubuntu 13.04 automatically compile shaders during program linkage)
        // but we don't want to depend on such behavior
        shader->compile();

        if (!shader->isCompiled())
            return false;
    }
    return true;
}

bool Program::checkLinkStatus() const
{
    if (GL_FALSE == static_cast<GLboolean>(get(GL_LINK_STATUS)))
    {
        critical() << "Linker error:" << std::endl << infoLog();
        return false;
    }
    return true;
}

#ifdef GLOBJECTS_GL_BINDING
void Program::bindFragDataLocation(const GLuint index, const std::string & name) const
{
    glBindFragDataLocation(id(), index, name.c_str());
}
#endif

void Program::bindAttributeLocation(const GLuint index, const std::string & name) const
{
    glBindAttribLocation(id(), index, name.c_str());
}

GLint Program::getFragDataLocation(const std::string & name) const
{
    return glGetFragDataLocation(id(), name.c_str());
}

#ifdef GLOBJECTS_GL_BINDING
GLint Program::getFragDataIndex(const std::string & name) const
{
    return glGetFragDataIndex(id(), name.c_str());
}
#endif

GLint Program::getUniformLocation(const std::string& name) const
{
	checkDirty();
    if (!m_linked)
        return -1;

    return glGetUniformLocation(id(), name.c_str());
}

std::vector<GLint> Program::getAttributeLocations(const std::vector<std::string> & names) const
{
    std::vector<GLint> locations(names.size());
    for (unsigned i = 0; i<names.size(); ++i)
    {
        locations[i] = getAttributeLocation(names[i]);
    }
    return locations;
}

std::vector<GLint> Program::getUniformLocations(const std::vector<std::string> & names) const
{
    std::vector<GLint> locations(names.size());
    for (unsigned i = 0; i<names.size(); ++i)
    {
        locations[i] = getUniformLocation(names[i]);
    }
    return locations;
}

GLint Program::getAttributeLocation(const std::string & name) const
{
	checkDirty();
    if (!m_linked)
        return -1;

    return glGetAttribLocation(id(), name.c_str());
}

void Program::getInterface(binding::GLenum programInterface, binding::GLenum pname, binding::GLint * params) const
{
    checkDirty();

    glGetProgramInterfaceiv(id(), programInterface, pname, params);
}

GLuint Program::getResourceIndex(const GLenum programInterface, const std::string & name) const
{
    checkDirty();

    return glGetProgramResourceIndex(id(), programInterface, name.c_str());
}

void Program::getResourceName(binding::GLenum programInterface, binding::GLuint index, binding::GLsizei bufSize, binding::GLsizei * length, char * name) const
{
    checkDirty();

    glGetProgramResourceName(id(), programInterface, index, bufSize, length, name);
}

void Program::getResource(binding::GLenum programInterface, binding::GLuint index, binding::GLsizei propCount, const binding::GLenum * props, binding::GLsizei bufSize, binding::GLsizei * length, binding::GLint * params) const
{
    checkDirty();

    glGetProgramResourceiv(id(), programInterface, index, propCount, props, bufSize, length, params);
}

binding::GLint Program::getResourceLocation(binding::GLenum programInterface, const std::string & name) const
{
    checkDirty();

    return glGetProgramResourceLocation(id(), programInterface, name.c_str());
}

binding::GLint Program::getResourceLocationIndex(binding::GLenum programInterface, const std::string & name) const
{
    checkDirty();

#ifdef GLOBJECTS_GL_BINDING
    return glGetProgramResourceLocationIndex(id(), programInterface, name.c_str());
#else
    return glGetProgramResourceIndex(id(), programInterface, name.c_str());
#endif
}

binding::GLint Program::getInterface(binding::GLenum programInterface, binding::GLenum pname) const
{
    checkDirty();

    binding::GLint result;

    getInterface(programInterface, pname, &result);

    return result;
}

binding::GLint Program::getResource(binding::GLenum programInterface, binding::GLuint index, binding::GLenum prop, binding::GLsizei * length) const
{
    binding::GLint result;

    getResource(programInterface, index, 1, &prop, 1, length, &result);

    return result;
}

std::vector<binding::GLint> Program::getResource(binding::GLenum programInterface, binding::GLuint index, const std::vector<binding::GLenum> & props, binding::GLsizei * length) const
{
    std::vector<binding::GLint> result;
    result.resize(props.size());

    getResource(programInterface, index, props, static_cast<binding::GLsizei>(result.size()), length, result.data());

    return result;
}

void Program::getResource(binding::GLenum programInterface, binding::GLuint index, const std::vector<binding::GLenum> & props, binding::GLsizei bufSize, binding::GLsizei * length, binding::GLint * params) const
{
    getResource(programInterface, index, static_cast<binding::GLsizei>(props.size()), props.data(), bufSize, length, params);
}

GLuint Program::getUniformBlockIndex(const std::string & name) const
{
    checkDirty();

    return glGetUniformBlockIndex(id(), name.c_str());
}

void Program::getActiveUniforms(const GLsizei uniformCount, const GLuint * uniformIndices, const GLenum pname, GLint * params) const
{
    checkDirty();

    glGetActiveUniformsiv(id(), uniformCount, uniformIndices, pname, params);
}

std::vector<GLint> Program::getActiveUniforms(const std::vector<GLuint> & uniformIndices, const GLenum pname) const
{
    std::vector<GLint> result(uniformIndices.size());
    getActiveUniforms(static_cast<GLint>(uniformIndices.size()), uniformIndices.data(), pname, result.data());
    return result;
}

std::vector<GLint> Program::getActiveUniforms(const std::vector<GLint> & uniformIndices, const GLenum pname) const
{
    std::vector<GLuint> indices(uniformIndices.size());
    for (unsigned i=0; i<uniformIndices.size(); ++i)
        indices[i] = static_cast<GLuint>(uniformIndices[i]);
    return getActiveUniforms(indices, pname);
}

GLint Program::getActiveUniform(const GLuint uniformIndex, const GLenum pname) const
{
    GLint result = 0;
    getActiveUniforms(1, &uniformIndex, pname, &result);
    return result;
}

std::string Program::getActiveUniformName(const GLuint uniformIndex) const
{
    checkDirty();

#ifdef GLOBJECTS_GL_BINDING
    GLint length = getActiveUniform(uniformIndex, GL_UNIFORM_NAME_LENGTH);
    std::vector<char> name(length);

    glGetActiveUniformName(id(), uniformIndex, length, nullptr, name.data());
#else
    GLint length = get(GL_ACTIVE_UNIFORM_MAX_LENGTH);
    std::vector<char> name(length);

    glGetActiveUniform(id(), uniformIndex, length, &length, nullptr, nullptr, name.data());
#endif

    return std::string(name.data(), length);
}

UniformBlock * Program::uniformBlock(const GLuint uniformBlockIndex)
{
    return getUniformBlockByIdentity(uniformBlockIndex);
}

UniformBlock * Program::uniformBlock(const std::string& name)
{
    return getUniformBlockByIdentity(name);
}

UniformBlock * Program::getUniformBlockByIdentity(const LocationIdentity & identity)
{
    checkDirty();

    if (m_uniformBlocks.find(identity) == m_uniformBlocks.end())
        m_uniformBlocks[identity] = UniformBlock(this, identity);

    return &m_uniformBlocks[identity];
}

void Program::addUniform(AbstractUniform * uniform)
{
    assert(uniform != nullptr);

    ref_ptr<AbstractUniform>& uniformReference = m_uniforms[uniform->identity()];

	if (uniformReference)
		uniformReference->deregisterProgram(this);

	uniformReference = uniform;

	uniform->registerProgram(this);

	if (m_linked)
		uniform->update(this);
}

void Program::updateUniforms() const
{
	// Note: uniform update will check if program is linked
    for (std::pair<LocationIdentity, ref_ptr<AbstractUniform>> uniformPair : m_uniforms)
		uniformPair.second->update(this);
}

void Program::updateUniformBlockBindings() const
{
    for (std::pair<LocationIdentity, UniformBlock> pair : m_uniformBlocks)
        pair.second.updateBinding();
}

void Program::setBinary(ProgramBinary * binary)
{
    if (m_binary == binary)
        return;

    if (m_binary)
        m_binary->deregisterListener(this);

    m_binary = binary;

    if (m_binary)
        m_binary->registerListener(this);
}

ProgramBinary * Program::getBinary() const
{
    return binaryImplementation().getProgramBinary(this);
}

GLint Program::get(const GLenum pname) const
{
    GLint value = 0;
    glGetProgramiv(id(), pname, &value);

	return value;
}

void Program::getActiveAttrib(binding::GLuint index, binding::GLsizei bufSize, binding::GLsizei * length, binding::GLint * size, binding::GLenum * type, binding::GLchar * name) const
{
    checkDirty();

    glGetActiveAttrib(id(), index, bufSize, length, size, type, name);
}

const std::string Program::infoLog() const
{
    GLint length = get(GL_INFO_LOG_LENGTH);

    if (length == 0)
        return std::string();

    std::vector<char> log(length);

    glGetProgramInfoLog(id(), length, &length, log.data());

	return std::string(log.data(), length);
}

void Program::dispatchCompute(const glm::uvec3 & numGroups)
{
    dispatchCompute(numGroups.x, numGroups.y, numGroups.z);
}

void Program::dispatchCompute(const GLuint numGroupsX, const GLuint numGroupsY, const GLuint numGroupsZ)
{
    use();

    if (!m_linked)
        return;

    glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
}

#ifdef GLOBJECTS_GL_BINDING
void Program::dispatchComputeGroupSize(const GLuint numGroupsX, const GLuint numGroupsY, const GLuint numGroupsZ, const GLuint groupSizeX, const GLuint groupSizeY, const GLuint groupSizeZ)
{
    use();

    if (!m_linked)
        return;

    glDispatchComputeGroupSizeARB(numGroupsX, numGroupsY, numGroupsZ, groupSizeX, groupSizeY, groupSizeZ);
}

void Program::dispatchComputeGroupSize(const glm::uvec3 & numGroups, const glm::uvec3 & groupSizes)
{
    dispatchComputeGroupSize(numGroups.x, numGroups.y, numGroups.z, groupSizes.x, groupSizes.y, groupSizes.z);
}

void Program::setShaderStorageBlockBinding(const GLuint storageBlockIndex, const GLuint storageBlockBinding) const
{
	checkDirty();
    if (!m_linked)
        return;

    glShaderStorageBlockBinding(id(), storageBlockIndex, storageBlockBinding);
}

GLenum Program::objectType() const
{
    return GL_PROGRAM;
}
#endif

} // namespace globjects
