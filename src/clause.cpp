#include "clause.h"

template <class T>
std::ostream & operator << (std::ostream & os, const clause <T> & c)
{
    typename clause<T>::const_iterator first = c.cbegin();
    typename clause<T>::const_iterator last = c.cend();

    os << "[";

    if (first != last)
    {
        os << (*first);
        first = std::next(first);

        while (first != last)
        {
            os << ";" << (*first);
            ++first;
        }
    }
    
    return os << "]";
}

template std::ostream & operator << <int>(std::ostream & os, const clause<int> & c);
