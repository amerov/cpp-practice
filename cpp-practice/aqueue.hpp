//
//  aqueue.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-12.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_aqueue_hpp
#define cpp_practice_aqueue_hpp

#include <iostream>

namespace dennycd {
    
    const int AQUEUE_MAX_SIZE = 5;
    
    #define decre_mod(x,mod) (((x-1) >= 0) ? (x-1) : (mod-1))
    #define incre_mod(x,mod) ( (x+1)%mod )
    
    /**
      Circular array-based implementation of Queue
     
      enqueue at end, dequeue at front 
     using an additional flag to indicat emptiness 
     **/
    template<typename T>
    class AQueue{
    public:
        AQueue() : _front(0),_end(0), _empty(true){}
        ~AQueue(){}
        
        // O(1)
        void enqueue(const T& item){
            if(full()) throw std::exception();
            if(_empty){
                _empty = false;
                _base[_end] = item;
            }
            else{
                _end = incre_mod(_end, AQUEUE_MAX_SIZE);
                _base[_end] = item;
            }
        }
        
        // O(1)
        T& front(){
            if(_empty) throw std::exception();
            return _base[_front];
        }
        
        //O(1)
        T dequeue(){
            if(_empty) throw std::exception();
            T ret = _base[_front];
            bool last = _front==_end;
            _front = incre_mod(_front, AQUEUE_MAX_SIZE);
            if(last) _reset();
            return ret;
        }
        
        
        bool empty() const{ return _empty;}
        bool full() const{
            return !_empty && (incre_mod(_end,AQUEUE_MAX_SIZE) == _front);
        }
        
        //O(1)
        int size() const{
            if(_empty) return 0;
            else if(_front  <= _end) return (_end-_front+1);
            else return AQUEUE_MAX_SIZE - _front + _end + 1;
        }
        
        void _reset(){
            _front = 0;
            _end = 0;
            _empty = true;
        }
        
        template<typename TT>
        friend std::ostream& operator<<(std::ostream& oss, const AQueue<TT>& q);
        
    private:
        T _base[AQUEUE_MAX_SIZE];
        int _front;
        int _end;
        bool _empty;
    };
    
    template<typename TT>
    std::ostream& operator<<(std::ostream& oss, const AQueue<TT>& q){
        oss << "{";
        if(!q.empty()){
            int cur = q._front;
            while(cur!=q._end){
                oss << q._base[cur];
                cur = incre_mod(cur, AQUEUE_MAX_SIZE);
                oss << ",";
            };
            oss << cur;
        }
        oss << "}";
        return oss;
    }
    
}

#endif
