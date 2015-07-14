#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/gl/bitfield.h>

namespace globjects
{

namespace binding
{
    using namespace ::gl;
}

}

#else

#include <glesbinding/gles/bitfield.h>

namespace globjects
{

namespace binding
{
    using namespace ::gles;
}

}

#endif
