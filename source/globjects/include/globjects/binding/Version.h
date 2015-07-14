#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/Version.h>

namespace globjects
{

namespace binding
{
    using glbinding::Version;
}

}

#else

#include <glesbinding/Version.h>

namespace globjects
{

namespace binding
{
    using glesbinding::Version;
}

}

#endif
