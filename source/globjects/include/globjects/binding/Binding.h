#pragma once

#ifdef GLOBJECTS_GL_BINDING

#include <glbinding/Binding.h>

namespace globjects
{

namespace binding
{
    using glbinding::Binding;
}

}

#else

#include <glesbinding/Binding.h>

namespace globjects
{

namespace binding
{
    using glesbinding::Binding;
}

}

#endif
