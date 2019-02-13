#include <cstdlib>
#include <iostream>

#include "encoder.h"


int main (int argc, char * argv [])
{
    try
    {
        bound <int> b (0,5), b1(0,3), b2(2,6);
        variable <int> x (b);
        variable <int> y (b);
        variable <int> z (b1);
	variable <int> t (b2);
	int c = 14;
        std::cout << "c=" << c << std::endl;
        
        std::vector < variable <int> > vars;
        vars.push_back(x);
        vars.push_back(y);
         

        for (const variable<int> & v : vars)
            std::cout << "x_" << v.get_symbol() << " in " << v.get_bound() << std::endl;

        inequation <int> ineq;
        ineq.emplace (x,3);
        ineq.emplace (y,5);
	ineq.emplace (z,4);
	ineq.emplace (t,1);

        ineq.set_type(E_INEQ_TYPE::LE);
        ineq.set_rhs(c);

	std::cout << ineq << std::endl;
     
        encoder<int> e (ineq);
	


        std::vector <clause<int>> clauses(e.encode("output.dimacs",E_TYPE_ENCODING::ORDER));

        /*for (const clause <int> & C : clauses)
        {
            std::cout << C << std::endl;
        }*/
    }
    catch (const std::exception & e)

    {
        std::cout << e.what() << std::endl;
    
        return EXIT_SUCCESS;
    }
} 
