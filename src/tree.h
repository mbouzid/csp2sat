#ifndef tree_h
#define tree_h

#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <set>
#include <algorithm>
#include "variable.h"

template <class T>
class node : private std::vector < node <T> * > 
{
    private:
         
        T m_value;
        node <T> * m_previous;

        const T & get_value () const
        {
            return m_value;
        }
        

    public:
        
        node (const T & value, node <T> * previous = nullptr):
            std::vector < node<T> * > (),
            m_value (value),
            m_previous (previous)
        {}


        static void print (std::ostream & os, const node & n, size_t depth)
        {
            for (size_t i = 0; i < depth; ++i)
                os << '\t';
            os << n.m_value << std::endl;
            for (size_t i = 0; i < n.size(); ++i)
                print (os, *(n.at(i)), depth+1);
            
        }
        


        static void create_from (node * root, std::vector < variable <T> > & v, const T & sum_bi);
	static void full_tree(node * root, std::vector < variable <T> > & vars);

        ~node()
        {
            size_t nchild = this->size();
            for (size_t i = 0; i < nchild; ++i)
                delete ((*this)[i]);
        }

        static void get_leaves (node <T> * root, std::vector <node <T> *> & leaves)
        {
            if (root->empty())
                leaves.push_back(root);
            else
            {
                size_t n = root->size();
                for (size_t i = 0; i < n; ++i)
                    get_leaves (root->at(i),leaves);
            }
        }

        static void get_combinations (node <T> * root, std::vector < std::vector <T> > & combinations, const T & sum_bi, const T & neutral)
        {
            std::vector <node<T> *> leaves;
            get_leaves(root,leaves);
             
            for (node <T> * l : leaves)
            {
                std::vector <T> combination;
                node <T> * p = l;
                while ( nullptr != p->m_previous)
                {
                    combination.push_back (p->m_value);
                    p = p->m_previous;
                }
                T sum = std::accumulate (combination.begin(), combination.end(), neutral);
                if (sum == sum_bi)
                    combinations.push_back(combination);
            }
        } 


        static void get_conflicts (node <T> * root, std::vector < std::vector <T> > & combinations, const T & sum_bi, const T & neutral)
        {
            std::vector <node<T> *> leaves;
            get_leaves(root,leaves);
             
            for (node <T> * l : leaves)
            {
                std::vector <T> combination;
                node <T> * p = l;
                while ( nullptr != p->m_previous)
                {
                    combination.push_back (p->m_value);
                    p = p->m_previous;
                }
                T sum = std::accumulate (combination.begin(), combination.end(), neutral);
                if (sum > sum_bi)
                    combinations.push_back(combination);
            }
        } 
};


template <class T>
std::ostream & operator << (std::ostream &, const node <T> & );


#endif
