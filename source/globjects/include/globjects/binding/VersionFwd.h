#pragma once

#ifdef GLOBJECTS_GL_BINDING

namespace glbinding
{

class Version;

}

namespace globjects
{

namespace binding
{
    using glbinding::Version;
}

}

#else

namespace glesbinding
{

class Version;

}

namespace globjects
{

namespace binding
{
    using glesbinding::Version;
}

}

#endif
