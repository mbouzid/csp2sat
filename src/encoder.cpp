#include "encoder.h"
#include "tree.h"
#include <fstream>
template <class T> 
std::vector <clause<T>> encoder<T>::encode (const char * dimacs, E_TYPE_ENCODING type) const
{
    std::vector <variable <T> > vars (m_ineq.get_variables()); 
    T cond_c (0);
    
    std::cout << "Test condition on right hand side..." ;
    for (const variable <T> & x : vars)
        cond_c += m_ineq.at(x) * x.get_bound().get_lower();
            
        
    if (not(m_ineq.get_rhs() >= cond_c))
    {
      std::cerr << "[BAD] Unsatified condition on right hand side: " << m_ineq.get_rhs() << "<"<< cond_c << std::endl; 
      exit(EXIT_FAILURE); 
    }
    else
      std::cout << "[OK]" << std::endl;

    // shift domain
    std::cout << "Shifting domain of variables according to their coefficients...";
    std::vector <variable <T> > nvars, nvars1;
    for (auto pair : m_ineq)
    {
        variable <T> x (pair.first);
        T coeff (pair.second);
        bound <T> nbound ((x.get_bound().get_lower()*coeff)-1,x.get_bound().get_upper()*coeff);
        bound <T> nbound1(x.get_bound().get_lower()*coeff,x.get_bound().get_upper()*coeff);
 
	
	nvars.push_back(variable<T> (nbound));
	nvars1.push_back(variable<T>(nbound1));
    }

    std::cout << "[OK]" << std::endl;


    size_t n = vars.size();
    T sum_bi (m_ineq.get_rhs()-n+1);

    std::cout << "Sum of b_i is " << sum_bi << std::endl;

   
    std::vector < clause<T> > clauses;
    std::set<atom<T>> atoms;


    if (type == E_TYPE_ENCODING::DIRECT)
    {
      // boolean variables
      for (const variable<T> & x : vars)
      {
	for (const T & i : x.get_bound().as_vector())
	{
	  atom <T> a (x,i);
	  atoms.insert(a);
	}
      }

      // At-least-one 
      for (const variable<T> & x : vars)
      {
	clause <T> c1;
	for (const T & i : x.get_bound().as_vector())
	{
	  atom <T> a (x,i);
	  c1.push_back(literal<T>(a));
	}
	clauses.push_back(c1);
      }    
  
      // At-most-one 
      for (const variable <T> & x : vars)
      {
	for (const T & i : x.get_bound().as_vector())
	{
	  for (const T & j : x.get_bound().as_vector())
	  {
	    if (i < j)
	    {
	      clause<T> c1;

	      atom<T> ai (x,i), aj (x,j);
	      c1.push_back(literal<T>(ai,true));
	      c1.push_back(literal<T>(aj,true));

	      clauses.push_back(c1);
	    }
	  }
	}
      }
   
      // Conflicts points
      node <T> * t = new node<T> (0);
    
      node<T>::full_tree(t,nvars1);

      std::vector <std::vector<T>> conflicts;
      node<T>::get_conflicts(t,conflicts,sum_bi,0);
	
      delete (t);

      for (const std::vector<T> & conflict : conflicts)
      {
	  size_t m = conflict.size();
	
	  clause <T> c1;
	  for (size_t i = 0; i < m; ++i)
	  {
            size_t k = (n-i)-1;
	    atom <T> a1 (vars.at(k),conflict.at(i));
	 
	    atoms.insert(a1);
	    c1.push_back(literal<T>(a1,true));
	  }
	  clauses.push_back(c1);
     }

    }// end direct encoding
    
    if (type == E_TYPE_ENCODING::SUPPORT)
    {
      // boolean variables
      for (const variable<T> & x : vars)
      {
	for (const T & i : x.get_bound().as_vector())
	{
	  atom <T> a (x,i);
	 atoms.insert(a);
	}
      }

    }// end support encoding

    if (type == E_TYPE_ENCODING::ORDER)
    {
      // boolean variables
      for (const variable<T> & x : vars)
      {
	T lb(x.get_bound().get_lower()-1), ub(x.get_bound().get_upper());

	for (T i = lb; i <= ub; i+=x.get_bound().get_step())
	{
	  atom <T> a (x,i);
	  atoms.insert(a);
	}
      }
      
      // bound and order clauses
      for (const variable<T> & x : vars)
      {
	T lb(x.get_bound().get_lower()-1), ub(x.get_bound().get_upper());

	atom<T> a_lb (x,lb) , a_ub(x,ub);

	clause<T> c_lb;
	clause<T> c_ub;

	c_lb.push_back(literal<T>(a_lb,true));
	c_ub.push_back(literal<T>(a_ub));
	
	clauses.push_back(c_lb);
	clauses.push_back(c_ub);
	
	for(const T & i : x.get_bound().as_vector())
	{
	  clause<T> c_order;
		
	  atom<T> a_inf (x,i-1), a_sup(x,i);
	  c_order.push_back(literal<T>(a_inf,true));
	  c_order.push_back(literal<T>(a_sup));

	  clauses.push_back(c_order);
	}
      }

      // Converting comparisons into primitive ones
      node<T> * solving_root = new node <T> (0);
      node<T>::create_from(solving_root,nvars,sum_bi);
    
     
      //std::cout << *solving_root << std::endl; 
    
        
      std::vector <std::vector <T> > combi;
      node<T>::get_combinations(solving_root,combi,sum_bi,0);
      
      delete (solving_root);

      // Conflict regions
      for (const std::vector <T> & comb : combi)
      {

	  size_t m = comb.size();
	/*  if (m != n)
	    break;
	*/
	  clause <T> C1;
            
	  for (size_t i = 0; i < m; ++i)
	  {
	      size_t k = (n-i)-1;
 
	      T a = m_ineq.at(vars.at(k));
                
	      T b = comb.at(i);
	      T div = b/a;
            
	      if (a > 0)
	      {
		  T lb (vars.at(k).get_bound().get_lower());
		  
		  atom <T> a1 (vars.at(k),std::floor(div));
		  atoms.insert(a1);
		  
		   
		  if (std::floor(div) < lb)
		    C1.push_back(literal<T>(a1,true));
		  else
		    C1.push_back(literal<T>(a1));
	      }
	      else
	      {
		  atom <T> a2 (vars.at(k),std::ceil(div)-1); 
		  atoms.insert(a2);
    
		  
		  
		  C1.push_back(literal<T>(a2,true));	      	      
		  
	      }
	  }

	 clauses.push_back(C1);
      }

    } // end order encoding
        

    std::map <atom<T>,size_t> map_atoms;
    size_t num = 1;
    for (auto atm : atoms)
    {
        map_atoms.emplace(atm,num);
	std::cout << num << " <=> " << atm << std::endl;
	++num;
    }

    std::vector <std::vector <int>> clauses_nums;
    
    size_t s = 0;
    for (auto cl : clauses)
    {
        clauses_nums.push_back(std::vector<int>());
        for (auto lit : cl)
        {    
            if (lit.is_neg())
                clauses_nums[s].push_back(-1*map_atoms.at(lit.get_atom()));
            else
                clauses_nums[s].push_back(map_atoms.at(lit.get_atom())); 
	}
	
	
        ++s;
    }
    
    std::ofstream ofs (dimacs);
    if (ofs)
    {
      ofs << "p cnf " << map_atoms.size() << " " << clauses_nums.size() << std::endl;
      for (auto clnum : clauses_nums)
      {
	for (auto litnum : clnum)
	  ofs << litnum << " ";
	ofs << "0" << std::endl;
      }
      ofs.close();
    }
    return clauses; 
}

template std::vector <clause<int>> encoder<int>::encode(const char *, E_TYPE_ENCODING) const ;
