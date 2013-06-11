//
//  queue.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-11.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_queue_hpp
#define cpp_practice_queue_hpp

#include <iostream>

namespace dennycd {
    
    /**
      Queue 
       FILO - first in last out 
     
     C - container type
     E - data element type
     **/
    template<typename C, typename E>
    class Queue{
    public:
        size_t size() const{ return _data.size(); }
        bool empty() const{ return _data.size()==0;}
        void enqueue(const E& item);
        E& front();
        E dequeue();
        
        template<typename CC, typename EE>
        friend std::ostream& operator<<(std::ostream& oss, const Queue<CC,EE>& q);
        
    public:
        Queue(){}
        virtual ~Queue(){}
        Queue(const Queue& q){ this->operator=(q); }
        Queue(const std::initializer_list<E>& list) : _data(list) {}
        Queue& operator=(const Queue& q){
            if(this!=&q) _data = q._data;
            return *this;
        }
        
    protected:
        C _data;
    };
    
    template<typename CC, typename EE>
    std::ostream& operator<<(std::ostream& oss, const Queue<CC,EE>& q)
    {
        oss << "[" << q._data << "]";
        return oss;
    }
    
    template<typename C, typename E>
    void Queue<C,E>::enqueue(const E& item){
        _data.insert(0,item);
    }
    
    template<typename C, typename E>
    E& Queue<C,E>::front(){
        return _data[(int)_data.size()-1];
    }
    
    template<typename C, typename E>
    E Queue<C,E>::dequeue(){
        E ret = _data[(int)_data.size()-1];
        _data.remove((int)_data.size()-1);
        return ret;
    }
    
    
}

#endif
