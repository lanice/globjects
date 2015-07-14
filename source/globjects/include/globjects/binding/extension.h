#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/gl/extension.h>

namespace globjects
{

namespace binding
{
    using namespace ::gl;
}

}

#else

#include <glesbinding/gles/extension.h>

namespace globjects
{

namespace binding
{
    using namespace ::gles;
}

}

#endif
