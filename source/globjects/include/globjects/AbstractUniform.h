#pragma once

#include <string>
#include <set>
#include <vector>
#include <array>

#include <glm/fwd.hpp>

#include <globjects/base/Referenced.h>

#include <globjects/globjects_api.h>

#include <globjects/LocationIdentity.h>
#include <globjects/TextureHandle.h>

namespace globjects
{

class Program;
template<typename T> class Uniform;

/** \brief Abstract base class for templated Uniforms.
 *
 * Unifies the specialized Uniforms in order to be able to store them in a list or a vector.
 *
 * \see Uniform
 * \see Program
 */
class GLOBJECTS_API AbstractUniform : public Referenced
{
	friend class Program; ///< Programs (de)register themselves.

public:
    enum BindlessImplementation
    {
        SeparateShaderObjectsARB
    ,   Legacy
    };

    static void hintBindlessImplementation(const BindlessImplementation impl);

public:
    AbstractUniform(binding::GLint location);
	AbstractUniform(const std::string & name);

	const std::string & name() const;
    binding::GLint location() const;

    const LocationIdentity & identity() const;

    /** Simplifies the often required casting of AbstractUniforms.
     *
     * @return a specialized Uniform of the requested type, returns a nullptr on a type mismatch
     *
     * \code{.cpp}
     * abstractUniform->as<float>()->setValue(3.142f);
     * \endcode
	*/
	template<typename T> Uniform<T> * as();
    template<typename T> const Uniform<T> * as() const;

protected:
    virtual ~AbstractUniform();

	void registerProgram(Program * program);
	void deregisterProgram(Program * program);

	/** Iterates over all programs attached to and calls update.
		Should be called on every value change (i.e., in Uniform).
	*/
	void changed();

	/** Sets the uniform's value on the program.
	*/
    void update(const Program * program) const;

	/** This function requires knowledge of the unifom's value.
	*/
    virtual void updateAt(const Program * program, binding::GLint location) const = 0;

    binding::GLint locationFor(const Program * program) const;

protected:
    void setValue(const Program * program, binding::GLint location, const float & value) const;
    void setValue(const Program * program, binding::GLint location, const int & value) const;
    void setValue(const Program * program, binding::GLint location, const unsigned int & value) const;
    void setValue(const Program * program, binding::GLint location, const bool & value) const;

    void setValue(const Program * program, binding::GLint location, const glm::vec2 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::vec3 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::vec4 & value) const;

    void setValue(const Program * program, binding::GLint location, const glm::ivec2 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::ivec3 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::ivec4 & value) const;

    void setValue(const Program * program, binding::GLint location, const glm::uvec2 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::uvec3 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::uvec4 & value) const;

    void setValue(const Program * program, binding::GLint location, const glm::mat2 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::mat3 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::mat4 & value) const;

    void setValue(const Program * program, binding::GLint location, const glm::mat2x3 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::mat3x2 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::mat2x4 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::mat4x2 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::mat3x4 & value) const;
    void setValue(const Program * program, binding::GLint location, const glm::mat4x3 & value) const;

    void setValue(const Program * program, binding::GLint location, const TextureHandle & value) const;

    void setValue(const Program * program, binding::GLint location, const std::vector<float> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<int> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<unsigned int> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<bool> & value) const;

    void setValue(const Program * program, binding::GLint location, const std::vector<glm::vec2> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::vec3> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::vec4> & value) const;

    void setValue(const Program * program, binding::GLint location, const std::vector<glm::ivec2> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::ivec3> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::ivec4> & value) const;

    void setValue(const Program * program, binding::GLint location, const std::vector<glm::uvec2> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::uvec3> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::uvec4> & value) const;

    void setValue(const Program * program, binding::GLint location, const std::vector<glm::mat2> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::mat3> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::mat4> & value) const;

    void setValue(const Program * program, binding::GLint location, const std::vector<glm::mat2x3> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::mat3x2> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::mat2x4> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::mat4x2> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::mat3x4> & value) const;
    void setValue(const Program * program, binding::GLint location, const std::vector<glm::mat4x3> & value) const;

    void setValue(const Program * program, binding::GLint location, const std::vector<TextureHandle> & value) const;

    template <typename T, std::size_t Count>
    void setValue(const Program * program, binding::GLint location, const std::array<T, Count> & value) const;

protected:
    LocationIdentity m_identity;
    std::set<Program *> m_programs;
};

} // namespace globjects

#include <globjects/AbstractUniform.hpp>
