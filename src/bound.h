#ifndef bound_h
#define bound_h

#include <vector>
#include <iostream>


template <class T>
class bound
{
    private:
        
        T m_lower;
        T m_upper;

        T m_step;
        
    public:

        bound (const T & lower, const T & upper):
            m_lower (lower),
            m_upper (upper)
        {
            if (sizeof(T) == sizeof(int) )
            {
                m_step = 1;
            }

            if (m_lower > m_upper)
            {
                m_lower = m_upper;
                m_upper = lower;
            }
        }
        
        bound (const bound & b):
            m_lower (b.m_lower),
            m_upper (b.m_upper),
            m_step (b.m_step)
        {}
        
        const T & get_lower () const
        {
            return m_lower;
        }

        const T & get_upper () const
        {
            return m_upper;
        }

        const T & get_step () const
        {
            return m_step;
        }
        
        std::vector <T> as_vector () const
        {
            std::vector <T> bnd;
            for (T i = m_lower; i <= m_upper; i += m_step)
            {
                bnd.push_back (i);
            }
            return bnd;
        }


        ~bound()
        {}
};

template <class T>
std::ostream & operator << (std::ostream & os, const bound <T> & b);

#endif
