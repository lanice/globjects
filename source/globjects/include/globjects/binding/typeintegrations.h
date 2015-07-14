#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/gl/typeintegrations.h>

namespace globjects
{

namespace binding
{
    using namespace ::gl;
}

}

#else

#include <glesbinding/gles/typeintegrations.h>

namespace globjects
{

namespace binding
{
    using namespace ::gles;
}

}

#endif
