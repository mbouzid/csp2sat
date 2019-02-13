#include "inequation.h"


template <class T>
std::ostream & operator << (std::ostream & os, const inequation<T> & ineq)
{
    std::vector <variable<T>> vars (ineq.get_variables());
    
    typename std::vector<variable<T>>::iterator first = vars.begin();
    typename std::vector<variable<T>>::iterator last = vars.end();
         
    if (first != last)
    {
        os << (ineq.at((*first)) > 0 ? "" : "-" ) ;
        os << (abs(ineq.at(*first)) == 1 ? "" : std::to_string(abs(ineq.at(*first)))) ;
        os << "x_" << (*first).get_symbol() ;
            
        first = std::next(first);
        while (first != last)
        {
            os << (ineq.at((*first)) > 0 ? "+" : "-" ) ;
            os << (abs(ineq.at(*first)) == 1 ? "" : std::to_string(abs(ineq.at(*first)))) ;
            os << "x_" << (*first).get_symbol() ;
            ++first; 
        } 
    }
    
    switch (ineq.get_type())
    {
        case E_INEQ_TYPE::EQ:
            os << "==";
            break ;
        case E_INEQ_TYPE::NEQ:
            os << "!=";
            break ;
        case E_INEQ_TYPE::LE:
            os << "<=";
            break ; 
        case E_INEQ_TYPE::GE:
            os << ">=";
            break ;
        case E_INEQ_TYPE::L:
            os << "<";
            break ;
        case E_INEQ_TYPE::G:
            os << "<";
            break ;
    }

    return os << ineq.get_rhs() ;
}


template std::ostream & operator << <int>(std::ostream & os, const inequation<int> & ineq);
