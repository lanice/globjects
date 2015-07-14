#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/gl/types.h>

namespace globjects
{

namespace binding
{
    using namespace ::gl;
}

}

#else

#include <glesbinding/gles/types.h>

namespace globjects
{

namespace binding
{
    using namespace ::gles;
}

}

#endif
