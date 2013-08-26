//
//  Heap.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-10-01.
//  -
//
#ifndef ASTEMSOFT_ADT_HEAP_HPP
#define ASTEMSOFT_ADT_HEAP_HPP

#include <exception>
#include <iostream>

namespace astemsoft
{
    namespace adt
    {
        
        class HeapException : public std::exception
        {
        public:
            HeapException(const std::string& msg = "") : message(msg){}
            ~HeapException() throw(){}
            const char* what() const throw()
            {
                return ("AstemSoft ADT Heap Exception: " + message).c_str();
            }
        private:
            std::string message;
        };
        
        /**
         Array-Based Heap Implementation  
         Defaulted as maxheap: root having the largest key value
         any child nodes have equal/smaller key values 
         
         Heap maintains a complete tree structure , therefore is balanced
         
         the complete tree always maitains a minimum tree height of value
         ceil(log(n+1))  (See DAPS Page 548, Theorem 10-4)
         
         see DAPS Chap.11, Page 594, Chap 10, Page 489 for references
         
         always delete/retrieve from root
         **/
        template<typename T>
        class Heap 
        {
        public:
            static const int DEFAULT_CAPACITY = 2;
            
            Heap();
            Heap(const Heap& hp);
            Heap& operator=(const Heap& hp);
            ~Heap();
        
            bool empty() const{return count==0;}
            int size() const{return count;}
            void clear();
            void print() const;
            
            void insert(const T& item) throw(HeapException);//insert new item
            void remove(T& item) throw(HeapException);//delete and retrieve top
            void top(T& item) const throw(HeapException);//retrieve top item
            
            void rebuild(const T[], int size);//rebuild a heap using item array
            
        private:
            void recursive_rebuild(int root);
            void expand() throw(HeapException);
            T* base;
            int capacity;
            int count;
        };
        
        //
        //Worst Case Time Complexity  N logN 
        //
        // n/2 time for each internal node rebuilt
        // logN time for each rebuilt operation
        template<typename T>
        void Heap<T>::rebuild(const T* arr, int size)
        {
            //maps array to local base
            if(base)
                delete[] base;
            capacity = size;
            count = size;
            base = new T[size];
            for(int i=0;i<size;i++)
                base[i] = arr[i];
            
            
            //start with the last node having child
            //backwards rebuild all node tree up to the top
            //at any time in a comlete tree, the # of leafs is equal to ceil(n/2)
            //the # of internal nodes are floor(n/2)
            //the last index of internal node is therefere  floor(n/2) - 1; 
            for(int i = (int)(count/2) - 1; i >=0; i-- )
                recursive_rebuild(i);
            
            
            print();
        }
        
        
        template<typename T>
        void Heap<T>::top(T& item) const throw(HeapException)
        {
            if(empty())
                throw HeapException("heap empty");
            item = base[0];
        }
        
        
        //recursively rebuilt the tree under root
        //by placing root node under the appropriate place within root's substree
        //@assume root's subtres are valid heap already
        template<typename T>
        void Heap<T>::recursive_rebuild(int root)
        {
            int lchild = -1,rchild = -1,swap = -1;
            
            std::cout << "rebuilding root node at " << root << std::endl; 
            
            //first make the proper swapping at current level to maintain heap consistency
            if(root < count)
            {
                lchild = 2*root+1;                
                if(lchild < count)  //rchild would be even larger
                {
                    swap = lchild;
                    rchild = 2*root+2; 
                    if(rchild < count) 
                    {
                        if(base[rchild] > base[lchild])
                            swap = rchild;
                    }
                }
                
                //if there exist childs,
                //and if existing child has larger key, swap
                if(swap!=-1 && base[swap] > base[root])
                {
                    std::cout << root << " <==> " << swap << std::endl;
                    
                    T tmp = base[root];
                    base[root] = base[swap];
                    base[swap] = tmp;
                    root = swap; //move downwards
                    
                    recursive_rebuild(root);//continue with the swapped node
                }
            }
        }
        
        //Worst Case Time Complexity O(logN) 
        //
        template<typename T>
        void Heap<T>::remove(T& item) throw(HeapException)
        {
            if(empty())
                throw HeapException("heap empty");
            
            item = base[0];
            base[0] = base[count-1];
            count--;
            int cur = 0,lchild,rchild,swap;
            
            //non-recursive version of tree rebuilt 
            //iteratively swapping with the largest child
            //until either leaf reached, or no larger child
            //
            //See DAPS Page 598 for recursive-rebuilt
            while(cur < count)
            {
                lchild = 2*cur+1;                
                swap = -1;
                if(lchild < count)  //rchild would be even larger
                {
                    swap = lchild;
                    rchild = 2*cur+2; 
                    if(rchild < count) 
                    {
                        if(base[rchild] > base[lchild])
                            swap = rchild;
                    }
                }
               
                //if there exist childs,
                //and if existing child has larger key, swap
                if(swap!=-1 && base[swap] > base[cur])
                {
                    T tmp = base[cur];
                    base[cur] = base[swap];
                    base[swap] = tmp;
                    cur = swap; //move downwards
                }
                else 
                    break;
            }
        }
        
        //Worst Case Time Complexity  O(logN)
        template<typename T>
        void Heap<T>::insert(const T& item) throw(HeapException)
        {
            if(count==capacity)
                expand();
            
            base[count] = item;
            
            int cur = count;
            int parent = (int)((cur-1)/2); //parent node
            
            //swap upwards until larger/equal parent reached
            while( parent>=0 && base[cur] > base[parent])
            {
                T tmp = base[cur];
                base[cur] = base[parent];
                base[parent] = tmp;
                cur = parent;
                parent = (int)((cur-1)/2);
            }
            
            count++;
        }
        
        template<typename T>
        void Heap<T>::print() const
        {
            std::cout << "current capacity: " << capacity << std::endl;
            for(int i=0;i<count;i++)
                std::cout << base[i] << std::endl;
            std::cout << "total nodes: " << count << std::endl;
        }
        
        template<typename T>
        void Heap<T>::clear()
        {
            if(base)
                delete[] base;
            
            capacity = DEFAULT_CAPACITY;
            base = new T[capacity];
            count = 0;
        }
        
        template<typename T>
        void Heap<T>::expand() throw(HeapException)
        {
            T* newbase = new T[2*capacity];
            if(!newbase)
                throw HeapException("heap memory alloc failed");
            
            for(int i=0;i<count;i++)
                newbase[i] = base[i];
            
            capacity = 2 * capacity;
            delete base;
            base = newbase;
        }
        
        template<typename T>
        Heap<T>::Heap(const Heap<T>& hp) : base(NULL)
        {
            *this = hp;
        }
        
        template<typename T>
        Heap<T>& Heap<T>::operator=(const Heap<T>& hp)
        {
            if(this!=&hp)
            {
                if(base)
                    delete base;
                capacity = hp.capacity;
                count = hp.count;
                base = new T[capacity];
                
                for(int i=0;i<count;i++)
                    base[i] = hp.base[i];
            }
            return *this;
        }
        
        template<typename T>
        Heap<T>::Heap() : base(NULL)
        {
            capacity = DEFAULT_CAPACITY;
            count = 0;
            base = new T[capacity];
        }
        
        template<typename T>
        Heap<T>::~Heap()
        {
            if(base)
                delete[] base;
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    }
}
#endif