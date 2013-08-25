//
//  HeapSort.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-10-01.
//  -
//
#ifndef ASTEMSOFT_ADT_HEAP_SORT_HPP
#define ASTEMSOFT_ADT_HEAP_SORT_HPP

#include "Heap.hpp"

namespace astemsoft
{
    namespace algs
    {

        using namespace astemsoft;
        using namespace astemsoft::adt;
        
        
        /**
         heapsorting an arbitrary ADT List
         Worst Case Time Complexity  N log N 
         See DAPS Chap. 11 Page 606 for the algorithm
         **/
        template<typename T>
        void heapsort(T* data, int size)
        {
            Heap<T> hp;
            hp.rebuild(data,size); // NlogN rebuilt
            
            T item;
            for(int i=0;i<size;i++)
            {
                hp.remove(item); //logN time removal
                data[i] = item;
            }
        }






























}
}
#endif