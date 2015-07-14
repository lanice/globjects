#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/gl/boolean.h>

namespace globjects
{

namespace binding
{
    using namespace ::gl;
}

}

#else

#include <glesbinding/gles/boolean.h>

namespace globjects
{

namespace binding
{
    using namespace ::gles;
}

}

#endif
