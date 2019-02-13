#ifndef literal_h
#define literal_h

#include "atom.h"

template <class T>
class literal
{
    private:
        
        atom <T> m_atom;
        bool m_negative;

    public:

        literal (const atom <T> & a, bool negative = false):
            m_atom (a),
            m_negative(negative)
        {}

        literal (const literal & l):
            m_atom (l.m_atom),
            m_negative (l.m_negative)
        {}


        bool is_neg() const
        {
            return m_negative;
        }
        
        bool operator < (const literal & l) const
        {
            return (m_atom < l.m_atom);
        }
        
        const atom<T> & get_atom() const
        {
            return m_atom;
        }

        ~literal()
        {}
};

template <class T>
std::ostream & operator << (std::ostream &, const literal <T> & );

#endif
