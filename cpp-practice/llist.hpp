//
//  llist.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-10.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_llist_hpp
#define cpp_practice_llist_hpp

#include <iostream>
#include <cassert>

namespace dennycd {
    
    /**
     Pointer-based Non-Circular Singly Link List Implementation
     **/
    template<typename T>
    class LList{
    public:
        LList();
        LList(const LList& list);
        LList(const std::initializer_list<T>& list);
        LList& operator=(const LList& list);
        virtual ~LList();
        
    public:
        void insert(int idx, const T& item);
        void remove(int idx);
        
        //indexing
        const T& get(int index) const;
        void set(int index, const T& item);
        T& operator[](int idx);
        
        //search
        template<typename K>
        int find(const K& key) const;
    
    protected:

        //link list node type
        struct LNode {
            T data;
            LNode* next;
            LNode() : next(NULL){}
            LNode(const LNode& node) : data(node.data), next(NULL){}
            LNode(const T&d, LNode*n = NULL) : data(d),next(n){}
        };
        
        
        LNode* _head;
        size_t _count;
        
    private:
        void _reset(); //reset the list to empty
    };
    
        
    template<typename T>
    LList<T>::LList(){
        _head = new LNode();
        _count = 0;
    }
    
    template<typename T>
    LList<T>::~LList<T>(){
        _reset(); 
        delete _head;
    }
    
    //copy constructor
    template<typename T>
    LList<T>::LList(const LList& list){
        _head = new LNode();
        this->operator=(list);
    }
    
    template<typename T>
    LList<T>::LList(const std::initializer_list<T>& list){
        _head = new LNode();
        _count = list.size();
        
        LNode* tail = _head;
        for(auto item = list.begin(); item != list.end(); item++)
        {
            tail->next = new LNode(*item);
            tail = tail->next;
        }
    }
    
    template<typename T>
    LList<T>& LList<T>::operator=(const LList<T>& list){
        if(this != &list){
            this->_reset(); //empty self
            LNode* tail = _head; //tailing node of self;
            LNode* cur = list._head->next; //next node to copy in target
            while(cur){
                tail->next = new LNode(*cur);
                tail = tail->next;
                cur = cur->next;
                _count += 1;
            }
        }
        return *this;
    }
    
    //empty the list
    // O(n)
    template<typename T>
    void LList<T>::_reset()
    {
        LNode* cur = NULL;
        while (_head->next) {
            cur = _head->next;
            _head->next = cur->next;
            delete cur;
        }
        _count = 0;
    }
    
    
    //===== public interface
    
    //O(n)
    // O(n) for indexing, O(1) for insert opt
    template<typename T>
    void LList<T>::insert(int idx, const T& item){
        int pos = 0;
        LNode* pre = _head;
        while (pos < idx && pre){
            pre = pre->next;
            pos += 1;
        }
        
        if(!pre) throw std::exception(); 
        pre->next = new LNode(item,pre->next);
    }
    
    
    //O(n)
    // - O(n) for indexing =, O(1) for removal
    template<typename T>
    void LList<T>::remove(int idx){
        int pos = 0;
        LNode* pre = _head;
        while (pos < idx && pre){
            pre = pre->next;
            pos += 1;
        }
        
        //if attempting to delete a non-existing node
        if(!pre || pre->next==NULL) throw std::exception();
        LNode* del = pre->next;
        pre->next = del->next;
        delete del;
    }
    
    //O(n) indexing
    template<typename T>
    T& LList<T>::operator[](int idx){
        int pos = 0;
        LNode* pre = _head->next;
        while (pos < idx && pre){
            pre = pre->next;
            pos += 1;
        }
        
        if(pos!=idx) throw std::exception(); //premature stop 
        return pre->data;
    }
    
    template<typename T>
    const T& LList<T>::get(int idx) const{
        return this->operator[](idx);
    }
    
    template<typename T>
    void LList<T>::set(int idx, const T& item){
        this->operator[](idx) = item;
    }
    
    ///O(n) search
    template<typename T> template<typename K>
    int LList<T>::find(const K& key) const{
        int pos = 0;
        LNode* cur = _head->next;
        while(cur){
            if(cur->data == key) break;
            cur = cur->next;
            pos += 1;
        }
        return cur ? pos : -1;
    }
}






#endif
