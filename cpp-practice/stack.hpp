//
//  stack.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-11.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_stack_hpp
#define cpp_practice_stack_hpp

#include <iostream>

namespace dennycd {

    /**
      Stack 
       FIFO - first in first out 
     
     C - the container array 
     E - the data element type
     **/
    template<typename C, typename E>
    class Stack{
    public:
        size_t size() const{return _data.size(); }
        bool empty() const{ return _data.size()==0; }
        void push(const E& item);
        E pop();
        E& top(); //return the top value
        
        template<typename CC, typename EE>
        friend std::ostream& operator<<(std::ostream& oss, const Stack<CC,EE>& st);
        
    public:
        Stack();
        Stack(const Stack& st);
        Stack(const std::initializer_list<E>& list);
        virtual ~Stack();
        Stack& operator=(const Stack& st);
    private:
        C  _data;
    };
    
    template<typename CC, typename EE>
    std::ostream& operator<<(std::ostream& oss, const Stack<CC,EE>& st)
    {
        oss << "[" << st._data << "]";
        return oss;
    }
    
    //== interface
    
    template<typename C, typename E>
    E& Stack<C,E>::top(){
        if(_data.size()==0) throw std::exception();
        return _data[0];
    }
    
    template<typename C, typename E>
    E Stack<C,E>::pop(){
        E val = _data[0];
        _data.remove(0);
        return val;
    }
    
    template<typename C, typename E>
    void Stack<C,E>::push(const E& item){
        _data.insert(0,item);
    }

    
    //== init
    template<typename C, typename E>
    Stack<C,E>::Stack(){
    }
    
    template<typename C, typename E>
    Stack<C,E>::Stack(const Stack& st){
        this->operator=(st);
    }
    
    template<typename C, typename E>
    Stack<C,E>::~Stack(){
    }
    
    template<typename C, typename E>
    Stack<C,E>::Stack(const std::initializer_list<E>& list) : _data(list){
    }
    
    template<typename C, typename E>
    Stack<C,E>& Stack<C,E>::operator=(const Stack<C,E>& st){
        if(this != &st){
            _data = st._data;
        }
        return *this;
    }
    
    
}

#endif
