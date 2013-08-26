//
//  Sorts.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-22.
//  -
//
#ifndef ASTEMSOFT_ALGS_SORTING
#define ASTEMSOFT_ALGS_SORTING
#include <iostream>

namespace astemsoft 
{
    namespace algs{
        
        //
        //sample "<" function object for comparison
        //see PPP Ch.21.4, Page 734 by B.S. 
        //
        //to use it, declare an object  less_than x,
        //then use x:   x(x,y); 
        template<class T>
        struct less_than
        {
            //return true if x < y, otherwise, false
            //overriding a call operator named operator()
            bool operator()(const T& x, const T& y) const
            {
                return (x < y);
            }
        };
        
        
        //TODO: Radix Sort that takes O(n) Worst Time Complexity
        //
        
        /**
         Generic Quick Sort Algorithm
         See DAPS Ch. 9.2, Page 460 for quick sort algorithm
         
         Average Time: O(nlogn) - when list in random order
         Worst Time: O(n^2)  - when list in order, either descend/ascend
         **/
        template<class Ran, class Cmp, class T>
        void quick_sort(Ran first, Ran last, Cmp cmp)
        {
            //base case
            if(first == last)
                return; 
            
            //divide step
            Ran pivot = first;
            Ran lastS1 = pivot;
            Ran firstUnknown = first + 1;
            
            do{
                //if <p, move into S1 by swapping with lastS1 + 1
                if(cmp(*firstUnknown, *pivot))
                {
                    T tmp = *(lastS1+1);
                    *(lastS1+1) = *firstUnknown;
                    *firstUnknown = tmp;
                    ++lastS1; //shift rightwards
                }
                //otherwise it goes into S2 automatically
                
                if(firstUnknown == last)
                    break;
                else 
                    ++firstUnknown;
            }while(true);
            
            //move pivot to inbetween S1 and S2
            //swap iterator target values
            T tmp = *lastS1;
            *lastS1 = *pivot;
            *pivot = tmp;
            //swap iterator itself
            Ran rtmp = lastS1;
            lastS1 = pivot;
            pivot = rtmp;
            
            //conquer 
            if(pivot!=first)
                quick_sort<Ran, Cmp, T>(first, pivot-1, cmp);
            if(pivot!=last)
                quick_sort<Ran, Cmp, T>(pivot+1, last, cmp);
        }
        
        template<class Ran, class T>
        void quick_sort(Ran first, Ran last)
        {
            quick_sort<Ran, less_than<T>, T>(first, last, less_than<T>());
        }
        
        /**
         Generic Merge Sort 
         Time O(nlogn)  Space O(n)
         
         divide and conquer recursion
         1) divide all items between [first ... last] into two parts
         2) sort each of the two part 
         3) merge two parts 
         **/
        template<class Ran, class Cmp, class T>
        void merge_sort(Ran first, Ran last, Cmp cmp)
        {
            if(first == last) //base case reached
                return;
            
            //divide 
            Ran pre = first + (last - first) / 2;
            Ran post = pre + 1;
            
            //conquer 
            merge_sort<Ran,Cmp,T>(first, pre, cmp);
            merge_sort<Ran,Cmp,T>(post,last,cmp);
            
            //merge [first...pre] and [post...last] into cache
            int n = last - first + 1;
            T* cache = new T[n];
            int pos = 0;
            Ran h1=first,h2=post;
            
            do{
                if( cmp( *h1, *h2)){
                    cache[pos++] = *h1;
                    if(h1==pre){
                        //copy remains of [h2...last]
                        Ran tmp = h2;
                        do{
                            cache[pos++] = *tmp;
                            if(tmp==last)
                                break;
                            else 
                                ++tmp;
                        }while(true);
                        
                        break; 
                    }
                    else 
                        ++h1;
                }
                else
                {
                    cache[pos++] = *h2;
                    if(h2==last)
                    {
                        //copy remains of [h1...pre]
                        Ran tmp = h1;
                        do{
                            cache[pos++] = *tmp;
                            if(tmp==pre)
                                break;
                            else 
                                ++tmp;
                        }while(true);
                        
                        break;
                    }    
                    else 
                        ++h2;
                }
                
            }while(true);
            
            //copy merged result back
            Ran cur = first;
            for(int i=0;i<n;i++,++cur)
                *cur = cache[i];
 
            //release cache
            delete cache; 
            cache = NULL;
        }
        
