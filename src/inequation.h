#ifndef inequation_h
#define inequation_h

#include <map>

#include "variable.h"

enum E_INEQ_TYPE
{
    EQ,                 // equal 
    NEQ,                // not equal
    LE,                 // less or equal
    GE,                 // great or equal
    L,                 // strictly less
    G                  // strictly great                          
};
typedef enum E_INEQ_TYPE E_INEQ_TYPE;


template <class T>
class inequation : public std::map <variable <T>, T>
{
    private:
       
       E_INEQ_TYPE m_type;
       T m_rhs;
     
    public:
          
        inequation ():
            std::map<variable<T>,T>()
        {}

        inequation (const inequation & in):
            std::map <variable<T>,T> (in),
            m_type(in.m_type),
            m_rhs (in.m_rhs)
        {}

        void set_type (E_INEQ_TYPE type)
        {
            m_type = type;
        }

        E_INEQ_TYPE get_type () const
        {
            return m_type;
        }
        
        const T & get_rhs () const
        {
            return m_rhs;
        }

        void set_rhs (const T & rhs)
        {
            m_rhs = rhs;
        }

        std::vector <variable<T>> get_variables () const
        {
            std::vector <variable<T>> vars;
            
            for (typename std::map<variable<T>,T>::const_iterator i = this->begin(); i != this->end(); ++i)
                vars.push_back((*i).first);
            
            return vars;
        }

	void into_primitive ()
	{
	  switch (m_type)
	  {
	    case E_INEQ_TYPE::EQ:
	      break ;
	    
	    case E_INEQ_TYPE::NEQ:
	      break ;
	    case E_INEQ_TYPE::LE:
	      break ; 
	    case E_INEQ_TYPE::GE:
	      break ;
	    case E_INEQ_TYPE::L:
	      
	      break ;
	    case E_INEQ_TYPE::G:
	      break ;
	  }
	}
};

template <class T>
std::ostream & operator << (std::ostream &, const inequation<T> &);

#endif
