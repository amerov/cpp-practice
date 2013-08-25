//
//  Queue.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-21.
//  -
//
#ifndef ASTEMSOFT_ADT_QUEUE_HPP
#define ASTEMSOFT_ADT_QUEUE_HPP

#include <exception>
#include "List.hpp"
#include "CDLList.hpp"

namespace astemsoft 
{

    //Queue Exception
    class QueueException : public std::exception
    {
    public:
        QueueException(const std::string& msg = "") : message(msg){}
        ~QueueException() throw(){}
        const char* what() const throw()
        {
            return ("AstemSoft ADT Queue Exception: " + message).c_str();
        }
    private:
        std::string message;
    };


    /**
     Generic Queue Implementation Using ADT List
     FIFO - First in, First Out queue
    
     T specify the item type
     Container specify the ADT List implementation. Defaulted to use circular double link list
     (must inherit from AstemSoft ADT List)
     **/
    template<typename T, class Container = CDLList<T> >
    class Queue
    {
    public:
        void enqueue(const T& item) throw(QueueException);
        void dequeue();
        void dequeue(T& item) throw(QueueException);
        void front(T& item) const throw(QueueException); 
        
        bool empty() const{return base->empty();}
        int size() const{return base->size();}
        void print() const{ base->print();}
        
    public:
        Queue();
        Queue(const Queue& q) throw(QueueException);
        Queue& operator =(const Queue& q) throw(QueueException);
        virtual ~Queue();
    
    private:
        List<T> *base; //ADT List Implementation
    };
    
    
    template<typename T, class C>
    void Queue<T,C>::dequeue(T& item) throw(QueueException)
    {
        try{
            base->retrieve(0,item);
            base->remove(0);
        }
        catch(ListException e)
        {
            throw QueueException(e.what());
        }
    }
    
    //append item to end of queue
    template<typename T, class C>
    void Queue<T,C>::enqueue(const T& item) throw(QueueException)
    {
        try{
            base->insert(base->size(),item); //append to end 
        }
        catch(ListException e)
        {
            throw QueueException(e.what());
        }
    }
    
    //
    template<typename T, class C>
    void Queue<T,C>::dequeue()
    {
        try{
            base->remove(0); //remove front item
        }
        catch(ListException e)
        {
            throw QueueException(e.what());
        }
    }
    
    template<typename T, class C>
    void Queue<T,C>::front(T& item) const throw(QueueException)
    {
        try{
            base->retrieve(0,item);
        }
        catch(ListException e)
        {
            throw QueueException(e.what());
        }
    }
    
    //proceed the copy only if not circular, and with matching list imple'
    template<typename T, class C>
    Queue<T,C>& Queue<T,C>::operator =(const Queue<T,C>& q) throw(QueueException)
    {
        if(this==&q)
            throw QueueException("circular copy detected");
     
        //make sure we copy from the same ADT List implementation
        C* tmp = dynamic_cast<C*>(q.base);  
        if(!tmp)
            throw QueueException("unmatched ADT list implementation");
    
        if(base){
            delete base;
            base = NULL;
        }
        
        base = new C(*tmp);
        
        return *this;
    }
    
    template<typename T, class C>
    Queue<T,C>::Queue(const Queue<T,C>& q) throw(QueueException)
    {
        base = NULL;
        *this = q;  
    }
    
    template<typename T, class C>
    Queue<T,C>::Queue()
    {
        base = new C();
    }
    
    template<typename T, class C>
    Queue<T,C>::~Queue()
    {
        if(base){
            delete base;
            base = NULL;
        }
    }
}
#endif
