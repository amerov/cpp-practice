//
//  lstack.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-11.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_lstack_hpp
#define cpp_practice_lstack_hpp

namespace dennycd {
    
    /**
      Link-list based stack implementation
     **/
    template<typename E>
    class LStack{
      
    public:
        
        //O(1)
        E& top(){
            if(!_top) throw std::exception();
            return _top->data;
        }
        
        //O(1)
        void push(const E& item){
            _top = new LNode(item, _top);
        }
        
        //O(1)
        E pop(){
            if(!_top) throw std::exception();
            E ret = _top->data;
            LNode* del = _top;
            _top = _top->next;
            delete del;
            return ret;
        }
        
        LStack() : _top(NULL){}
        virtual ~LStack(){
            _reset();
        }
        
        int size() const{
            int count = 0;
            LNode* cur = _top;
            while(cur)
            {
                cur = cur->next;
                count++;
            }
            return count;
        }
        
        bool empty() const{ return _top==NULL;}

        template<typename EE> friend std::ostream& operator<<(std::ostream& oss, const LStack<EE>& st);
        
    protected:
      
        //O(n) 
        void _reset(){
            LNode* cur = NULL;
            while (_top) {
                cur = _top;
                _top = _top->next;
                delete cur;
            }
        }
        
        //node
        struct LNode{
            E data;
            LNode* next;
            LNode() : next(NULL){}
            LNode(const E& d, LNode* n = NULL) : data(d), next(n){}
        };
        
        LNode* _top;
    };

    template<typename EE>
    std::ostream& operator<<(std::ostream& oss, const LStack<EE>& st){
        oss << "{";
        auto cur = st._top;
        while(cur)
        {
            oss << cur->data;
            if(cur->next) oss << ",";
            cur = cur->next;
        }
        oss << "}";
        return oss;
    }
}

#endif
