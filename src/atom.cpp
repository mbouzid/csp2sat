#include "atom.h"

template <class T>
std::ostream & operator << (std::ostream & os, const atom<T> & a)
{
    return os << "p(x_" << a.get_variable().get_symbol() << "," << a.get_rhs() << ")";
}


template std::ostream & operator << <int>(std::ostream & os, const atom<int> & a);
