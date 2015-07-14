#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/ContextHandle.h>

namespace globjects
{

namespace binding
{
    using glbinding::ContextHandle;
    using glbinding::getCurrentContext;
}

}

#else

#include <glesbinding/ContextHandle.h>

namespace globjects
{

namespace binding
{
    using glesbinding::ContextHandle;
    using glesbinding::getCurrentContext;
}

}

#endif
