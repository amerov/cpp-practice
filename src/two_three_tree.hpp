//
//  two_three_tree.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-19.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_two_three_tree_hpp
#define cpp_practice_two_three_tree_hpp

#include "alg_share.h"

namespace dennycd{
    
    /**
      A balanced tree 
         - internal nodes has either 2 / 3 childs 
         - all leaf nodes at the same level
         - data are in sorted order  
     
     
     tree with K-level has at least 2^K - 1 nodes
     N-node tree height bounded by ceil(log(N+1))
     
     **/
    template<class D>
    class TwoThreeTree {
    public:
        
        typedef enum{
            TraverseOrderIn,
            TraverseOrderPre,
            TraverseOrderPost
        }TraverseOrder;
        
        typedef std::function<void(const D& data)> TraverseFunc;
        
        typedef enum{
            TNodeTypeTwo,
            TNodeTypeThree
        }TNodeType;
        
        struct TNode{
            D ldata;
            D rdata;
            TNode* lchild;
            TNode* mchild;
            TNode* rchild;
            
            TNode* parent;
            
            TNodeType type;
            
//            //undetermined
            TNode():lchild(NULL), mchild(NULL), rchild(NULL), parent(NULL){
            
            }

            
            TNode(D d, TNode*l = NULL, TNode* m = NULL){
                two(d,l,m);
                parent = NULL;
            }
            
            TNode(D ld, D rd, TNode*l = NULL, TNode*m = NULL, TNode* r = NULL){
                three(ld, rd, l, m, r);
                parent = NULL;
            }
        
            
            bool leaf() const{return (lchild==NULL && mchild==NULL && rchild==NULL);}
            
            
            void two(D d, TNode*l = NULL, TNode*r = NULL){
                type = TNodeTypeTwo;
                ldata = d;
                lchild = l;
                mchild = r;
                rchild = NULL;
                
                
                if(lchild) lchild->parent = this;
                if(mchild) mchild->parent = this;
            }
            
            void three(D d1,  D d2, TNode*l = NULL, TNode*m = NULL, TNode*r = NULL){
                type = TNodeTypeThree;
                ldata = d1;
                rdata = d2;
                
                lchild = l;
                mchild = m;
                rchild = r;
                
                if(lchild) lchild->parent = this;
                if(mchild) mchild->parent = this;
                if(rchild) rchild->parent = this;
            }
            
            bool two() const{ return type == TNodeTypeTwo; }
            bool three() const{ return type == TNodeTypeThree; }
       
            
            TNode* left_sibling(TNode* cur){
                if(two()){
                    return (cur==mchild) ? lchild : NULL;
                }
                else{
                    if(cur == lchild) return NULL;
                    else if(cur == mchild) return lchild;
                    else if(cur == rchild) return mchild;
                    else return NULL;
                }
            }
            
            TNode* right_sibling(TNode* cur){
                if(two()){
                    return (cur==lchild) ? mchild : NULL;
                }
                else{
                    if(cur==lchild) return mchild;
                    if(cur==mchild) return rchild;
                    return NULL;
                }
            }
            
            
            //access the mid data item in betweem the two kid
            D* mid_data(TNode* left, TNode* right){
                if(two()){
                    assert(left == lchild && right == mchild);
                    return &ldata;
                }
                else{
                    if(left == lchild && right == mchild)
                        return &ldata;
                    else if(left == mchild && right == rchild)
                        return &rdata;
                    else assert(NULL);
                }
            }
            
            
            //replace the child and return the old child
            void replace_child(TNode* oldchild, TNode* newchild){
                if(two()){
                    if(lchild == oldchild)
                        lchild = newchild;
                    else if(mchild == oldchild)
                        mchild = newchild;
                    else
                        assert(NULL);
                }
                else{
                    if(lchild == oldchild)
                        lchild = newchild;
                    else if(mchild == oldchild)
                        mchild = newchild;
                    else if(rchild == oldchild)
                        rchild = newchild;
                    else
                        assert(NULL);
                }
            }
            
        };
        
        TwoThreeTree() : m_root(NULL){
        }
        
        ~TwoThreeTree(){
            _recursive_cleanup(m_root);
        }
        
    public:
        
