#ifndef encoder_h
#define encoder_h

#include "inequation.h"
#include "clause.h"

enum E_TYPE_ENCODING
{
  DIRECT,
  SUPPORT,
  ORDER
};
typedef enum E_TYPE_ENCODING E_TYPE_ENCODING;

template <class T>
class encoder
{ 
    private:
        
        inequation <T> m_ineq;

    public:
        
        encoder (const inequation<T> & ineq):
            m_ineq (ineq)
        {}

        std::vector <clause<T>> encode (const char * dimacs, E_TYPE_ENCODING type) const;

        ~encoder()
        {}

};

#endif
