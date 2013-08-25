//
//  BinaryTreeA.h
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-24.
//  -
//
#ifndef ASTEMSOFT_ADT_BINARY_TREE_ARRAY_HPP
#define ASTEMSOFT_ADT_BINARY_TREE_ARRAY_HPP

#include "Set.hpp"
#include <iostream>

namespace astemsoft
{
    namespace adt
    {
        
        
        /**
         Array-based Implementation of Binary Search Tree
         
         the tree conforms to Binary Search Tree with sorted order 
         
         A free list is used to keep track of empty array entries
         See DAPS Chapter 10.1, Page 500 for discussion
         
         In Free List, we use rchild as the next pointer 
         
         For retrieval, insertion and deletion, time complexity is 
         Worst Case O(n)  -  Average Case O(logN) 
         
         For traversal, it is fixed at O(n)
         **/
        template<typename T>
        class BinaryTreeA : public Set<T>
        {
        public:
            enum TraversalType{
                PREORDER = 0,
                INORDER,
                POSTORDER
            };
            
            static const int DEFAULT_MAX_NODES = 2;//default tree capacity
        private:
            //tree node
            struct TNode{
            public:
                TNode(){lchild = rchild = -1;}
                T item;
                int lchild;
                int rchild;
            };
            
        public:
            BinaryTreeA() throw(SetException);
            BinaryTreeA(const BinaryTreeA& tree) throw(SetException);
            BinaryTreeA& operator =(const BinaryTreeA& tree) throw(SetException);
            virtual ~BinaryTreeA();
            
            void clear();
            bool empty() const{return count==0;}
            int size() const{return count;}
            int height() const{return recursive_height(root);}
            
            template<typename K> void insert(const T& item) throw(SetException);
            template<typename K> void remove(const K& key) throw(SetException);
            template<typename K> void retrieve(const K& key, T& item) const throw(SetException);
            
            template<typename F> void traverse(F& func) throw(SetException){ traverse(INORDER, func);}
            template<typename F> void traverse(F& func) const throw(SetException){ traverse(INORDER, func);}
            template<typename F> void traverse(TraversalType type, F& func) throw(SetException);
            template<typename F> void traverse(TraversalType type, F& func) const throw(SetException);
            void print() const;
            
            template<typename FUNC, typename KEY>
            void update( FUNC& func, const KEY& key) throw(SetException);
                    
        private:
            template<typename F> void recursive_traverse(TraversalType tt, int ptr,F& func) const;
            template<typename K> int* recursive_search(int* ptr, const K& key) const;
            void recursive_remove(int & ptr);
            int recursive_height(int ptr) const;
            
            void expand() throw(SetException);
            void initialize(); //initialize base content, reset to default storage
            TNode* base; 
            int capacity;
            int root; //indext to root 
            int free; //index to head of free list
            int count; //track total number of content nodes
        };
        
        template<typename ITEM>
        template<typename FUNC, typename KEY>
        void BinaryTreeA<ITEM>::update( FUNC& func, const KEY& key) throw(SetException)
        {
            int ptr = root;
            int *pp = recursive_search(&ptr, key);
            if( *pp == -1)
                throw SetException("no matching key found");
            
            func(base[*pp].item);
        }
        
        template<typename T>
        template<typename F>
        void BinaryTreeA<T>::traverse(TraversalType type, F& func) throw(SetException)
        {
            recursive_traverse(type,root,func);
        }
        
        template<typename T>
        template<typename F>
        void BinaryTreeA<T>::traverse(TraversalType type, F& func) const throw(SetException)
        {
            recursive_traverse(type,root,func);
        }

        template<typename T>
        int BinaryTreeA<T>::recursive_height(int ptr) const
        {
            if(ptr != -1)
            {
                int lheight = recursive_height( base[ptr].lchild);
                int rheight = recursive_height( base[ptr].rchild);
                return (1 + ( lheight > rheight ? lheight : rheight));
            }
            else 
                return 0;
        }
        
