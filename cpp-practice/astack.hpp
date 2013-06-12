//
//  astack.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-11.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_astack_hpp
#define cpp_practice_astack_hpp

#include <iostream>

namespace dennycd {

    const int MAX_STACK_SIZE = 1024;
    
    /**
      Array-based implementation of Stack
     */
    template<typename E>
    class AStack{
    public:
        
        //O(1)
        void push(const E& item){
            if(_top+1 > MAX_STACK_SIZE) throw std::exception();
            _base[++_top] = item;
        }
        
        //O(1)
        E pop(){
            if(_top<0) throw std::exception();
            return _base[_top--];
        }
        
        //O(1)
        E& top(){
            if(_top<0) throw std::exception();
            return _base[_top];
        }
        
        
        int size() const{return _top+1;}
        bool empty() const{return _top==-1;}
    public:
        AStack() : _top(-1){}
        //virtual ~AStack(){}
        template<typename EE> friend std::ostream& operator<<(std::ostream& oss, const AStack<EE>& st);
        
    protected:
        E _base[MAX_STACK_SIZE]; 
        int _top; //top index of the stack
    };
    
    template<typename EE>
    std::ostream& operator<<(std::ostream& oss, const AStack<EE>& st){
        oss << "{";
        for(int i=st._top; i>=0 ;i--)
        {
            oss << st._base[i];
            if(i>0) oss << ",";
        }
        oss << "}";
        return oss;
    }
}

#endif
