#include "bound.h"


template <class T>
std::ostream & operator << (std::ostream & os, const bound <T> & b)
{
    return os << '[' << b.get_lower() << "," << b.get_upper() << ']' ;
}

template std::ostream & operator << <int> (std::ostream & , const bound <int> &);
