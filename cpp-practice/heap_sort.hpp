//
//  heap_sort.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-18.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_heap_sort_hpp
#define cpp_practice_heap_sort_hpp
#include "heap.hpp"

namespace dennycd {
    
    /**
       HeapSort 
     
     D - data array type
     E - element type
     
     
     
     Time Complexity O(N logN )
     Space Complexity O(1)
     
     **/
    template<typename D, typename E>
    void heapsort(D& data){
    
        int n = (int)data.size();
        
        //step one is to use the data to build a new heap
        //by taking every node and rebuild a semi heap on it
        // O(N logN)
        for(int i=n-1;i>=0;i--){
        
            //rebuild [i n) by trickle i down
            int present = i;
            while(present < n){
                int swap = -1;
                int lchild = present * 2 + 1;
                int rchild = present * 2 + 2;
                
                if(lchild < n && data[present] < data[lchild])
                    swap = lchild;
                if(rchild < n && data[present] < data[rchild]){
                    if(!(swap >= 0 && data[swap] > data[rchild]))
                        swap = rchild;
                }
                
                if(swap < 0) break;
                swap(data[swap], data[present]);
                present = swap;
                
            }
        }
        
        
        
        // note -  max heap ==>> sorted array in ascending order
        //Step Two - iteratively take top of the heap into a sorted region
        // unsorted -  [0 last]
        // sorted - [last+1, n)
        //  O(N log N)
        for(int last = n-1; last >= 1;last--){
            swap(data[0], data[last]);
            
            //rebuild the heap [0, last] by trickle [0] down
            int present = 0;
            while(present < last){
                int swap = -1;
                int lchild = present * 2 + 1;
                int rchild = present * 2 + 2;
                
                if(lchild < last && data[present] < data[lchild])
                    swap = lchild;
                if(rchild < last && data[present] < data[rchild]){
                    if(!(swap >= 0 && data[swap] > data[rchild]))
                        swap = rchild;
                }
                
                if(swap < 0) break;
                swap(data[swap], data[present]);
                present = swap;
                
            }
            
        }
        
        
    }
}


#endif
