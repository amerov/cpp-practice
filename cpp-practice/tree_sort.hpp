//
//  tree_sort.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-17.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_tree_sort_hpp
#define cpp_practice_tree_sort_hpp

#include "a_binary_tree.hpp"
#include "p_binary_tree.hpp"

namespace dennycd{
    
    /**
      tree sort using a binary search tree 
     
     Average :  O(N logN)
            - n insertion 
            - logN for each tree insertion
    
     Wost  O(N ^ 2)
            - n insertion
            - n for each tree insertion
     
     Space Complexity O(N)
     
        D - data list type
        E - data item type
     **/
    template<typename D, typename E, typename TREE = BinaryTreeA<E> >
    void tree_sort(D& data){
        int n = (int)data.size();
        
        TREE tree;
        for(int i=0;i<n;i++)
            tree.insert(data[i]);
                
        //in order traversal
        data.clear();
        tree.traversal_inorder([&](E& item){
            data.insert((int)data.size(), item);
        });
    }
}
#endif
