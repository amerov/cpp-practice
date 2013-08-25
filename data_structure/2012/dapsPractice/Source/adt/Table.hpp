//
//  Table.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-29.
//
#ifndef ASTEMSOFT_ADT_TABLE_HPP
#define ASTEMSOFT_ADT_TABLE_HPP

#include <exception>
#include <string>
#include <iostream>
#include "Set.hpp"

namespace astemsoft
{
    namespace adt
    {
       
        //ADT Table Exception
        class TableException : public std::exception
        {
        public:
            TableException(const std::string& msg = "") : message(msg){}
            ~TableException() throw(){}
            const char* what() const throw()
            {
                return ("[AstemSoft ADT Table Exception] " + message).c_str();
            }
        private:
            std::string message;
        };
        
        /**
         Generic ADT Table Interface
         
         CONTAINER - the storage implementation for the Table
         ITEM - the record data type
         KEY - primary search key type : primary search key is UNIQUE in table 
         **/
        template<typename CONTAINER, typename ITEM, typename KEY>
        class Table
        {
        public:
            Table() throw(TableException);
            Table(const Table& t) throw(TableException);
            Table& operator =(const Table& t) throw(TableException);
            virtual ~Table();
            
            virtual bool empty() const{ return base->empty();}
            virtual int size() const{return base->size();}
            virtual void clear(){ base->clear();}
            
            virtual void insert(const ITEM& item) throw(TableException);
            virtual void remove(const KEY& key) throw(TableException);
            virtual void retrieve(const KEY& key, ITEM& item) const throw(TableException);
            
            template<typename FUNC>  void update(FUNC& func, const KEY& key) throw(TableException);
            template<typename FUNC>  void traverse(FUNC& func) throw(TableException);
            
        public:
            //virtual void save(const std::string& filename) const throw(TableException);
            //virtual void restore(const std::string& filename) throw(TableException);
            virtual void print() const{ return base->print();}
        
        private:
            Set<ITEM>* base; //the set container
        };
        
        template<typename C, typename I, typename K>
        template<typename FUNC> 
        void Table<C,I,K>::update(FUNC& func, const K& key) throw(TableException)
        {
            try{
                ((C*)base)->update(func, key);
            }
            catch(SetException e)
            {
                throw TableException(e.what());
            }
        }
        
        template<typename C, typename I, typename K>
        template<typename FUNC>
        void Table<C,I,K>::traverse(FUNC& func) throw(TableException)
        {
            try{
                ((C*)base)->traverse(func);
            }
            catch(SetException e)
            {
                throw TableException(e.what());
            }
        }
        
        template<typename C, typename ITEM, typename KEY>
        void Table<C,ITEM,KEY>::insert(const ITEM& item) throw(TableException)
        {
            try{
                //The issue of member template name
                //see http://stackoverflow.com/questions/3786360/confusing-template-error
                //for a briefl discussion of this mess
                
                //TODO: somethow the polymorphic functio override does not work here
               // (*base).template insert<KEY>(item);
                ((C*)base)->template insert<KEY>(item);
            }
            catch(SetException e)
            {
                throw TableException(e.what());
            }
        }
        
        
        template<typename C, typename I, typename KEY>
        void Table<C,I,KEY>::remove(const KEY& key) throw(TableException)
        {
            try{
                ((C*)base)->remove(key);
            }
            catch(SetException e)
            {
                throw TableException(e.what());
            }
        }
        
        
        template<typename C, typename ITEM, typename KEY>
        void Table<C,ITEM,KEY>::retrieve(const KEY& key, ITEM& item) const throw(TableException)
        {
            try{
                ((C*)base)->retrieve(key,item);
            }
            catch(SetException e)
            {
                throw TableException(e.what());
            }
        }
        

        ////=====constructor / destructor maintenance
        template<typename C, typename I, typename K>
        Table<C,I,K>::Table() throw(TableException) : base(NULL)
        {
            base = new C();
            if(!base)
                throw TableException("heap memory alloc failed");
        }
        
        template<typename C, typename I, typename K>
        Table<C,I,K>::~Table()
        {
            if(base)
            {
                delete base;
                base = NULL;
            }
        }
        
        template<typename C, typename I, typename K>
        Table<C,I,K>& Table<C,I,K>::operator=(const Table<C,I,K>& t) throw(TableException)
        {
            if(this !=&t)
            {
                try{
                    //TODO - check this to ensure operator override is on C 
                    *((C*)base) = *((C*)(t.base));  
                }
                catch(SetException e)
                {
                    throw TableException(e.what());
                }
            }
            return *this;
        }
        
        template<typename C, typename I, typename K>
        Table<C,I,K>::Table(const Table<C,I,K>& t) throw(TableException) : base(NULL)
        {
            base = new C();
            if(!base)
                throw TableException("heap memory alloc failed");
    
            *this = t;
        }
        
        
    }
}
#endif