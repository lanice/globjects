#pragma once

#include <string>
#include <vector>
#include <map>

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>

#include <globjects/base/Changeable.h>
#include <globjects/base/ChangeListener.h>
#include <globjects/base/ref_ptr.h>

#include <globjects/Object.h>

namespace globjects 
{
class AbstractStringSource;

/** \brief Encapsulates OpenGL shaders.
    
    A shader can be constructed using an AbstractStringSource.
    A shader can be attached to a program using
    Program::attach(). A Shader subclasses either ChangeListener and Changeable
    to react to changing shader sources and to propagate this change to 
    ChangeListeners.

    \see  http://www.opengl.org/wiki/Shader

    \see Program
    \see ShaderSource
    \see ChangeListener
    \see Changeable
 */
class GLOBJECTS_API Shader : public Object, protected ChangeListener, public Changeable
{
    friend class Program;

public:
    using IncludePaths = std::vector<std::string>;

public:
    enum class IncludeImplementation
    {
        ShadingLanguageIncludeARB
    ,   Fallback
    };

    static void hintIncludeImplementation(IncludeImplementation impl);

public:
    static Shader * fromString(const binding::GLenum type, const std::string & sourceString, const IncludePaths & includePaths = IncludePaths());
    static Shader * fromFile(const binding::GLenum type, const std::string & filename, const IncludePaths & includePaths = IncludePaths());

    static void globalReplace(const std::string & search, const std::string & replacement);
    static void globalReplace(const std::string & search, int i);
    static void clearGlobalReplacements();

public:
    Shader(const binding::GLenum type);
    Shader(const binding::GLenum type, AbstractStringSource * source, const IncludePaths & includePaths = IncludePaths());

    virtual void accept(ObjectVisitor& visitor) override;

	binding::GLenum type() const;

    void setSource(AbstractStringSource * source);
	void setSource(const std::string & source);
    const AbstractStringSource* source() const;
    void updateSource();

    const IncludePaths & includePaths() const;
    void setIncludePaths(const IncludePaths & includePaths);

    bool compile() const;
	bool isCompiled() const;
    void invalidate();

    binding::GLint get(binding::GLenum pname) const;
    std::string getSource() const;
    bool checkCompileStatus() const;
	std::string infoLog() const;

    std::string typeString() const;

#ifdef GLOBJECTS_GL_BINDING
    virtual binding::GLenum objectType() const override;
#endif

    static std::string typeString(binding::GLenum type);

protected:
    virtual ~Shader();

    virtual void notifyChanged(const Changeable * changeable) override;

protected:
    std::string shaderString() const;

protected:
	binding::GLenum m_type;
    ref_ptr<AbstractStringSource> m_source;
    IncludePaths m_includePaths;

    mutable bool m_compiled;
    mutable bool m_compilationFailed;

    static std::map<std::string, std::string> s_globalReplacements;
};

} // namespace globjects
