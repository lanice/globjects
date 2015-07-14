#pragma once

#include <vector>

#include <globjects/binding/types.h>

#include <globjects/globjects_api.h>

#include <globjects/base/Referenced.h>
#include <globjects/base/ChangeListener.h>
#include <globjects/base/Changeable.h>
#include <globjects/base/ref_ptr.h>

namespace globjects
{

class AbstractStringSource;


/**
 * \brief The ProgramBinary class is used for directly setting binary sources for a Program.
 *
 * \see Program
 * \see http://www.opengl.org/registry/specs/ARB/get_program_binary.txt
 */
class GLOBJECTS_API ProgramBinary : public Referenced, public Changeable, protected ChangeListener
{
public:
    ProgramBinary(binding::GLenum binaryFormat, const std::vector<char> & binaryData);
    ProgramBinary(binding::GLenum binaryFormat, AbstractStringSource * dataSource);

    binding::GLenum format() const;
    const void * data() const;
    binding::GLsizei length() const;

     virtual void notifyChanged(const Changeable* sender) override;

protected:
    virtual ~ProgramBinary();

    void validate() const;

protected:
    binding::GLenum m_binaryFormat;
    ref_ptr<AbstractStringSource> m_dataSource;

    mutable bool m_valid;
    mutable std::vector<unsigned char> m_binaryData;
};

} // namespace globjects
