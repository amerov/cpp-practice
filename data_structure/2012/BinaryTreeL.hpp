//
//  BinaryTreeL.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-23.
//  -
//
#ifndef ASTEMSOFT_ADT_BINARY_TREE_HPP
#define ASTEMSOFT_ADT_BINARY_TREE_HPP

#include "Set.hpp"
#include <iostream>
#include <fstream>

namespace astemsoft
{
    namespace adt
    {
       
        
        /**
         A Pointer-Based Implementation of Binary Search Tree
         Left subtree has keys strictly smaller than current node
         Right subtree has keys strictly larger than current node
         Thereby items in the tree set are properly sorted
         
         T - item type
         K - item search key type, defaulted to be the same as item type
         F - the function object for external handling of tree item
         
         @assume T shall implement comparison operator for key:  T > < == K
         @assume T shall implement << ostream operator:   std::cout <<
         @assume T shall override type cast operator for key :   keytype ()
         
         For retrieval, insertion and deletion, time complexity is 
         Worst Case O(n)  -  Average Case O(logN) 
         
         The heigh of tree ranges from  ceil(log(n+1))) to n, depending on
         insertion ordering
         
         For traversal, it is fixed at O(n)
         
         See DAPS Chapter 10, Page 550 for discussion 
         **/
        template<typename T>
        class BinaryTreeL : public Set<T>
        {
        public:
            //typedef  void ItemHandler(const T& item);
            //typedef void (*ItemHandler)(const T& item); //for external item processing
            enum TraversalType{
                PREORDER = 0,
                INORDER,
                POSTORDER
            };
            
        private:
            //tree node 
            struct TNode{
                T item;
                TNode* lchild;
                TNode* rchild;
            };
       
        public:
            BinaryTreeL() : root(NULL),count(0){}
            BinaryTreeL(const BinaryTreeL& bt){ *this = bt; }
            virtual ~BinaryTreeL();
            BinaryTreeL& operator =(const BinaryTreeL& bt);
            
        public:
            void save(const std::string& filename) const throw(SetException);
            void restore(const std::string& filename) throw(SetException);
            void clear();
            bool empty() const{return (root == NULL);}
            int size() const{return count;}
            
            template<typename K>
            void insert(const T& item) throw(SetException);
            
            template<typename K> 
            void remove(const K& key) throw(SetException);
            
            template<typename K> 
            void retrieve(const K& key, T& item) const throw(SetException);

                        
            template<typename F> 
            void traverse(F& func) throw(SetException){ traverse(INORDER, func);}
            
            template<typename F> 
            void traverse(F& func) const throw(SetException){ traverse(INORDER, func);}
            
            template<typename F> 
            void traverse(TraversalType type, F& funcObj) throw(SetException);
            
            template<typename F> 
            void traverse(TraversalType type, F& funcObj) const throw(SetException);
            
            template<typename FUNC, typename KEY>
            void update( FUNC& func, const KEY& key) throw(SetException);
            
            void print() const;
            int height() const{ return recursive_height(root);}
            
        private:
            TNode* root; //root node
            int count;  //number of nodes
        private:
            //remove all nodes under the pointer(including itself)
            void recursive_clear(TNode*& ptr); 
            //copy and construct new subtree from source to target
            void recursive_create(TNode*& target, const TNode* source); 
            //recursively compute height of tree
            int recursive_height(const TNode* ptr) const; 
            //recursively traverse node and process each
            //void recursive_traverse(TraversalType tt, const TNode* ptr, ItemHandler func) const;
            //functional object verion of recursive traversal
            template<typename F> 
            void recursive_traverse(TraversalType tt, const TNode* ptr, F& funcObj) const;
            //re-construct a balanced tree from sorted input stream of items
            void recursive_read(TNode*& ptr, int n, std::ifstream& ifs);

            //non-recursive traversal using auxilary stack
            //void nonrecursive_traverse(const TNode* ptr, ItemHandler func) const;
            
