//
//  p_binary_tree.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-17.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_p_binary_tree_hpp
#define cpp_practice_p_binary_tree_hpp

#include "alg_share.h"

/**
  Pointer-based Binary Search Tree Implementation
 **/
namespace dennycd {
  
    /**
      T - data item type
      K - data key item
     **/
    template<typename T>
    class BinaryTreeP{
    public:
        
        typedef enum {
            PREORDER,
            INORDER,
            POSTORDER
        }TraverseOrder;
        
        //user traversal function 
        typedef std::function<void(T& data)> Operator;
        
        //tree node type
        struct TNode{
            T data;
            TNode* lchild;
            TNode* rchild;
            TNode(const T&d, TNode*l, TNode*r) : data(d), lchild(l), rchild(r){}
            TNode(const T&d) : data(d), lchild(NULL), rchild(NULL){}
        };
        
        BinaryTreeP(){
            _root = NULL;
        }
        
        //init from a list using tree sort 
        BinaryTreeP(const std::initializer_list<T>& list){
            _root = NULL;
            for(auto elem = list.begin(); elem!=list.end();elem++)
                if(!_recursive_insert(*elem, _root)) throw std::exception();
        }
        
        virtual ~BinaryTreeP(){
            _recursive_clearup(_root);
        }
        
        bool empty() const{ return _root==NULL;}
        
        
        //insert a new item. return false if inerst failed
        bool insert(const T& data){
            return _recursive_insert(data, _root);
        }
        
        //check if itme with the given key exist in tree
        template<typename KEY>
        bool exists(KEY key){
            TNode* target = _recursive_search(key, _root);
            return (target!=NULL);
        }
        
        //O(logN)
        template<typename KEY>
        bool remove(KEY key){
            return _recursive_delete(key, _root);
        }
        
        //O(logN) operation
        template<typename KEY>
        T& retrieve(KEY key){
            TNode* target = _recursive_search(key, _root);
            if(!target) throw std::exception();
            return target->data;
        }
        
        
        void traversal_inorder(Operator opt){
            _recursive_traversal(_root, opt, INORDER);
        }
 
        void traversal_preorder(Operator opt){
            _recursive_traversal(_root, opt, PREORDER);
        }

        void traversal_postorder(Operator opt){
            _recursive_traversal(_root, opt, POSTORDER);
        }
        
        template<typename TT>
        friend std::ostream& operator << (std::ostream& oss, const BinaryTreeP<TT>& tree);
        
    protected:
        
        void _recursive_traversal(TNode* parent, Operator& opt, TraverseOrder order){
            if(!parent) return;
            
            switch (order) {
                case PREORDER:
                {
                    opt(parent->data);
                    _recursive_traversal(parent->lchild, opt, order);
                    _recursive_traversal(parent->rchild, opt, order);
                }break;
                    
                case INORDER:
                {
                    _recursive_traversal(parent->lchild, opt, order);
                    opt(parent->data);
                    _recursive_traversal(parent->rchild, opt, order);
                }break;
                    
                case POSTORDER:
                {
                    _recursive_traversal(parent->lchild, opt, order);
                    _recursive_traversal(parent->rchild, opt, order);
                    opt(parent->data);
                }break;
            }
        }
        
        
        
        //recursive deletion 
        // O(logN) for locating the delete point
        // O(logN) for finding left/right candidates to promote
        // O(1) to swap 
        template<typename KEY>
        bool _recursive_delete(KEY key, TNode*& parent){
            if(!parent) return false;
            
            //delete point
            if(parent->data == key){
                
                //find right most offspring of left child
                TNode*& lcandidate = parent->lchild;
                while(lcandidate && lcandidate->rchild)
                    lcandidate = lcandidate->rchild;
                
                //find left most offspring of right child
                TNode*& rcandidate = parent->rchild;
                while(rcandidate && rcandidate->lchild)
                    rcandidate = rcandidate->lchild;
                
                //pick a candiate and swap its content with parent 
                if(lcandidate){
                    swap(parent->data, lcandidate->data);
                    TNode* del = lcandidate;
                    lcandidate = lcandidate->lchild;
                    delete del;
                }
                else if(rcandidate){
                    swap(parent->data, rcandidate->data);
                    TNode* del = rcandidate;
                    rcandidate = rcandidate->rchild;
                    delete del;
                }
                //no candidate, simply delete the node as this would be a leaf
                else{
                    delete parent;
                    parent = NULL;
                }
                
                return true;
                
            }
            else if(parent->data > key)
                return _recursive_delete(key, parent->lchild);
            else
                return _recursive_delete(key, parent->rchild);
        }
        
        
        //recursive insertion
        //O(logN) time for finding insertion point - O(1) for insertion
        bool _recursive_insert(const T& data, TNode*& parent){
            
            if(parent==NULL){
                parent = new TNode(data); //insertion point !
                return true;
            }
            else if(data == parent->data)
                return false; //key duplication - insertion failed
            else if(data < parent->data)
                return _recursive_insert(data, parent->lchild);
            else
                return _recursive_insert(data, parent->rchild);
        }
        
        
        //binary search with the tree. return the hit node if found, NULL otherwise
        // O(logN) time
        template<typename KEY>
        TNode* _recursive_search(KEY key, TNode* parent){
            if(!parent) return NULL;
            if(parent->data == key) return parent;
            if(key < parent->data)
                return _recursive_search(key, parent->lchild);
            else
                return _recursive_search(key, parent->rchild);
        }
        
        //clean up all offspring of parent , free parent node and set it to NULL
        // O(N) operation - must hitting all nodes
        void _recursive_clearup(TNode*& parent){
            if(parent==NULL) return;
            _recursive_clearup(parent->lchild);
            _recursive_clearup(parent->rchild);
            delete parent;
            parent = NULL;
        }
        
        
    private:
        TNode* _root; //root node
    };
    
    template<typename TT>
    std::ostream& operator << (std::ostream& oss, BinaryTreeP<TT>& tree){
        oss << "{";
        tree.traversal_inorder([&oss](TT& item){
            oss << item << ",";
        });
        oss << "}";
        return oss;
    }
    
}


#endif
