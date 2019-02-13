#include "literal.h"


template <class T>
std::ostream & operator << (std::ostream & os, const literal <T> & l)
{
    return os << (l.is_neg() ? "-" : "") << l.get_atom() ;
}

template std::ostream & operator << <int> (std::ostream &, const literal <int> &);
