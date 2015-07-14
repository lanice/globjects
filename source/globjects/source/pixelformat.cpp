#include "pixelformat.h"

#include <globjects/binding/enum.h>

#include <globjects/globjects.h>
#include <globjects/logging.h>


namespace 
{

using namespace globjects::binding;

int nextMultiple(const int n, const int k)
{
    return n + (k-n%k)%k;
}

int byteSize(const GLenum type)
{
    switch (type)
    {
        case GL_UNSIGNED_BYTE:
        case GL_BYTE:
            return 1;

        case GL_UNSIGNED_SHORT:
        case GL_SHORT:
            return 2;

        case GL_UNSIGNED_INT:
        case GL_INT:
            return 4;

        case GL_HALF_FLOAT:
            return 2;

        case GL_FLOAT:
            return 4;

        default:
            return 1;
    }
}

int numberOfComponents(const GLenum format)
{
    switch (format)
    {
        case GL_RED:
        case GL_GREEN:
        case GL_BLUE:
#ifdef GLOBJECTS_GL_BINDING
        case GL_RED_INTEGER:
        case GL_GREEN_INTEGER:
        case GL_BLUE_INTEGER:
#endif

        case GL_ALPHA:
        case GL_LUMINANCE:
        case GL_LUMINANCE_ALPHA:

        case GL_STENCIL_INDEX:
#ifdef GLOBJECTS_GL_BINDING
        case GL_COLOR_INDEX:
#endif
        case GL_DEPTH_COMPONENT:
        case GL_DEPTH_STENCIL:
            return 1;

        case GL_RG:
        case GL_RG_INTEGER:
            return 2;

        case GL_RGB:
#ifdef GLOBJECTS_GL_BINDING
        case GL_BGR:
#endif
        case GL_RGB_INTEGER:
#ifdef GLOBJECTS_GL_BINDING
        case GL_BGR_INTEGER:
#endif
            return  3;

        case GL_RGBA:
#ifdef GLOBJECTS_GL_BINDING
        case GL_BGRA:
#else
        case GL_BGRA_EXT:
#endif
        case GL_RGBA_INTEGER:
#ifdef GLOBJECTS_GL_BINDING
        case GL_BGRA_INTEGER:
#endif
            return 4;
        default:
            return 1;
    }
}

int bytesPerPixel(const GLenum format, const GLenum type)
{
    switch (type) // several components encoded in type, disregard component count
    {
#ifdef GLOBJECTS_GL_BINDING
        case GL_UNSIGNED_BYTE_3_3_2:
        case GL_UNSIGNED_BYTE_2_3_3_REV:
            return 1; // 8 bit
#endif

        case GL_UNSIGNED_SHORT_5_6_5:
        case GL_UNSIGNED_SHORT_4_4_4_4:
        case GL_UNSIGNED_SHORT_5_5_5_1:
#ifdef GLOBJECTS_GL_BINDING
        case GL_UNSIGNED_SHORT_5_6_5_REV:
        case GL_UNSIGNED_SHORT_4_4_4_4_REV:
        case GL_UNSIGNED_SHORT_1_5_5_5_REV:
#endif
            return 2; // 16 bit

#ifdef GLOBJECTS_GL_BINDING
        case GL_UNSIGNED_INT_8_8_8_8:
        case GL_UNSIGNED_INT_8_8_8_8_REV:
        case GL_UNSIGNED_INT_10_10_10_2:
#endif
        case GL_UNSIGNED_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_24_8:
        case GL_UNSIGNED_INT_10F_11F_11F_REV:
        case GL_UNSIGNED_INT_5_9_9_9_REV:
        case GL_FLOAT_32_UNSIGNED_INT_24_8_REV:
            return 4; // 32 bit

        default:
            break;
    }

    return numberOfComponents(format) * byteSize(type);
}

}

namespace globjects {

using namespace binding;

int imageSizeInBytes(const int width, const int height, const GLenum format, const GLenum type)
{
#ifdef GLOBJECTS_GL_BINDING
    if (type == GL_BITMAP)
    {
        // handle differently?
        warning() << "imageSizeInBytes: GL_BITMAP not implemented yet";
        return -1;
    }
#endif

    int pixelSize = bytesPerPixel(format, type);

    int rowSize = pixelSize * width;

    int alignment = getInteger(GL_PACK_ALIGNMENT); // can be 1, 2, 4 or 8

    rowSize = nextMultiple(rowSize, alignment);

    return rowSize * height;
}

} // namespace globjects