        //REFERENCE DAPSC - Chap. 12 the deletion algorithm
        template<class KEY>
        bool remove(KEY key){
            
            //find the target node
            TNode* target = NULL;
            D data;
            if(!_recursive_search(m_root, key, data, target))
                return false;
            assert(target!=NULL);
            std::cout << "deleting " << data << std::endl;
            
            //if not a leaf, swap its value with leaf
            if(!target->leaf()){
                
                //find inorder successor
                TNode* successor = inorder_successor(target, data);
                assert(successor && successor->leaf());
                
                //swap with left most value in the succesor
                swap_with_inorder_successor(target, data, successor);
            
                target = successor;
            }
            
            //being deletion at leaf node
            return _recursive_remove(target, data);

                
            
        }
        
        
        bool insert(const D& data){
            
            //first locate the leaf node to
            TNode* leaf = NULL;
            D tmpData; 
            _recursive_search(m_root, data, tmpData, leaf);
            

            //initial root node
            if(leaf==NULL){
                m_root = new TNode(data);
                return true;
            }


            TNode* present = leaf; //current target node to put data in
            TNode* intermediate = new TNode(data); //the newly formed dangling node to be inserted (as result of a previous split)
            
            while(present && intermediate){
                intermediate = insert_and_split(present, intermediate);
                if(intermediate)
                    present = intermediate->parent;
            }
            
            //reaching root, upgrad the root
            if(intermediate)
                m_root = intermediate;
            
            return true;
        }
        
        
        
        // Log(N) runtime 
        //search for data with the specified key
        template<typename KEY>
        bool search(KEY key, D& data){
            TNode* placeholder;
            return _recursive_search(m_root, key, data, placeholder);
        }
        
        
        //O(N)
        void traverse_inorder(TraverseFunc func) const{
            _recursive_traversal(m_root, func, TraverseOrderIn);
        }
        
        void clear(){
            _recursive_cleanup(m_root);
        }
        
        bool empty() const{
            return m_root == NULL;
        }
        
