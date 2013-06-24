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
        size_t size() const { return _count;}
        
        void insert(int idx, const T& item);
        void remove(int idx);
        
        //indexing
        T& operator[](int idx);
        const T& get(int index) const;
        void set(int index, const T& item);
        
        //find
        template<typename K>
        int find(const K& key) const;

        template<typename K>
        friend std::ostream& operator <<(std::ostream& oss, const ALList<K>& list);
        
        void clear(){ _reset(); }
        
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
        size_t _count;
        
    private:
        void _reset();
    };
    
    //=== IMPLEMENTATION

    template<typename K>
    std::ostream& operator <<(std::ostream& oss, const ALList<K>& list){
        oss << "[";
        auto cur = list._head->next;
        while(cur!=list._head){
            oss << cur->data;
            if(cur->next != list._head) oss << ",";
            cur = cur->next;
        }
        oss << "]";
        return oss;
    }
    
    
    template<typename T> template<typename K>
    int ALList<T>::find(const K& key) const{
        int pos = 0;
        LNode* cur = _head->next;
        while(cur != _head && cur->data != key){
            pos += 1;
            cur = cur->next;
        }
        
        return cur==_head ? -1 : pos; 
        
    }
    
    //O(n) for indexing
    // O(1) for tail access 
    template<typename T>
    const T& ALList<T>::get(int idx) const{
        
        if(idx >=0 && idx==_count-1) //tail case
            return _tail->data;
        
        LNode* cur = _head;
        for(int pos=0; pos <= idx; pos++){
            cur = cur->next;
            if(cur==_head) throw std::exception(); // invalid index
        }
        return cur->data;
    }
    
    template<typename T>
    void ALList<T>::set(int idx, const T&item){
        this->operator[](idx) = item;
    }
    
    //O(n) for indexing
    // O(1) for tail access
    template<typename T>
    T& ALList<T>::operator[](int idx)
    {
        if(idx >=0 && idx==_count-1) //tail case 
            return _tail->data;
        
        LNode* cur = _head;
        for(int pos=0; pos <= idx; pos++){
            cur = cur->next;
            if(cur==_head) throw std::exception(); // invalid index
        }
        return cur->data;
    }
    
    template<typename T>
    ALList<T>::ALList(const std::initializer_list<T>& list){
        _head = _tail = new LNode();
        _head->next = _head;
        _count = list.size();
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
            _count = list._count;
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
        _count = 0;
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
        _count = 0;
    }

    //O(n) indexing, O(1) insert
    //O(1) for tail insertion 
    template<typename T>
    void ALList<T>::insert(int idx, const T& item)
    {
        if(idx==_count){  //insertion at tail
            _tail->next = new LNode(item, _head);
            _tail = _tail->next;
        }
        else{
            int pos = 0;
            LNode* pre = _head;
            while(pre->next!=_head && pos < idx)
            {
                pre = pre->next;
                pos += 1;
            }
            
            if(pos!=idx) throw std::exception();
            pre->next = new LNode(item, pre->next);
        }
        
        _count += 1;
    }
    

    //O(n) indexing, O(1) insert
    // O(n) for tail removal - as there is no
    // acces to the node preceding the tail 
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
        
        _count -= 1;
    }
    
}
#endif
