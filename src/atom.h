#ifndef atom_h
#define atom_h

#include "variable.h"

template <class T>
class atom
{
    private:
        
        variable <T> m_variable;
        T m_rhs;

    public:
        
        atom (const variable<T> & var, const T & rhs):
            m_variable (var),
            m_rhs (rhs)
        {}

        atom (const atom & a):
            m_variable (a.m_variable),
            m_rhs (a.m_rhs)
        {}

        const variable <T> & get_variable() const
        {
            return m_variable;
        }

        const T & get_rhs () const
        {
            return m_rhs;
        }

        bool operator < (const atom & a) const
        {
	  return ((m_variable == a.m_variable) ? (m_rhs < a.m_rhs) : (m_variable < a.m_variable));
        }
        
        bool operator == (const atom & a) const
        {
            return ((m_variable == a.m_variable)and(m_rhs== a.m_rhs));
        }
        ~atom()
        {}
};

template <class T>
std::ostream & operator << (std::ostream &, const atom<T> & );


#endif
