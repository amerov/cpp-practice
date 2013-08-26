//
//  SetASorted.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-29.
//  -
//
#ifndef ASTEMSOFT_ADT_ARRAY_LIST_SORTED_HPP
#define ASTEMSOFT_ADT_ARRAY_LIST_SORTED_HPP

#include "Set.hpp"
#include <cassert>
#include <iostream>

namespace astemsoft
{
    namespace adt
    {

        /**
         A Sorted Array-Based ADT Set Implementation
         Data are sorted in asending order
         
         ITEM - the data item type
         **/
        template<typename ITEM>
        class SetASorted : public Set<ITEM>
        {
            static const int DEFAULT_CAPACITY = 2;
        public:
            SetASorted() throw(SetException);
            SetASorted(const SetASorted& list) throw(SetException);
            virtual ~SetASorted();
            SetASorted& operator =(const SetASorted& list) throw(SetException);
            
            void clear();
            bool empty() const{return count==0;}
            int size() const{return count;}
            
            void print() const;
            
            // O(N) worst case time complexity for insertion
            // O(logN) for search, O(n) for insert/shift
            template<typename KEY>
            void insert(const ITEM& item) throw(SetException);
            
            // O(N) worst case time complexity
            // O(logN( for search, O(n) for remove/shift
            template<typename KEY> 
            void remove(const KEY& key) throw(SetException);
            
            // O(logN) for retrieval
            template<typename KEY> 
            void retrieve(const KEY& key, ITEM& item) const throw(SetException); 
            
            // O(logN) for locating the object
            // O(logN) * K where K is the time cost on funcional handler
            //throw exception if none exist
            template<typename FUNC, typename KEY>
            void update( FUNC& func, const KEY& key) throw(SetException);
            
            //  contant time at N
            template<typename FUNC>
            void traverse(FUNC& func) throw(SetException);
            
            template<typename FUNC>
            void traverse(FUNC& func) const throw(SetException);
            
            ITEM& operator [](int index) const throw(SetException);
            
            template<typename KEY>
            bool exist(const KEY& key) throw(SetException);
        private:
            /**
             Standard Binary Search Algorithm
             Worst Case Time Complexity (WCTC): O(logN) 
             
             @begin, end - bounding index for the search
             @key - the target key to search for
             @found - return falg indicating search result
             @return - item index (found=true); expected insertion index (found=false)
             **/
            template<typename KEY> 
            int recursive_binary_search(int begin, int end, 
                                        const KEY& key, bool& found) const;
            
            void expand() throw(SetException);
            ITEM* base;
            int count;
            int capacity;
        };
        
        
        template<typename ITEM>
        template<typename KEY>
        bool SetASorted<ITEM>::exist(const KEY& key) throw(SetException)
        {
            bool found;
            recursive_binary_search(0, count-1, key, found);
            return found;
        }
        
        template<typename ITEM>
        ITEM& SetASorted<ITEM>::operator [](int index) const throw(SetException) 
        {
            if(index < 0 || index >= count)
                throw SetException("index out of bound");
            return base[index];
        }
        
        template<typename ITEM>
        template<typename FUNC, typename KEY>
        void SetASorted<ITEM>::update( FUNC& func, const KEY& key) throw(SetException)
        {
            bool found;
            int idx = recursive_binary_search(0, count-1, key, found);
            
            if(!found)
                throw SetException("keyed item not found");
            
            func(base[idx]);
        }
        
        template<typename ITEM>
        template<typename FUNC>
        void SetASorted<ITEM>::traverse(FUNC& func) throw(SetException)
        {
            for(int i=0;i<count;i++)
                func(base[i]);
        }
        
        //a constant version
        template<typename ITEM>
        template<typename FUNC>
        void SetASorted<ITEM>::traverse(FUNC& func) const throw(SetException)
        {
            for(int i=0;i<count;i++)
                func(base[i]);
        }
        
        template<typename ITEM>
        void SetASorted<ITEM>::expand() throw(SetException)
        {
            ITEM* newbase = new ITEM[2*capacity];
            if(!newbase)
                throw SetException("heap memory alloc failed");
            
            for(int i=0;i < capacity; i++)
                newbase[i] = base[i];
                
            if(base)
            {
                delete[] base;
                base = NULL;
            }
            
            base = newbase;
            capacity = 2 * capacity;
        }
        
