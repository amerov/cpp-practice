//
//  ALList.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-24.
//  -
//
#ifndef ASTEMSOFT_ADT_ARRAY_BASED_LINK_LIST_HPP
#define ASTEMSOFT_ADT_ARRAY_BASED_LINK_LIST_HPP

#include "List.hpp"
#include <iostream>
namespace astemsoft
{
    namespace adt
    {

        /**
         An Array-Based Link-List Style Implementation for ADT List
         See DAPS Chapter 4, Programming Problem 9, Page 234
         **/
        template<typename T>
        class ALList : public List<T>
        {
        public:
            static const int DEFAULT_CAPACITY = 2;
        private:
            struct ALNode{
                T item;
                int next; //index to next linked node
            public:
                ALNode(): next(-1){}
            };
            
        public:
           
            ALList() throw(ListException);
            ALList(const ALList& al) throw(ListException);
            ALList& operator =(const ALList& al) throw(ListException);
            virtual ~ALList();
            
            
        public:
            void clear();
            int size() const{return count;}
            bool empty() const{ return (head == -1);}
            void insert(int index, const T& item) throw(ListException);
            void remove(int index) throw(ListException);
            void retrieve(int index, T& item) const;
            void print() const;
            
        private:
            void initialize() throw(ListException);
            void expand() throw(ListException);
            ALNode* base; 
            int capacity; 
            int count;
            int head; //index of first item
            int free; //index of first empty slot
        };

        
        template<typename T>
        void ALList<T>::insert(int index, const T& item) throw(ListException)
        {
            if(free==-1)
                expand();
            if(index < 0 || index > count)
                throw ListException("insertion: index invalid");
            
            
            int pre = -1, cur = head;
            for(int i=0;i<index;i++)
            {
                pre = cur;
                cur = base[cur].next;
            }
            
            //insert right after pre, shift cur downwards
            
            //take one from free list
            int idx = free;
            free = base[free].next;
            
            //append cur after idx
            base[idx].item = item;
            base[idx].next = cur;
            
            //append idx after pre 
            if(pre==-1)
                head = idx;
            else 
                base[pre].next = idx;
            
            count++;
        }
        
        
        template<typename T>
        void ALList<T>::remove(int index) throw(ListException)
        {
            if(head==-1)
                throw ListException("empty list for removal");
            if(index < 0 || index >= count)
                throw ListException("removal: index out of bound");

            
            int pre = -1, cur = head;
            for(int i=0;i<index;i++)
            {
                pre = cur;
                cur = base[cur].next;
            }
            
            //detach cur from list
            if(pre==-1)
                head = base[cur].next;
            else 
                base[pre].next = base[cur].next;
            
            //move cur to head of free list
            base[cur].next = free;
            free = cur;

            count--;
            
            if(count==0)
                head = -1;
        }
        
        
        template<typename T>
        void ALList<T>::retrieve(int index, T& item) const
        {
            if(index < 0 || index >= count)
                throw ListException("retrieval: index out of bound");
            
            int cur = head;
            for(int i=0;i<index;i++)
                cur = base[cur].next;
            
            item = base[cur].item;
        }
        
        
        template<typename T>
        void ALList<T>::print() const
        {
            std::cout << "list capacity = " << capacity << std::endl;
            for(int i=0,cur=head;i<count;i++)
            {
                std::cout << base[cur].item << std::endl;
                cur = base[cur].next;
            }
        }
        
        
        /**
         the content list kept untouched
         free list is expaned into the extra segment
         double the original capacity
         **/
        template<typename T>
        void ALList<T>::expand() throw(ListException)
        {
            if(!base)
                return;

            ALNode* newbase = new ALNode[2*capacity];
            if(!newbase)
                throw ListException("heap memory alloc failed");
               
            //copy existing content to lower segment
            for(int i=0;i<capacity;i++)
                newbase[i] = base[i];
            
            //expand free list through high segment
            //tail existing free list to the ned
            //and update free head to the start of high segment
            for(int i=capacity;i< 2*capacity-1; i++)
                newbase[i].next = i + 1;
            
            newbase[2*capacity-1].next = free;
            free = capacity;
          
            delete[] base;
            base = newbase;
            capacity = 2 * capacity;
                
            //head, count remains unchanged
            //std::cout << "expanding to " << capacity << std::endl;
        }
        
        
        template<typename T>
        void ALList<T>::initialize() throw(ListException)
        {
            if(base){
                delete[] base;
                base = NULL;
            }
            
            capacity = DEFAULT_CAPACITY;
            base = new ALNode[capacity];
            if(!base)
                throw ListException("heap memory alloc failed");
            
            head = -1;
            //initalize state of the free list
            //all nodes are free list
            free = 0;
            for(int i=0;i<capacity-1;i++)
            {
                base[i].next = i+1;
            }
            base[capacity-1].next = -1;
            count = 0;
        }
        
        template<typename T>
        void ALList<T>::clear() 
        {
            initialize();
        }

        template<typename T>
        ALList<T>::~ALList()
        {
            if(base)
            {
                delete[] base;
                base = NULL;
            }
        }
        
        template<typename T>
        ALList<T>::ALList()throw(ListException)  : base(NULL) 
        {
            initialize();
        }
        
        
        template<typename T>
        ALList<T>::ALList(const ALList<T>& al) throw(ListException)  : base(NULL) 
        {
            *this = al;
        }
        
        template<typename T>
        ALList<T>& ALList<T>::operator =(const ALList<T>& al) throw(ListException)
        {
            if(this!=&al)
            {
                if(base){
                    delete[] base;
                    base = NULL;
                }
                
                capacity = al.capacity;
                base = new ALNode[capacity];
                if(!base)
                    throw ListException("heap memory alloc failed");
                
                head = al.head;
                free = al.free;
        
                for(int i=0;i<capacity;i++)
                {
                    base[i] = al.base[i];
                }
                
                count = al.count;
            }
            return *this;
        }
        
        
    }
}
#endif