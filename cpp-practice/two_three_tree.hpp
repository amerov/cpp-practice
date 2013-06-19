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
       
        };
        
        TwoThreeTree() : m_root(NULL){}
        ~TwoThreeTree(){}
        
    public:
        
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
        
        template<class DD>
        friend std::ostream& operator << (std::ostream& oss, const TwoThreeTree<DD>& tree);
        
        
    protected:


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
//                    present->parent = newnode;
//                    node->parent = newnode;
                    
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
         **/
       template<typename KEY>
        bool _recursive_search(TNode* parent, const KEY& key, D& data, TNode*& leaf){
            if(!parent){
                leaf = NULL;
                return false;
            }
            
            //leaf node
            if(parent->leaf()){
                
                if(key==parent->ldata){  //hit
                    data = parent->ldata;
                    return true;
                }
                else{
                    leaf = parent;
                    return false;
                }
            }
            //two node
            else if(parent->two()){
                if(key < parent->ldata)
                    return _recursive_search(parent->lchild, key, data, leaf);
                else if(key == parent->ldata){   //hit 
                    data = parent->ldata;
                    return parent;
                }
                else
                    return _recursive_search(parent->mchild, key, data, leaf);
                
            }
            //three node
            else if(parent->three()){

                if(key < parent->ldata)
                    return _recursive_search(parent->lchild, key, data, leaf);
                else if(key == parent->ldata){   //hit on left data
                    data = parent->ldata;
                    return parent;
                }
                if(key < parent->rdata)
                    return _recursive_search(parent->mchild, key, data, leaf);
                else if(key == parent->rdata){   //hit on right data
                    data = parent->rdata;
                    return parent;
                }
                else
                    return _recursive_search(parent->rchild, key, data, leaf);
                
                
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
