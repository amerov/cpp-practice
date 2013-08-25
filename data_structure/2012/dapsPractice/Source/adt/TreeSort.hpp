//
//  TreeSort.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-28.
//
#ifndef ASTEMSOFT_ALGS_TREE_SORT_HPP
#define ASTEMSOFT_ALGS_TREE_SORT_HPP

#include "BinaryTreeL.hpp"
#include "BinaryTreeA.hpp"
#include "List.hpp"

namespace astemsoft
{
    namespace algs
    {
        
        using namespace astemsoft;
        using namespace astemsoft::adt;
        
        //function object for handling coping
        template<class T>
        struct treesort_copy
        {
        public:
            treesort_copy(List<T>* pl) : plist(pl){}
            
            //add each item to end of the list
            void operator()(const T& item)
            {
                plist->insert(plist->size(),item);
            }
            
        private:
            List<T>* plist;
        };
        
        //using function handler version
        template<class T>
        void treesort_copy_func(const T& item)
        {
            std::cout << item << std::endl;
        }
        

        /**
         Generic Tree Sort Algorithm
         DAPS Chapter 10, Page 551 
         Using Binary Search Tree to Sort an unordered ADT list in order
         
         Worst cases:  O(n^2) 
         Average cases: O(n logn)
         **/
        template<typename T, typename TR >
        void treesort(List<T>* plist, TR& tree)
        {
            for(int i=0; i<plist->size();i++)
            {
                T item;
                plist->retrieve(i,item);
                tree.insert(item);
            }
            
            plist->clear();
           
           // tree.traverse(BinaryTreeL<T>::INORDER, treesort_copy_func<T>);
           
            treesort_copy<T> tc(plist);
            tree.traverse(TR::INORDER, tc);
        }

    }
}
#endif