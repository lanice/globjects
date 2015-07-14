#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/gl/enum.h>

namespace globjects
{

namespace binding
{
    using namespace ::gl;
}

}

#else

#include <glesbinding/gles/enum.h>

namespace globjects
{

namespace binding
{
    using namespace ::gles;
}

}

#endif
