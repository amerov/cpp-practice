//
//  a_binary_tree.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-17.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_a_binary_tree_hpp
#define cpp_practice_a_binary_tree_hpp

/**
  Array Based Binary Tree Implementaiton
 **/
namespace dennycd {

    template<typename T>
    class BinaryTreeA{
      
    public:
        
        static const int MAX_TREE_CAPACITY = 1024;
        
        typedef enum {
            PREORDER,
            INORDER,
            POSTORDER
        }TraverseOrder;
        
        //user traversal function
        typedef std::function<void(T& data)> Operator;
        
        //tree node
        struct TNode{
            T data;
            int lchild;
            int rchild;
            TNode(){ lchild = -1; rchild = -1;}
            TNode(const T& d) : data(d), lchild(-1), rchild(-1){}
            TNode(const T&d, int l, int r) : data(d), lchild(l), rchild(r){}
        };
        
        BinaryTreeA(const std::initializer_list<T>& list){

            _root = -1;
            
            //initialize free list - right child used as pointer to next free slot
            _free = 0;
            
            _base[MAX_TREE_CAPACITY-1].rchild = -1; //make sure tail is marked as end
            for(int i= MAX_TREE_CAPACITY -1 ;i>0;i--)
                _base[i-1].rchild = i;
            
            for(auto elem = list.begin(); elem!=list.end();elem++)
                if(!_recursive_insert(*elem, _root)) throw std::exception();
        }
        
        BinaryTreeA(){
            _root = -1;
            
            //initialize free list - right child used as pointer to next free slot
            _free = 0;
            
            _base[MAX_TREE_CAPACITY-1].rchild = -1; //make sure tail is marked as end
            for(int i= MAX_TREE_CAPACITY -1 ;i>0;i--)
                _base[i-1].rchild = i;
        }
        
        virtual ~BinaryTreeA(){}
        
        
        bool empty() const{return _root == -1;}
        
        
        bool insert(const T& data){
            return _recursive_insert(data, _root);
        }
        
        template<typename KEY>
        bool exists(KEY key){
            return (_recursive_search(key, _root) != -1);
        }
        
        
        template<typename KEY>
        T& retrieve(KEY key){
            int idx = _recursive_search(key, _root);
            if(idx==-1) throw std::exception();
            return _base[idx].data;
        }
        
        template<typename KEY>
        bool remove(KEY key){
            return _recursive_delete(key, _root);
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
        friend std::ostream& operator << (std::ostream& oss, const BinaryTreeA<TT>& tree);
        
    protected:
        
        void _recursive_traversal(int parent, Operator& opt, TraverseOrder order){
            if(parent==-1) return;
            switch (order) {
                case PREORDER:
                {
                    opt(_base[parent].data);
                    _recursive_traversal(_base[parent].lchild, opt, order);
                    _recursive_traversal(_base[parent].rchild, opt, order);
                }break;
                    
                case INORDER:
                {
                    _recursive_traversal(_base[parent].lchild, opt, order);
                    opt(_base[parent].data);
                    _recursive_traversal(_base[parent].rchild, opt, order);
                }break;
                    
                case POSTORDER:
                {
                    _recursive_traversal(_base[parent].lchild, opt, order);
                    _recursive_traversal(_base[parent].rchild, opt, order);
                    opt(_base[parent].data);
                }break;
            }
            
        }
        
        
        template<typename KEY>
        bool _recursive_delete(KEY key, int& parent){
            if(parent==-1) return false;
            
            //delete point
            if(_base[parent].data == key){
                
                //find right most offstring of left child
                int& lcandidate = _base[parent].lchild;
                while(lcandidate!=-1 && _base[lcandidate].rchild!=-1)
                    lcandidate = _base[lcandidate].rchild;
                
                //find left most offstring of right child
                int& rcandidate = _base[parent].rchild;
                while(rcandidate!=-1 && _base[rcandidate].lchild!=-1)
                    rcandidate = _base[rcandidate].lchild;
                
                //pick a candiate and swap value with parent
                if(lcandidate!=-1){
                    swap(_base[parent].data, _base[lcandidate].data);
                    int del = lcandidate;
                    lcandidate = _base[lcandidate].lchild;
                    _return_empty_slot(del);
                }
                else if(rcandidate!=-1){
                    swap(_base[parent].data, _base[rcandidate].data);
                    int del = rcandidate;
                    rcandidate = _base[rcandidate].rchild;
                    _return_empty_slot(del);
                }
                //no canddiate found, parent is a leaf node, remove it
                else{
                    _return_empty_slot(parent);
                    parent = -1;
                }
                
                return true;
                
            }
            else if(key < _base[parent].data)
                return _recursive_delete(key, _base[parent].lchild);
            else
                return _recursive_delete(key, _base[parent].rchild);
        }
        
        template<typename KEY>
        int _recursive_search(KEY key, int parent){
            if(parent==-1) return -1;
            else if(_base[parent].data == key) return parent;
            else if(key < _base[parent].data)
                return _recursive_search(key, _base[parent].lchild);
            else
                return _recursive_search(key, _base[parent].rchild);
        }
        
        
        bool _recursive_insert(const T& data, int& parent){
            if(parent == -1){
                parent = _consume_empty_slot();
                _base[parent] = TNode(data, -1, -1);
                return true;
            }
            else if(_base[parent].data == data)
                return false; //key duplication
            else if(data < _base[parent].data)
                return _recursive_insert(data, _base[parent].lchild);
            else
                return _recursive_insert(data, _base[parent].rchild);
        }
        
        
        
        
        //
        bool _has_free_slot(){
            return (_free != -1);
        }
        
        //take a new empty slot off freelist
        //return -1 if list is full
        int _consume_empty_slot(){
            if(_free==-1) return -1;
            
            //take from head
            int slot = _free;
            _free = _base[_free].rchild; // gets -1 if last item gets returned
            return slot;
        }
        
        
        //return a slot to free list as empty
        void _return_empty_slot(int slot){
            //append at front
            _base[slot].lchild = -1;
            _base[slot].rchild = _free; //first empty slot will get rchild as -1 marked as end of free list
            _free = slot;
        }
        
        
        
    private:
        TNode _base[MAX_TREE_CAPACITY];
        int _root; //data point entry
        int _free; //free list entry
    };
    
    template<typename TT>
    std::ostream& operator << (std::ostream& oss, BinaryTreeA<TT>& tree){
        oss << "{";
        tree.traversal_inorder([&oss](TT& item){
            oss << item << ",";
        });
        oss << "}";
        return oss;
    }
    
    
}

#endif