        template<class DD>
        friend std::ostream& operator << (std::ostream& oss, const TwoThreeTree<DD>& tree);
        
        
    protected:

        
        
        
        void _recursive_cleanup(TNode* present){
            if(!present) return;
            
            if(present->two()){
                _recursive_cleanup(present->lchild);
                _recursive_cleanup(present->mchild);
            }
            else if(present->three()){
                _recursive_cleanup(present->lchild);
                _recursive_cleanup(present->mchild);
                _recursive_cleanup(present->rchild);
            }
            else assert(0);
            
            delete present;
            present = NULL;
        }
        
        
        /**
         remove data on target node. trickle up the tree if deletion results in
         empty target node
         **/
        bool _recursive_remove(TNode* target, const D& data){
            assert(target);
            
            //simply shrink to two node by removing the target data, and we are done
            if(target->three()){
                if(target->ldata == data){
                    assert(target->lchild == NULL); //must have been marked as empty
                    target->two(target->rdata, target->mchild, target->rchild); //essentiall discarding lchild
                }
                else if(target->rdata == data){
                    assert(target->rchild == NULL);
                    target->two(target->ldata, target->lchild, target->mchild); //essentiall discarding rchild
                }
                return true;
            }
            //a two node means triggering a recursive removal starting
            //at  this leaf
            else{
                //if the target node has no parent, meaning we reached the root
                //simply update root
                if(target->parent==NULL){
                    assert(m_root == target);

                    //the deletion might come from any of the child node!!
                    if(m_root->lchild){
                        m_root = m_root->lchild;
                        m_root->parent = NULL;
                    }
                    else if(m_root->mchild){
                        m_root = m_root->mchild;
                        m_root->parent = NULL;
                    }
                    else //case where this is the last node to delet e
                    {
                        m_root = NULL; 
                    }
                    
                    //get rid of the root node 
                    delete target;
                    return true;
                }
                
                TNode* leftSibling = target->parent->left_sibling(target);
                TNode* rightSibling = target->parent->right_sibling(target);
                
                //REDISTRIBUTION
                //case where a sibling has extra item to redistribute
                if(leftSibling && leftSibling->three()){
                    
                    //move a parent item down to target,  //move rchild of left sibling to lchild of target
                    //TODO - how about mchild of target ? any changes ??
                    target->two(*(target->parent->mid_data(leftSibling, target)),
                                leftSibling->rchild,
                                target->mchild);
                    
                    //copy the right most data item from sibling to parent
                    *(target->parent->mid_data(leftSibling, target)) = leftSibling->rdata; 
                    
                    //now shrink left sibling to be a two-node
                    leftSibling->two(leftSibling->ldata, leftSibling->lchild, leftSibling->mchild);
                    
                
                    //all done, no further operation
                    return true;
                }
                else if(rightSibling && rightSibling->three()){
                 
                    //copy parent data item down
                    target->two(*(target->parent->mid_data(target, rightSibling)),
                                target->lchild,
                                rightSibling->lchild);
                    
                    //move left most item of right sibling up to parent
                    *(target->parent->mid_data(target, rightSibling)) = rightSibling->ldata;
                    
                    //shrink sibling to be a two-node
                    rightSibling->two(rightSibling->rdata, rightSibling->mchild, rightSibling->rchild);
                    
                    return true;
                }
                
             
                //MERGE
                //if no sibling available for redistribution, attempt to merge
                if(leftSibling && leftSibling->two()){
                    
                    D removedData = *(target->parent->mid_data(leftSibling,target)); //the datea item to remove on parent
                    
                    //upgrade left sibling to be a three-node using parent 's mid
                    //move target's lchild to rchild of left sib
                    leftSibling->three(leftSibling->ldata, *(target->parent->mid_data(leftSibling,target)),
                                       leftSibling->lchild,
                                       leftSibling->mchild,
                                       /*target->lchild*/ target->mchild );
                    
                    //mark the deleted target link to be empty
                    target->parent->replace_child(target, NULL);
                    
                    //now safe to delete target
                    delete target;
                    
                    //trickle up by removing the data item on parent 
                    return _recursive_remove(leftSibling->parent, removedData);
                    
                }
                else if(rightSibling && rightSibling->two()){
                    
                    //the mid item to be removed from parent
                    D removeData = *(target->parent->mid_data(target,rightSibling));
                    
                    //upgrad right sibling to ba three node by moving parent's item down
                    //also make right sibling's left most child to point to target's lchild
                    rightSibling->three(removeData, rightSibling->ldata,
                                        /*target->mchild*/ target->lchild,
                                        rightSibling->lchild,
                                        rightSibling->mchild);
                    
                    //mark parent's link to be empty 
                    target->parent->replace_child(target, NULL);

                    delete target;
                    
                    return _recursive_remove(rightSibling->parent, removeData);
                }
                
                
                //this shall not occur
                std::cout << "cannot merge or redistribute!" << std::endl;
                assert(0);
                
                
            }
        }
        
        
        //swap the od on origin with the left most value on target
        void swap_with_inorder_successor(TNode*origin, const D& od, TNode* target){
            assert(origin && target);
            assert(target->leaf() && !origin->leaf());
            
            if(origin->two()){
                swap(origin->ldata, target->ldata);
            }
            else if(origin->three()){
                if(origin->ldata == od)
                    swap(origin->ldata, target->ldata)
                else if(origin->rdata == od)
                    swap(origin->rdata, target->ldata)
                else assert(NULL);
            }
            else assert(NULL);
        }
        
        //find data's inorder successor in the tree
        TNode* inorder_successor(TNode* parent, const D& data){
            assert(parent!=NULL && !parent->leaf());
            
            //find left most leaf of its right child
            if(parent->two()){
                assert(parent->mchild != NULL);
                TNode* present = parent->mchild;
                while(present->lchild)
                    present = present->lchild;
                return present;
            }
            else if(parent->three()){
                if(data == parent->ldata){
                    TNode* present = parent->mchild;
                    assert(present);
                    while(present->lchild)
                        present = present->lchild;
                    return present;
                }
                else if(data == parent->rdata){
                    TNode* present = parent->rchild;
                    assert(present);
                    while(present->lchild)
                        present = present->lchild;
                    return present;
                }
                else assert(NULL);
            }
            
            assert(NULL);
        }


