#pragma once

#include <globjects/binding/types.h>

namespace globjects {

int imageSizeInBytes(int width, int height, binding::GLenum format, binding::GLenum type);

} // namespace globjects
