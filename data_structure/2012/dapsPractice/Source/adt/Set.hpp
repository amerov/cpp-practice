//
//  Set.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-23.
//  -
//
#ifndef ASTEMSOFT_ADT_SET_HPP
#define ASTEMSOFT_ADT_SET_HPP


#include <exception>
#include <string>
namespace astemsoft
{
    namespace adt
    {
        //default "<" function object for value-based comparison
        template<typename T>
        struct less_than
        {
            bool operator()(const T& x, const T& y) const
            {
                return (x < y);
            }
        };
        
        class SetException : public std::exception
        {
        public:
            SetException(const std::string& msg = "") : message(msg){}
            ~SetException() throw(){}
            const char* what() const throw()
            {
                return ("AstemSoft ADT Set Exception: " + message).c_str();
            }
        private:
            std::string message;
        };
        
        /**
         Generic Interface For Value-Based Collection ADT
         
         T - value-based item type
         K - item key type
         **/
        template<typename T>
        class Set{
        public:
            Set(){}
            virtual ~Set(){}
            
            virtual void clear() = 0; //reset Set content
            virtual bool empty() const = 0; //check for emptyness (no nodes)
            virtual int size() const = 0; //total number of nodes 
            
        public:
            virtual T& operator [](int index) const throw(SetException){ throw SetException("implementation not supported");}    
            
            template<typename K>
            void insert(const T& item) throw(SetException){ throw SetException("implementation not supported");}
            
            template<typename K> 
             void remove(const K& key) throw(SetException){ throw SetException("implementation not supported"); }
            
            template<typename K> 
             void retrieve(const K& key, T& item) const throw(SetException){ throw SetException("implementation not supported"); }
            
            template<typename FUNC>
             void traverse(FUNC& func) throw(SetException) { throw SetException("implementation not supported"); }  //traversal through all set elements
            
            template<typename FUNC>
             void traverse(FUNC& func) const throw(SetException) { throw SetException("implementation not supported"); }  //traversal through all set elements
            
            template<typename FUNC, typename KEY>
             void update( FUNC& func, const KEY& key) throw(SetException){throw SetException("implementation not supported");} //perform  update on a single item in the set
            
            template<typename KEY>
             bool exist(const KEY& key) throw(SetException){throw SetException("implementation not supported");} //perform  update on a single item in the set
            
        public:
            virtual void save(const std::string& filename) const throw(SetException){ throw SetException("implementation not supported"); }
            virtual void restore(const std::string& filename) throw(SetException){ throw SetException("implementation not supported"); }
            virtual void print() const{ throw SetException("implementation not supported"); } //print to std output
        };
        
    }
}
#endif