        template<typename T>
        template<typename K>
        void BinaryTreeA<T>::remove(const K& key) throw(SetException)
        {
            int *pp = recursive_search(&root, key);
            if( *pp == -1 )
                throw SetException("deletion error: no matching key found");
        
            recursive_remove(*pp);
            count--;
        }
        
        
        template<typename T>
        void BinaryTreeA<T>::recursive_remove(int & ptr)
        {
            if( ptr == -1)
                return;
            
            //leaf node
            if( base[ptr].lchild == -1 && base[ptr].rchild == -1 )
            {
                base[ptr].rchild = free;
                free = ptr;
                ptr = -1;
            }
            //left child not nill 
            else
            if( base[ptr].lchild != -1 && base[ptr].rchild == -1 ) 
            {
                base[ptr].rchild = free;  //detach ptr to free list
                free = ptr;
                ptr = base[ptr].lchild;
                base[ptr].lchild = -1;
            }
            else
            if( base[ptr].lchild == -1 && base[ptr].rchild != -1 )
            {
                int next = base[ptr].rchild;
                base[ptr].rchild = free;
                free = ptr;
                ptr = next;
            }
            //both child exist
            else
            {
                int *cur = &(base[ptr].rchild);
             
                //reach node having no left child (in-order successor)
                while( base[*cur].lchild != -1)
                    cur = &( base[*cur].lchild );
                
                //swap cur and ptr
                T tmp = base[*cur].item;
                base[*cur].item = base[ptr].item;
                base[ptr].item = tmp;
                
                //remove cur node (from whereeve it is pointed)
                recursive_remove(*cur);
            }
        }
        
        /**
         the content list kept untouched
         free list is expaned into the extra segment
         double the original capacity
         **/
        template<typename T>
        void BinaryTreeA<T>::expand() throw(SetException)
        {
            if(!base)
                return;
            
            TNode* newbase = new TNode[2*capacity];
            if(!newbase)
                throw SetException("heap memory alloc failed");
            
            //copy existing content to lower segment 
            for(int i=0;i<capacity;i++)
                newbase[i] = base[i];
            
            //expand free list through high segment 
            for(int i=capacity;i < 2*capacity; i++){
                newbase[i].lchild = -1;
                newbase[i].rchild = ( i < (2*capacity-1) ) ? (i+1) : free;
            }

            free = capacity;
            delete[] base;
            base = newbase;
            capacity = 2 * capacity;
            
            //root, count remains unchanged
            //std::cout << "expanding to " << capacity << " at count " << count << std::endl;
        }
        
        
        template<typename T>
        template<typename K>
        void BinaryTreeA<T>::insert(const T& item) throw(SetException)
        {
            if(free==-1)
                expand();
            
            int * pp = recursive_search(&root, (K)item); //auto conversion from item type to key type
         
            if( *pp != -1 )
                throw SetException("insertion failed: existing key found");
            
            //take a free node from free list
            int idx = free;
            free = base[free].rchild; //move free pointer down
            
            //insert a new node 
            base[idx].item = item;
            base[idx].lchild = base[idx].rchild = -1;
            
            //and let *pp points to it 
            *pp = idx;
            
            count++;
        }

        
        template<typename T>
        template<typename K>
        void BinaryTreeA<T>::retrieve(const K& key, T& item) const throw(SetException)
        {
            int ptr = root;
            int *pp = recursive_search(&ptr, key);
            if( *pp == -1)
                throw SetException("retrieval failed: no matching key found");
            item = base[*pp].item;
        }
        
        
        template<typename T>
        template<typename F> 
        void BinaryTreeA<T>::recursive_traverse(TraversalType tt, int ptr,F& func) const
        {
            if( ptr != -1)
            {
                switch(tt)
                {
                    case PREORDER:
                        func(base[ptr].item);
                        recursive_traverse(tt, base[ptr].lchild,func);
                        recursive_traverse(tt, base[ptr].rchild,func);
                        break;
                    case INORDER:
                        recursive_traverse(tt, base[ptr].lchild,func);
                        func(base[ptr].item);
                        recursive_traverse(tt, base[ptr].rchild,func);
                        break;
                    case POSTORDER:
                        recursive_traverse(tt, base[ptr].lchild,func);
                        recursive_traverse(tt, base[ptr].rchild,func);
                        func(base[ptr].item);
                        break;
                }
            }
        }
        
        
        //on matched, return address of the pointer pointing to target node
        //on unmatched, retrun address of the pointer where key-ed new node
        // shall be inserted. (must be a at leaf and *p == -1)
        //@ptr - current subtree to be searched for 
        //@key - the target key value
        template<typename T>
        template<typename K>
        int* BinaryTreeA<T>::recursive_search(int* ptr, const K& key) const
        {
            if( *ptr != -1)
            {
                if( base[*ptr].item > key )
                {
                    if( base[*ptr].lchild == -1  )
                        return &( base[*ptr].lchild );
                    else 
                        return recursive_search(&( base[*ptr].lchild), key);
                }
                else
                    if( base[*ptr].item < key )
                    {
                        if( base[*ptr].rchild == -1 )
                            return &( base[*ptr].rchild );
                        else 
                            return recursive_search( &(base[*ptr].rchild), key);
                    }
            }
            
            //either *ptr==-1 reached or found
            return ptr;
            
        }
        