            //auxiliary function to remove a node
            //@ptr - reference pointer towards the node to be removed
            void remove_node(TNode*& ptr);
            
            //return the address to a TNode pointer 
            //if pointer is not null, a key match is found
            //if pointer is null, no key match found, the pointer is 
            //the place where the expected key shall be inserted in
            //
            //@ptr - current substree to be searched 
            //@key - the target key 
            template<typename K>
            TNode** recursive_search(TNode** ptr, const K& key) const
            {
                if(*ptr)
                {
                    if((*ptr)->item > key){
                        
                        if((*ptr)->lchild==NULL)
                            return &((*ptr)->lchild);
                        else 
                            return recursive_search(&((*ptr)->lchild), key);
                    }
                    else 
                        if((*ptr)->item < key){
                            
                            if((*ptr)->rchild==NULL)
                                return &((*ptr)->rchild);
                            else 
                                return recursive_search(&((*ptr)->rchild), key);
                        }
                }
                
                //either NULL reached or found
                return ptr;
            }
        };

        template<typename ITEM>
        template<typename FUNC, typename KEY>
        void BinaryTreeL<ITEM>::update( FUNC& func, const KEY& key) throw(SetException)
        {
            TNode * ptr = root;
            TNode** pp = recursive_search( &ptr, key); //avoid passing address of root to the func
            if(*pp == NULL)
                throw SetException("no matching key found");
            
            func((*pp)->item);
        }
        
        //save to file functional object
        template<typename T>
        struct BinaryTreeLSaveFuncObj
        {
        public:
            BinaryTreeLSaveFuncObj(std::ofstream* pp) : pfs(pp){}
            
            void operator()(const T& item)
            {
                (*pfs) << item << std::endl;
            }
            
        private:
            std::ofstream* pfs;
        };
        
        //See DAPS Chapter 10 Page 552 
        //save via PREORDER to preserver original tree structure 
        //save via INORDER, and reload via binary_reload to produce balanced tree
        //
        //always save node count as the first item in the disk file
        template<typename T>
        void BinaryTreeL<T>::save(const std::string& filename) const throw(SetException)
        {
            using namespace std;
            ofstream ofs;
            ofs.open(filename.c_str());
            
            if(ofs.fail())
                throw SetException("failed to open file for save");
            
            ofs << count << endl;
            
            BinaryTreeLSaveFuncObj<T> otls(&ofs);
            recursive_traverse(INORDER,root,otls);
            
            ofs.close();
        }
        
        
        template<typename T>
        void BinaryTreeL<T>::recursive_read(TNode*& ptr, int n, std::ifstream& ifs)
        {
            if(n > 0)
            {
                //spawn node node 
                ptr = new TNode();
                ptr->lchild = ptr->rchild = NULL;
            
                //construct left child first 
                recursive_read(ptr->lchild, (int)(n/2), ifs);
                
                //read current node 
                ifs >> ptr->item;
                
                //construct right child 
                recursive_read(ptr->rchild, (int)((n-1)/2), ifs);
            }
        }
        
        template<typename T>
        void BinaryTreeL<T>::restore(const std::string& filename) throw(SetException)
        {
            using namespace std;
            ifstream ifs;
            ifs.open(filename.c_str());
            
            if(ifs.fail())
                throw SetException("failed to open file for load");
            
            
            clear(); 
            ifs >> count;
            
            recursive_read(root, count, ifs);
        }

        
        //raise exception if identical keyed node found 
        template<typename T>
        template<typename K>
        void BinaryTreeL<T>::insert(const T& item) throw(SetException)
        {
            TNode** pp = recursive_search(&root, (K)item); //conversion from item type to key type
            if(*pp != NULL)
                throw SetException("insert failed. existing key found");

            //insert at the obtained address
            *pp = new TNode();
            (*pp)->item = item;
            (*pp)->lchild = (*pp)->rchild = NULL;
            
            count++;
        }
        
