#ifndef clause_h
#define clause_h

#include <vector>
#include "literal.h"

template <class T>
class clause : public std::vector <literal<T>>  {};


template <class T>
std::ostream & operator << (std::ostream & , const clause <T> & );

#endif
