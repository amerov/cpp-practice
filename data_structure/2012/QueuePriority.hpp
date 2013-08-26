//
//  QueuePriority.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-30.
//  -
//
#ifndef ASTEMSOFT_ADT_PRIORITY_QUEUE_HPP
#define ASTEMSOFT_ADT_PRIORITY_QUEUE_HPP

#include "Queue.hpp"
#include "Heap.hpp"

namespace astemsoft 
{
    namespace adt
    {

        /**
         Priority Queue  , always dequeue item having highest priority
         Here we simply use heap as de fa'co storage
         **/
        template<typename T>
        class QueuePriority
        {
        public:
            void enqueue(const T& item) throw(QueueException);
            void dequeue();
            void front(T& item) const throw(QueueException); 
            
            bool empty() const{return base.empty();}
            int size() const{return base.size();}
            void print() const{ base.print();}
            
        public:
            QueuePriority(){}
            QueuePriority(const QueuePriority& q){ *this = q;}
            QueuePriority& operator =(const QueuePriority& q); 
            virtual ~QueuePriority(){}

        private:
            Heap<T> base;
        };



        //append item to end of queue
        template<typename T>
        void QueuePriority<T>::enqueue(const T& item) throw(QueueException)
        {
            try{
                base.insert(item);
            }
            catch(HeapException e)
            {
                throw QueueException(e.what());
            }
        }
        
        //
        template<typename T>
        void QueuePriority<T>::dequeue()
        {
            try{
                T item;
                base.remove(item);
            }
            catch(HeapException e)
            {
                throw QueueException(e.what());
            }
        }
        
        template<typename T>
        void QueuePriority<T>::front(T& item) const throw(QueueException)
        {
            try{
                base.top(item);
            }
            catch(HeapException e)
            {
                throw QueueException(e.what());
            }
        }
        
        //proceed the copy only if not circular, and with matching list imple'
        template<typename T>
        QueuePriority<T>& QueuePriority<T>::operator =(const QueuePriority<T>& q)
        {
            if(this!=&q)
                base = q.base;
            return *this;
        }








































}
}
#endif