        //raise exception if no keyed node found
        template<typename T>
        template<typename K>
        void BinaryTreeL<T>::remove(const K& key) throw(SetException)
        {
            TNode **pp = recursive_search(&root, key);
            if(*pp == NULL)
                throw SetException("deletion error. no matching key found");
            
            remove_node(*pp);
            
            count--;
        }
        
        //See DAPS Chapter 10 Trees, Page 528 
        //p has no child node
        //p has one child node
        //p has two child node 
        //   -- swap N with p's in-order successor 
        //   -- delete p's in-order successor
        template<typename T>
        void BinaryTreeL<T>::remove_node(TNode *&ptr)
        {
            if(!ptr)
                return;
            
            if(!ptr->lchild && !ptr->rchild)  //leaf node
            {
                delete ptr;
                ptr = NULL;
            }
            else 
            if(ptr->lchild && !ptr->rchild)  //left child not null
            {
                TNode* tmp = ptr;
                ptr = ptr->lchild;
                delete tmp; tmp = NULL;
            }
            else
            if(!ptr->lchild && ptr->rchild) //right child not null
            {
                TNode* tmp = ptr;
                ptr = ptr->rchild;
                delete tmp; tmp = NULL;
            }
            else    //both child exist
            {
                //cur is a pointer reference 
                TNode **cur = &(ptr->rchild);
                
                //reach node having no left child (in-order successor)
                while((*cur)->lchild)
                    cur = &((*cur)->lchild);
                
                //swap cur and ptr
                T  tmp = (*cur)->item;
                (*cur)->item = ptr->item;
                ptr->item = tmp;
                
                //remve cur node (from whereever it is pointed)
                remove_node(*cur); 
            }
        }
        
        //extract item matching the key
        template<typename T>
        template<typename K>
        void BinaryTreeL<T>::retrieve(const K& key, T& item) const throw(SetException)
        {
            TNode * ptr = root;
            TNode** pp = recursive_search( &ptr, key); //avoid passing address of root to the func
            if(*pp == NULL)
                throw SetException("retrieve failed. no matching key found");
            
            item = (*pp)->item;
        }

        template<typename T>
        BinaryTreeL<T>::~BinaryTreeL()
        {
            clear();
        }
        
        template<typename T>
        void BinaryTreeL<T>::clear()
        {
            recursive_clear(root);
            count = 0;
        }
        
        template<typename T>
        void BinaryTreeL<T>::recursive_clear(TNode*& ptr)
        {
            if(ptr){
                recursive_clear(ptr->lchild); 
                recursive_clear(ptr->rchild);
                delete ptr;
                ptr = NULL;
            }
        }
        
        template<typename T>
        BinaryTreeL<T>& BinaryTreeL<T>::operator=(const BinaryTreeL<T>& bt)
        {
            if(this != &bt)
            {
                clear();
                recursive_create(root, bt.root);
            }
            return *this;
        }
        
        //copy subtrees from source to target
        template<typename T>
        void BinaryTreeL<T>::recursive_create(TNode*& target, const TNode* source)
        {
            if(source)
            {
                target = new TNode;
                target->item = source->item;
                recursive_create(target->lchild, source->lchild);
                recursive_create(target->rchild, source->rchild);
            }
        }
        
        template<typename T>
        int BinaryTreeL<T>::recursive_height(const TNode* ptr) const
        {
            if(ptr)
            {
                int lheight = recursive_height(ptr->lchild);
                int rheight = recursive_height(ptr->rchild);
                return (1+ (lheight > rheight ? lheight : rheight) ); // 1 + max(child height) 
            }
            else 
                return 0;
        }
        
        
        //function object version of the traversal
        template<typename T>
        template<typename F>
        void BinaryTreeL<T>::traverse(TraversalType type, F& funcObj) throw(SetException)
        {
            recursive_traverse(type, root, funcObj);
        }
        template<typename T>
        template<typename F>
        void BinaryTreeL<T>::traverse(TraversalType type, F& funcObj) const throw(SetException)
        {
            recursive_traverse(type, root, funcObj);
        }
        