        template<typename ITEM>
        template<typename KEY>
        void SetASorted<ITEM>::insert(const ITEM&item) throw(SetException)
        {
            bool found;
            int idx = recursive_binary_search(0, count-1, (KEY)item, found);
            
            if(found)
                throw SetException("keyed item exist");
            
            if(count == capacity)
                expand();
            
            //shift [idx ... count-1] righwards
            for(int i= count-1; i>=idx; i--)
                base[i+1] = base[i];
            
            base[idx] = item;
            count++;
        }
        
        template<typename ITEM>
        template<typename KEY> 
        void SetASorted<ITEM>::remove(const KEY& key) throw(SetException)
        {
            bool found;
            int idx = recursive_binary_search(0, count-1, key, found);
            
            if(!found)
                throw SetException("keyed item not found");
            
            //shift [idx+1 ... count-1] leftwards
            for(int i=idx+1; i<count; i++)
                base[i-1] = base[i]; 
            
            count--;
        }
        
        template<typename ITEM>
        template<typename KEY> 
        void SetASorted<ITEM>::retrieve(const KEY& key, ITEM& item) const throw(SetException)
        {
            bool found;
            int idx = recursive_binary_search(0, count-1, key, found);
            
            if(!found)
                throw SetException("keyed item not found");
            
            item = base[idx];
        }
        

        
        template<typename ITEM>
        void SetASorted<ITEM>::print() const
        {
            std::cout << "current capacity: " << capacity << std::endl;
            
            for(int i=0;i<count;i++)
                std::cout << base[i] << std::endl;
        }
        
        template<typename ITEM>
        void SetASorted<ITEM>::clear()
        {
            if(base)
            {
                delete[] base;
                base = NULL;
            }
            
            capacity = DEFAULT_CAPACITY;
            count = 0;
            base = new ITEM[capacity];
        }
        
        template<typename ITEM>
        SetASorted<ITEM>::~SetASorted()
        {
            if(base)
            {
                delete[] base;
                base = NULL;
            }
        }
        
        template<typename ITEM>
        SetASorted<ITEM>::SetASorted() throw(SetException) : base(NULL)
        {
            capacity = DEFAULT_CAPACITY;
            count = 0;
            base = new ITEM[capacity];
            if(!base)
                throw SetException("heap memory alloc failed");
        }
        
        
        template<typename ITEM>
        SetASorted<ITEM>::SetASorted(const SetASorted<ITEM>& list) throw(SetException)
        : base(NULL)
        {
            *this = list;
        }
        
        template<typename ITEM>
        SetASorted<ITEM>& SetASorted<ITEM>::operator =(const SetASorted<ITEM>& list) throw(SetException)
        {
            if(this != &list)
            {
                ITEM* newbase = new ITEM[list.capacity];
                if(!newbase)
                    throw SetException("heap memory alloc failed");
                
                if(base)
                {
                    delete[] base;
                    base = NULL;
                }
                
                capacity = list.capacity;
                count = list.count;
                base = newbase;
                
                for(int i=0;i<count;i++)
                    base[i] = list.base[i];
            }
            return *this;
        }
        
        template<typename ITEM> 
        template<typename KEY>
        int SetASorted<ITEM>::recursive_binary_search(int begin, int end, 
                                                       const KEY& key,
                                                       bool& found) const
        {
            found = false;
            
            if(begin <= end)
            {
                int n = end - begin + 1;
                int k = (int)(n/2); //take floor of half
                
                if(base[begin+k] > key) //search lower half
                    if(begin==end)
                        return begin;
                    else 
                        return recursive_binary_search(begin, begin + k -1, key, found);
                else 
                if(base[begin+k] < key) //search higher half
                    if(begin==end)
                        return (begin+1);
                    else 
                        return recursive_binary_search(begin + k + 1, end, key, found);
                else
                {
                    found = true;
                    return (begin+k); // search hit in intermediate step
                }
            }
            else 
                return begin; //for cases of begin points to pos after the last item
        }
        
    }
}




















#endif
