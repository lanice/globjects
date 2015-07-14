#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/Meta.h>

namespace globjects
{

namespace binding
{
    using namespace ::glbinding;
}

}

#else

#include <glesbinding/Meta.h>

namespace globjects
{

namespace binding
{
    using namespace ::glesbinding;
}

}

#endif