        /*
        template<typename T, typename K>
        void BinaryTreeL<T,K>::traverse(TraversalType type, ItemHandler func)
        {
            recursive_traverse(type, root, func);
        }

        template<typename T>
        void print_console(const T& item)
        {
            std::cout << item << std::endl;
        }
        */
        
         //function object for node printing
         template<typename T>
         struct BinaryTreeLPrint
         {
         public:
         void operator()(const T& item)
         {
         std::cout << item << std::endl;
         }
         };
         
        
        //print to standard output in mid order
        template<typename T>
        void BinaryTreeL<T>::print() const
        {
            //nonrecursive_traverse(root, print_console<T>);
            BinaryTreeLPrint<T> btp;
            recursive_traverse(PREORDER, root, btp);
            //recursive_traverse(INORDER, root, print_console<T>);
            //recursive_traverse(POSTORDER, root, print_console<T>);
        }
        
/*    
#include "Stack.hpp"
        //recursive traversal using stacks
        template<typename T, typename K>
        void BinaryTreeL<T,K>::nonrecursive_traverse(const TNode* ptr, ItemHandler func) const
        {
            Stack<TNode*> stack;
            TNode* cur = root;
            bool done = false;
            
            while(!done)
            {
                //reaching a new node that nees further traversing down
                if(cur)
                {
                    stack.push(cur);
                    cur = cur->lchild;
                }
                //reaching a null, backtracking up from stack
                else 
                {
                    if(stack.empty()) //if stack null while backtrack, finish
                        done = true;
                    else 
                    {
                        stack.top(cur);
                        func(cur->item);
                        stack.pop();
                        
                        cur = cur->rchild;
                    }
                }
            }
        }
*/
        
        /*
        //time O(n)  - visiting each node exactly once
        //@tt - tranversal type 
        //@ptr - the current subtree to traverse
        //@func - the handler function object to be invoked on each node
        template<typename T, typename K>
        void BinaryTreeL<T,K>::recursive_traverse(TraversalType tt, 
                                                  const TNode* ptr, 
                                                  ItemHandler func) const
        {
            if(ptr)
            {
                switch(tt)
                {
                    case PREORDER:
                        func(ptr->item);
                        recursive_traverse(tt, ptr->lchild,func);
                        recursive_traverse(tt, ptr->rchild,func);
                        break;
                    case INORDER:
                        recursive_traverse(tt, ptr->lchild,func);
                        func(ptr->item);
                        recursive_traverse(tt, ptr->rchild,func);
                        break;
                    case POSTORDER:
                        recursive_traverse(tt, ptr->lchild,func);
                        recursive_traverse(tt, ptr->rchild,func);
                        func(ptr->item);
                        break;
                }
            }
        }
        */
        
        //functional object verion of the recursive traversal
        //using function-level template instead of class-level 
        //to avoid scope issues !!
        template<typename T>
        template<typename F>
        void BinaryTreeL<T>::recursive_traverse(TraversalType tt, const TNode* ptr, F& func) const
        {
            if(ptr)
            {
                switch(tt)
                {
                    case PREORDER:
                        func( ptr->item );
                        recursive_traverse(tt, ptr->lchild,func);
                        recursive_traverse(tt, ptr->rchild,func);
                        break;
                    case INORDER:
                        recursive_traverse(tt, ptr->lchild,func);
                        func(ptr->item);
                        recursive_traverse(tt, ptr->rchild,func);
                        break;
                    case POSTORDER:
                        recursive_traverse(tt, ptr->lchild,func);
                        recursive_traverse(tt, ptr->rchild,func);
                        func(ptr->item);
                        break;
                }
            }
        }
        
        
    }//adt
}//AstemSoft












#endif