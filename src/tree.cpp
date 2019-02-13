#include "tree.h"
#include <queue>

template <class T>
std::ostream & operator << (std::ostream & os, const node <T> & n)
{
    node<T>::print(os,n,0);
    return os;
}

template <class T>
void node<T>::create_from(node <T> * root, std::vector < variable <T> > & vars, const T & sum_bi)
{
    
    if (false == vars.empty())
    {    
        variable <T> var (*vars.begin());
		
        for (const T & value : var.get_bound().as_vector())
        {
            if (sum_bi - value >= 0 )
                root->push_back(new node<T> (value,root));
        }
       
        for (size_t i = 0; i < root->size(); ++i)
        {
            std::vector <variable<T>> vnext (vars);
            vnext.erase(vnext.begin());
            
	     
            node<T>::create_from((*root)[i],vnext,sum_bi-root->at(i)->get_value());
        } 
        
    }
    else
        return; 
}

template <class T>
void node<T>::full_tree(node <T> * root, std::vector < variable <T> > & vars)
{
    
    if (false == vars.empty())
    {    
        variable <T> var (*vars.begin());
		
        for (const T & value : var.get_bound().as_vector())
        {
	    root->push_back(new node<T> (value,root));
        }
       
        for (size_t i = 0; i < root->size(); ++i)
        {
            std::vector <variable<T>> vnext (vars);
            vnext.erase(vnext.begin());
            
	    node<T>::full_tree((*root)[i],vnext);
        } 
        
    }
    else
        return; 
}
template void node <int>::full_tree(node <int> *, std::vector <variable<int>> &);
template void node <int>::create_from (node <int> *, std::vector <variable<int>> &, const int & );
template std::ostream & operator << <int>(std::ostream &, const node <int> &);
