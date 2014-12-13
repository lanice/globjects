#include <globjects/base/HeapOnlyDeleter.h>

#include <globjects/base/HeapOnly.h>

namespace globjects {

HeapOnlyDeleter::HeapOnlyDeleter()
{
}

void HeapOnlyDeleter::operator()(HeapOnly * ptr) const
{
    ptr->destroy();
}

} // namespace globjects
