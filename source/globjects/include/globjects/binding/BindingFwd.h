#pragma once

#ifdef GLOBJECTS_GL_BINDING

namespace glbinding
{

class Binding;

}

namespace globjects
{

namespace binding
{
    using glbinding::Binding;
}

}

#else

namespace glesbinding
{

class Binding;

}

namespace globjects
{

namespace binding
{
    using glesbinding::Binding;
}

}

#endif
