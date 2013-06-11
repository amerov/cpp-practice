//
//  allist.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-10.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_allist_hpp
#define cpp_practice_allist_hpp

#include <iostream>
#include <cassert>


namespace dennycd {
 
    /**
      Acyclic Singly linked list
     **/
    template<typename T>
    class ALList{
    public:
        ALList();
        ALList(const ALList& list);
        ALList(const std::initializer_list<T>& list);
        virtual ~ALList();
        ALList& operator=(const ALList& list);
        
    public:
        void insert(int idx, const T& item);
        void remove(int idx);
    
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
        LNode* _tail;
        
    private:
        void _reset();
    };
    
    template<typename T>
    ALList<T>::ALList(const std::initializer_list<T>& list){
        _head = _tail = new LNode();
        _head->next = _head;
        for(auto item = list.begin(); item != list.end(); item++){
            _tail->next = new LNode(*item, _head);
            _tail = _tail->next;
        }
    }
    
    template<typename T>
    ALList<T>& ALList<T>::operator=(const ALList<T>& list){
        if(this != &list){
            _reset();
            LNode* cur = list._head->next;
            while(cur!=list._head){
                _tail->next =  new LNode(cur->data, _head);
                _tail = _tail->next;
                cur = cur->next;
            }
        }
        return *this;
    }
    
    template<typename T>
    ALList<T>::ALList(const ALList& list){
        _head = _tail = new LNode();
        _head->next = _head;
        this->operator=(list);
    }
    
    template<typename T>
    ALList<T>::ALList(){
        _head = _tail = new LNode();
        _head->next = _head;
    }
    
    
    template<typename T>
    ALList<T>::~ALList(){
        _reset();
        delete _head;
    }
    
    //O(n) cleanup
    template<typename T>
    void ALList<T>::_reset(){
        LNode* cur = NULL;
        while(_head->next != _head){
            cur = _head->next;
            _head->next = cur->next;
            delete cur;
        }
        _tail = _head;
    }

    //O(n) indexing, O(1) insert
    template<typename T>
    void ALList<T>::insert(int idx, const T& item)
    {
        int pos = 0;
        LNode* pre = _head;
        while(pre->next!=_head && pos < idx)
        {
            pre = pre->next;
            pos += 1;
        }
        
        if(pos!=idx) throw std::exception();
        pre->next = new LNode(item, pre->next);
        if(pre->next->next == _head)
            _tail = pre->next;
    }
    
    template<typename T>
    void ALList<T>::remove(int idx)
    {
        int pos = 0;
        LNode* pre = _head;
        while(pre->next!=_head && pos < idx){
            pre = pre->next;
            pos += 1;
        }
        
        if(pos!=idx || pre->next==_head)
            throw std::exception();
        LNode* del = pre->next;
        pre->next = del->next;
        delete del;
        if(pre->next == _head)
            _tail = pre;
    }
    
}
#endif
