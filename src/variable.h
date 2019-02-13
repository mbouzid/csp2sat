#ifndef variable_h
#define variable_h

#include <cstdlib>
#include "bound.h"

template <class T>
class variable
{
    private:
        
        static size_t s_symbol;
        size_t m_symbol;
        bound <T> m_bound;

    public:
        
        variable (const bound <T> & b):
            m_symbol (++s_symbol),
            m_bound (b)
        {}
    
        
        variable (const variable & v ):
            m_symbol (v.m_symbol),
            m_bound (v.m_bound)
        {}

        bool operator < (const variable & v) const
        {
            return (m_symbol < v.m_symbol);
        }
	
	bool operator == (const variable & v) const
	{
	  return (m_symbol == v.m_symbol);
	}

        const bound <T> & get_bound() const
        {
            return m_bound;
        }
        
        size_t get_symbol() const
        {
            return m_symbol;
        }

        ~variable ()
        {}
};


template <class T>
std::ostream & operator << (std::ostream & os, const variable <T> & v);

#endif
