
#include "ProgramBinaryImplementation_None.h"

#include <globjects/binding/functions.h>
#include <globjects/binding/boolean.h>

#include <globjects/Program.h>


namespace globjects 
{

bool ProgramBinaryImplementation_None::updateProgramLinkSource(const Program * program) const
{
    return program->compileAttachedShaders();
}

ProgramBinary * ProgramBinaryImplementation_None::getProgramBinary(const Program * /*program*/) const
{
    return nullptr;
}

} // namespace globjects
