//
//  List.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-18.
//  -
//
#ifndef ASTEMSOFT_ADT_LIST_HPP
#define ASTEMSOFT_ADT_LIST_HPP

#include <exception> //for exception class
#include <string>

//
// Interface Definition for Basic ADT List
// contains no data members but pure virtual functions 
//
//
//
namespace astemsoft{
    
    //ADT List exception class
    class ListException : public std::exception
    {
    public:
        ListException(const std::string& msg = "") : message(msg){}
        ~ListException() throw(){}
        const char* what() const throw()
        {
            return ("AstemSoft ADT List Exception: " + message).c_str();
        }
    private:
        std::string message;
    };
    
    //Generic Interface for Random Access Iterator
    //TODO: inheritance on this iterator interface still have issues
    //      that ListIterator class are not automatically considered in
    //      a child class context
    template<typename T>
    class ListIterator
    {
    public:
        ListIterator(){}
        virtual ~ListIterator(){}
        virtual const T& operator*() = 0; // dereferencing operator
        virtual ListIterator& operator=(const ListIterator& rhs) = 0;//assignment operator
        virtual ListIterator& operator++() = 0; //traverse to next item
        virtual ListIterator& operator--() = 0; //traverse to previoys item
        virtual bool operator==(const ListIterator& rhs) const = 0; //equalness 
        virtual bool operator!=(const ListIterator& rhs) const = 0; //difference
    };
    
    
    //interface for Basic ADT List
    template<typename T>
    class List{

    public:
        //create empty list 
        List(){}
        
        //deconstruct the list, release mem resource
        virtual ~List(){}

         //empty the content of the list
        virtual void clear() = 0;
        
        //number of items in the list 
        virtual int size() const = 0; 
        
        //whether the list is empty 
        virtual bool empty() const = 0; 
        
        //insert item at given position in the list 
        virtual void insert(int index, const T& item) throw(ListException) = 0;
        
        //delete item at given position in the list 
        virtual void remove(int index) throw(ListException) = 0;
        
        //look at/retrieve item at a given position in the list 
        virtual void retrieve(int index, T& item) const = 0;
        
        //save list content to destination disk file 
        virtual void save(const std::string& filename) const throw(ListException){}
        
        //reload list content from source disk file 
        virtual void restore(const std::string& filename) throw(ListException){}
        
        //print content of list
        virtual void print() const{}
        
    };
}
#endif