        template<class Ran, class T>
        void merge_sort(Ran first, Ran last)
        {
            merge_sort<Ran, less_than<T>, T>(first, last, less_than<T>());
        }
        
        /**
         Generic Insertion Sort
         
         left side sorted, right side unsorted
         iteratively take one item from unsorted and insert into sorted
         
         Time: O(n^2)  Space: O(n)
         **/
        template<class Ran, class Cmp, class T>
        void insertion_sort(Ran first, Ran last, Cmp cmp)
        {
            if(first == last)
                return;
            
            Ran unsorted = first + 1;
            do{
                //shift all > items rightwards
                T tmp = *unsorted; 
                Ran cur = unsorted;
                for(; cur!=first; --cur)
                {
                
                    //shift rightwards if  cur > tmp
                   if(cmp( tmp, *(cur-1) ))
                       *cur = *(cur-1); 
                    //on first cur <= tmp, stop and copy into it
                   else 
                       break;
                }
                *cur = tmp;
                
                
               if(unsorted == last) //done after last one
                   break;
                else 
                    ++unsorted; //otherwise continue
            }while(true);
        
        }
        
        template<class Ran, class T>
        void insertion_sort(Ran first, Ran last)
        {
            insertion_sort<Ran, less_than<T>, T>(first, last, less_than<T>());
        }
        
        
        /**
         Generic Bubble Sort 
         Time: O(n^2) Space: O(n)
         
         left side unsorted region, right side sorted
         iteratively swap two adjacent items, up to max unsorted
         **/
        template<class Ran, class Cmp, class T>
        void bubble_sort(Ran first, Ran last, Cmp cmp)
        {
            Ran unsorted = last;
            
            while(unsorted != first)
            {
                bool swapped = false;
                //iterate from [first ... unsorted]
                Ran cur = first;
                while(cur != unsorted)
                {
                    if(cmp( *(cur+1), *cur )) //if smaller, swap
                    {
                        T tmp = *(cur+1);
                        *(cur+1) = *cur;
                        *cur = tmp;
                        swapped = true;
                    }
                    
                    ++cur; //move next
                }
                
                //if no swap at all, sort done
                if(!swapped){
                    std::cout << "early mature in bubble sort" << std::endl;
                    break; 
                }
                --unsorted;
            }
            
        }
        
        template<class Ran, class T>
        void bubble_sort(Ran first, Ran last)
        {
            bubble_sort<Ran, less_than<T>, T>(first, last, less_than<T>());
        }
        
        //Generic Selection Sort Algorithm 
        //
        //left side unsorted, right side sorted
        //Selection Sort does not requries an already sorted array 
        // Time O(n^2), Space O(n)
        //Operates on Random Access Iterator Concept
        //Data is a ordered set that can be freely accessed and moved
        //
        //Ran - random access iterator type
        //Cmp - function object for comparison, default to be  < (less than)
        //T - value type for the item being sorted
        //
        //all items inbetween first and ran (includsively) sorted
        //RULE:  if   x [cmp] y  is true, x precedes y in the set
        //
        //@first,last points to the first and last element of set
        template<class Ran, class Cmp, class T>
        void selection_sort(Ran first, Ran last, Cmp cmp)
        {
            Ran unsorted = last;
            
            while(unsorted != first)
            {
                //find the largest item in [first ... unsorted]
                Ran max = first, i = first;
                do{
                    if(cmp(*max,*i))
                        max = i;
                    
                    if(i == unsorted) //quit once unsorted reached
                        break;
                    else 
                        ++i; //next item
                }while(true);
                
                
                //swap target value between unsorted with max
                if(unsorted!=max){
                    //std::cout << "swaping " << *max << " <=> " << *unsorted << std::endl;
                    T tmp = *unsorted;
                    *unsorted = *max;
                    *max = tmp;
                }
                
                --unsorted; //move backward 
            }
            
        }
        
        //default comparator
        template<class Ran, class T>
        void selection_sort(Ran first, Ran last)
        {
            selection_sort<Ran, less_than<T>, T>(first, last, less_than<T>());
        }
        
        
        
        
    }
}
#endif