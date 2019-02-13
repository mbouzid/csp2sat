#include "variable.h"

template <class T>
size_t variable<T>::s_symbol = 0;

template <class T>
std::ostream & operator << (std::ostream & os, const variable <T> & v)
{
    return os << v.get_symbol();
}

template std::ostream & operator << <int> (std::ostream &, const variable <int> & );
template size_t variable<int>::s_symbol ;
