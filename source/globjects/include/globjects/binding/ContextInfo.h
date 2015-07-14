#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/ContextInfo.h>

namespace globjects
{

namespace binding
{
    using glbinding::ContextInfo;
}

}

#else

#include <glesbinding/ContextInfo.h>

namespace globjects
{

namespace binding
{
    using glesbinding::ContextInfo;
}

}

#endif