        //attemp to insert a two-node into present
        //if insertion result in a split, return the newly created parent node
        TNode* insert_and_split(TNode*& present, TNode* node){
            assert(present && node);
            
            //without split -> convert into a three-node
            if(present->two()){
                if(node->ldata < present->ldata){  //insert at left

                    //note present's lchild originally points to a destroyed child that has been splitted 
                    present->three(node->ldata, present->ldata, node->lchild, node->mchild, present->mchild);
                    
                }
                else{ //insert at right

                    //present's old rchild points to an already destroued child that has been splitted
                    present->three(present->ldata, node->ldata, present->lchild, node->lchild, node->mchild);
                }
                
                //on done, get rid of intermediate node
                delete node;
                return NULL;
            }
            //split a three-node into a parent and two node
            else if(present->three()){
                
                TNode* newnode = new TNode();
                newnode->parent = present->parent;
                
                //promote the mid point to a new node
                const D* midd = mid(present->ldata, present->rdata, node->ldata);
                
                //[newnode, ldata, rdata]
                if(midd == &(present->ldata)){

                    //newnode as parent 
                    newnode->two(present->ldata, node, present);

                    //present node becomes the right node with one data
                    present->two(present->rdata, present->mchild, present->rchild);
                    
                    
                }
                //[ldata, rdata, newnode]
                else if(midd == &(present->rdata)){

                    newnode->two(present->rdata, present, node);
                    
                    //present is resued as the left child node -> shrink to one-node 
                    present->two(present->ldata, present->lchild, present->mchild);
                    
                    
                }
                //[ldata, newnode, rdata]
                else{
                    
                    //new node link
                    newnode->two(node->ldata, present, node);

                    TNode* old = node->lchild;
                    
                    //node goes to right child
                    node->two(present->rdata, node->mchild, present->rchild);
                    
                    //present becomes left child
                    present->two(present->ldata, present->lchild, old);
                    

                }
                
                return newnode;
            }
            else assert(NULL);
            
        }

        
        //return the node containing the key data, null if not found
        /**
          parent - current searched node
          key - search key
          data - copy data
          leaf - if failed to find, the leaft node where the search stopped
                 if found, the target node containing the key
         **/
       template<typename KEY>
        bool _recursive_search(TNode* parent, const KEY& key, D& data, TNode*& target){
            if(!parent){
                target = NULL;
                return false;
            }
            
            //leaf node
            if(parent->leaf()){

                if(key==parent->ldata){  //hit
                    target = parent;
                    data = parent->ldata;
                    return true;
                }
                else
                if(parent->three() && key==parent->rdata){
                    target = parent;
                    data = parent->rdata;
                    return true;
                }
                else{
                    target = parent;
                    return false;
                }
            }
            //two node
            else if(parent->two()){
                if(key < parent->ldata)
                    return _recursive_search(parent->lchild, key, data, target);
                else if(key == parent->ldata){   //hit
                    target = parent;
                    data = parent->ldata;
                    return true;
                }
                else
                    return _recursive_search(parent->mchild, key, data, target);
                
            }
            //three node
            else if(parent->three()){

                if(key < parent->ldata)
                    return _recursive_search(parent->lchild, key, data, target);
                else if(key == parent->ldata){   //hit on left data
                    target = parent;
                    data = parent->ldata;
                    return parent;
                }
                if(key < parent->rdata)
                    return _recursive_search(parent->mchild, key, data, target);
                else if(key == parent->rdata){   //hit on right data
                    target = parent;
                    data = parent->rdata;
                    return parent;
                }
                else
                    return _recursive_search(parent->rchild, key, data, target);
                
                
            }
            else assert(NULL);
        }


        void _recursive_traversal(TNode* parent, TraverseFunc& func, TraverseOrder order) const{
            if(!parent) return;
            
            switch(order){
                case TraverseOrderIn:{
                    _recursive_traversal(parent->lchild, func, order);
                    func(parent->ldata);
                    _recursive_traversal(parent->mchild, func, order);
                    
                    if(parent->three()){
                        func(parent->rdata);
                        _recursive_traversal(parent->rchild, func, order);
                    }
                }break;
            
            
                case TraverseOrderPre:{
                    func(parent->ldata);
                    if(parent->three())
                        func(parent->rdata);
                    
                    _recursive_traversal(parent->lchild, func, order);
                    _recursive_traversal(parent->mchild, func, order);
                    
                    if(parent->three())
                        _recursive_traversal(parent->rchild, func, order);
                }break;
                    
                case TraverseOrderPost:{
                    _recursive_traversal(parent->lchild, func, order);
                    _recursive_traversal(parent->mchild, func, order);
                    if(parent->three()) _recursive_traversal(parent->rchild, func, order);

                    func(parent->ldata);
                    if(parent->three()) func(parent->rdata);
                }break;
            }
            
            
        }

        
    protected:
        TNode* m_root;
    };


    
    template<class DD>
    std::ostream& operator<< (std::ostream& oss, const TwoThreeTree<DD>& tree){
        oss << "{";
        tree.traverse_inorder([&](const DD& data){
            oss << data << ",";
        });
        oss << "}";
        return oss;
    }
    
}








#endif
