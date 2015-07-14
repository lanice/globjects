#pragma once

#ifdef GLOBJECTS_GL_BINDING

namespace glbinding
{

class ContextInfo;

}

namespace globjects
{

namespace binding
{
    using glbinding::ContextInfo;
}

}

#else

namespace glesbinding
{

class ContextInfo;

}

namespace globjects
{

namespace binding
{
    using glesbinding::ContextInfo;
}

}

#endif
