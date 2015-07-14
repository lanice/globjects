
#include "AbstractProgramBinaryImplementation.h"

#include <globjects/globjects.h>

#ifdef GLOBJECTS_GL_BINDING
#include "ProgramBinaryImplementation_GetProgramBinaryARB.h"
#endif
#include "ProgramBinaryImplementation_None.h"


namespace globjects 
{

using namespace binding;

AbstractProgramBinaryImplementation::AbstractProgramBinaryImplementation()
{
}

AbstractProgramBinaryImplementation::~AbstractProgramBinaryImplementation()
{
}

AbstractProgramBinaryImplementation * AbstractProgramBinaryImplementation::get(const Program::BinaryImplementation impl)
{
#ifdef GLOBJECTS_GL_BINDING
    if (impl == Program::BinaryImplementation::GetProgramBinaryARB 
     && hasExtension(GLextension::GL_ARB_get_program_binary))
    {
        return ProgramBinaryImplementation_GetProgramBinaryARB::instance();
    }
    else
    {
        return ProgramBinaryImplementation_None::instance();
    }
#else
    (void) impl; // unused

    return ProgramBinaryImplementation_None::instance();
#endif
}

} // namespace globjects
