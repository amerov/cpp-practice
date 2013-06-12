//
//  lqueue.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-11.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_lqueue_hpp
#define cpp_practice_lqueue_hpp

#include <iostream>

namespace dennycd {
    /**
      pointer based queue using an external tail pointer with acyclic links
      element are enqueue at tail, and dequeue at front
     **/
    template<typename E>
    class LQueue{
        
    public:

        void enqueue(const E& item){
            if(!_tail){
                _tail = new LNode(item);
                _tail->next = _tail;
            }
            else{
                _tail->next = new LNode(item, _tail->next);
                _tail = _tail->next;
            }
            
            
        }
        
        E& front(){
            if(!_tail) throw std::exception();
            return _tail->next->data;
        }
        
        
        
        E dequeue(){
            if(!_tail) throw std::exception(); //none
            LNode* del = _tail->next;
            _tail->next = del->next;
            if(del == _tail) _tail = NULL; //down to 0
            E ret = del->data;
            delete del;
            return ret;
        }
        
        
        bool empty() const { return _tail==NULL;}
        int size() const{
            int count = 0;
            if(!_tail) return count;
            LNode* cur = _tail;
            do{
                count++;
                cur = cur->next;
            }while(cur!=_tail);
            return count;
        }
        
        template<typename EE>
        friend std::ostream& operator<<(std::ostream& oss, const LQueue<EE>& q);
        
        
        LQueue() : _tail(NULL) {}
        virtual ~LQueue() { _reset(); }
        
    protected:
        
        void _reset(){
            if(!_tail) return; //0 
            while(_tail->next != _tail){  //down to last
                LNode* del = _tail->next;
                _tail->next = del->next;
                delete del;
            }
            delete _tail;  //0
            _tail = NULL;
        }
        
        struct LNode{
            E data;
            LNode* next;
            LNode(const E& d, LNode*n=NULL) : data(d), next(n){}
        };        
        LNode* _tail;
    };
    
    template<typename EE>
    std::ostream& operator<<(std::ostream& oss, const LQueue<EE>& q)
    {
        oss << "{";
        auto cur = q._tail;
        if(cur){
            do{
                cur = cur->next;
                oss << cur->data;
                if(cur!=q._tail) oss << ",";
            }while(cur!=q._tail);
        }
        oss << "}";
        return oss;
    }
}


#endif
