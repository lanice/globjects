#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/gl/functions.h>

namespace globjects
{

namespace binding
{
    using namespace ::gl;
}

}

#else

#include <glesbinding/gles/functions.h>

namespace globjects
{

namespace binding
{
    using namespace ::gles;
}

}

#endif
