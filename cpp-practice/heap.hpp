//
//  heap.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-18.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_heap_hpp
#define cpp_practice_heap_hpp

#include "alg_share.h"

/**
  An array-based binary tree implementation of Heap - A Priority Queue
 
 
 A heap is not sorted, but ranked towards the root
  - a max heap has root node having higher priority than any child nodes
 
 delete always retrieve the the root value
 **/
namespace dennycd {
    
    const int MAX_ADT_HEAP_SIZE = 1024;
    
    /**
      T - data type 
      K - key type
     
     
       lchild of i : 2i+1
       rchild of i : 2i+2
       parent of i : floor((i-1)/2)
     
     
       heap is a complete tree is a balance tree 
        with minimum tree height  ceil( log(N+1)  )
     
     
     **/
    template<typename T, typename K>
    class Heap{
    public:
        Heap() : _count(0){}
        ~Heap(){}

        
        /**
           - add to tail 
           - trickle up until it hit a parent that's larger/equal than it
         
            O(logN) operation for tricker up
         
         **/
        void insert(const T& data){
            if(_count+1==MAX_ADT_HEAP_SIZE) throw std::exception();
            
            _base[_count++] = data;
            
            int present = _count-1;
            int parent = floor((present-1)/2);
            
            while(parent>=0){
                if(_base[present] > _base[parent]){
                    swap(_base[present], _base[parent]);
                    present = parent;
                    parent = floor((present-1)/2);
                }
                else break;
            }
        }
        
        
        /**
          delete top item
         
          - swap in tail 
          - trickle root down until it finds all its children equal/smaller than itself
         
         
            O(log N) operation for trickle down
         
         **/
        T remove(){
            if(_count-1 < 0) throw std::exception();
            
            T data = _base[0];
            _base[0] = _base[--_count];
            
            
            //trick down
            int present = 0;
            while(present < _count){
                
                int swap = -1;
                int lchild = present * 2 + 1;
                int rchild = present * 2 + 2;
                
                if(lchild < _count && _base[present] < _base[lchild])
                    swap = lchild;
                if(rchild < _count && _base[present] < _base[rchild]){
                    if(!(swap >= 0 && _base[swap] > _base[rchild]))
                        swap = rchild;
                }
                
                if(swap < 0) break;
                
                swap(_base[swap], _base[present]);
                present = swap;
            }
            
            return data;
        }
        
        
        
        
    private:
        T _base[MAX_ADT_HEAP_SIZE];
        int _count;
    };
}

#endif
