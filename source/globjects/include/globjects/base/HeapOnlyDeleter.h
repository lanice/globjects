#pragma once

#include <globjects/globjects_api.h>


namespace globjects 
{

class HeapOnly;

/** \brief The HeapOnly class
    Restricts creation to heap

    \see http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Requiring_or_Prohibiting_Heap-based_Objects
 */
class GLOBJECTS_API HeapOnlyDeleter
{
public:
    HeapOnlyDeleter();

    void operator()(HeapOnly * ptr) const;
};

} // namespace globjects