        //printing function object
        template<typename T>
        struct BinaryTreeAPrint
        {
        public:
            void operator()(const T& item)
            {
                std::cout << item << "&";
            }
        };
        
        template<typename T>
        void BinaryTreeA<T>::print() const
        {
            std::cout << "total nodes: " << count << std::endl;
            std::cout << "current capacity: " << capacity << std::endl;
            std::cout << "current tree height: " << height() << std::endl;
            
            BinaryTreeAPrint<T> btap;
            std::cout << "\nINORDER" << std::endl;
            recursive_traverse(INORDER, root, btap);
            std::cout << "\nPREORDER" << std::endl;
            recursive_traverse(PREORDER, root, btap);
            std::cout << "\nPOSTORDER" << std::endl;
            recursive_traverse(POSTORDER, root, btap);
        }
        
        
        template<typename T>
        BinaryTreeA<T>::~BinaryTreeA()
        {
            if(base){
                delete[] base;
                base = NULL;
            }
        }
        
        template<typename T>
        BinaryTreeA<T>::BinaryTreeA(const BinaryTreeA<T>& tree) throw(SetException)
        {
            base = NULL;
            *this = tree;
        }
        
        template<typename T>
        BinaryTreeA<T>& BinaryTreeA<T>::operator =(const BinaryTreeA<T>& tree) throw(SetException)
        {
            if(this!=&tree)
            {
                TNode* newbase = new TNode[capacity];
                if(!newbase)
                    throw SetException("heap memory alloc failed");
                
                if(base)
                {
                    delete[] base;
                    base = NULL;
                }
                
                base = newbase;
                capacity = tree.capacity;
                root = tree.root;
                free = tree.free;
                count = tree.count;
                
                for(int i=0;i<capacity;i++)
                    base[i] = tree.base[i];
            }
            return *this;
        }
        
        
        template<typename T>
        BinaryTreeA<T>::BinaryTreeA() throw(SetException)
        {
            base = NULL;
            initialize();
        }
        
        template<typename T>
        void BinaryTreeA<T>::clear()
        {
            initialize();
        }
        
        template<typename T>
        void BinaryTreeA<T>::initialize()
        {
            if(base){
                delete[] base;
                base = NULL;
            }

            capacity = DEFAULT_MAX_NODES;
            base = new TNode[capacity];
            if(!base)
                throw SetException("heap memory alloc failed");
            
            root = -1;
            
            //initialize free list
            //link all free nodes 
            free = 0;
            for(int i=0; i<capacity;i++)
            {
                base[i].lchild = -1;
                base[i].rchild =  (i < capacity-1) ? i+1 : -1;
            }
            
            count = 0;
        }
        
        
        
    }
}
#endif