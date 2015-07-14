#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/gl/values.h>

namespace globjects
{

namespace binding
{
    using namespace ::gl;
}

}

#else

#include <glesbinding/gles/values.h>

namespace globjects
{

namespace binding
{
    using namespace ::gles;
}

}

#endif
