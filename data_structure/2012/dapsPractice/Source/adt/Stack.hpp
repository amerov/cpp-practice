//
//  Stack.h
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-19.
//
#ifndef ASTEMSOFT_ADT_STACK_HPP
#define ASTEMSOFT_ADT_STACK_HPP

#include <exception>
#include "List.hpp" //Interface for Stack's Container Implementation
#include "AList.hpp"
#include "LList.hpp"

namespace astemsoft 
{

    //Stack Exception
    class StackException : public std::exception
    {
    public:
        StackException(const std::string& msg = "") : message(msg){}
        ~StackException() throw(){}
        const char* what() const throw()
        {
            return ("AstemSoft ADT Stack Exception: " + message).c_str();
        }
    private:
        std::string message;
    };

    /**
     Generic Stack Implementation 
     LIFO - last in, first out 
     
     T specify the item type
     Container specify the ADT List implementation class (must inherit from AstemSoft::List)
     **/
    template<typename T, class Container = AList<T> >
    class Stack
    {
    public:
        Stack();
        Stack(const Stack& stk) throw(StackException);
        Stack& operator =(const Stack& stk) throw(StackException);
        virtual ~Stack();

    public:
        bool empty() const{ return base->empty();}
        void push(const T& item) throw(StackException);  //push new item on top of stack
        void pop(); //pop top item from stack
        void top(T& item) const throw(StackException); //retrieve top item 
        void print() const{ base->print();}

    private:
        //ADT List Implementation of Stack Base
        List<T>* base;
    };

    
    // add new item to top of stack
    template<typename T, class C>
    void Stack<T,C>::push(const T& item) throw(StackException)
    {
        try{
            base->insert(base->size(),item);
        }
        catch(ListException e)
        {
            throw StackException(e.what()); //report upwards
        }
        
    }
    
    //remove top item on stack
    template<typename T,class C>
    void Stack<T,C>::pop()
    {
        try{
            base->remove(base->size()-1); 
        }
        catch(ListException e){}
    }
    
    //retrieve top item on stack
    template<typename T,class C>
    void Stack<T,C>::top(T& item) const throw(StackException)
    {
        if(base->empty())
            throw StackException("stack empty");
        
        base->retrieve(base->size()-1,item);
    }

    //
    //copy constructor
    //
    template<typename T,class C>
    Stack<T,C>::Stack(const Stack<T,C>& stk) throw(StackException) : base(NULL)
    {
        *this = stk;
    }
    
    //
    //assignment operator 
    //
    template<typename T,class C>
    Stack<T,C>& Stack<T,C>::operator =(const Stack<T,C>& stk) throw(StackException)
    {
        if(this != &stk)
        {
            if(base){
                delete base;
                base = NULL;
            }
            
            //construct container 
            //according to compile-time object type
            base = new C( *((C*)stk.base) );
        }
        return *this;
    }

    //
    //instantiate stack with specific list 
    //implementation
    //
    template<typename T,class C>
    Stack<T,C>::Stack()
    {
        base = new C();
    }


    //
    //on destruction, release list data
    //
    template<typename T,class C>
    Stack<T,C>::~Stack()
    {
        if(base){
            delete base;
            base = NULL;
        }
    }


}
#endif
