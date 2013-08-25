//
//  AList.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-18.
//  -
//
#ifndef ASTEMSOFT_ARRAY_LIST_HPP
#define ASTEMSOFT_ARRAY_LIST_HPP

#include "List.hpp"
//#include <stddef.h> //for NULL
#include <iostream>
#include <fstream> //for istream
//
// array based ADT List Implementation 
//
namespace astemsoft
{

    /**
     An Array-Based ADT List Implementation 
     **/
    template<typename T>
    class AList : public List<T>
    {
    public:
        static const int DEFAULT_NUMBERS = 2;//default size of the array
    public:
        AList();
        AList(const AList& list); //copy constructor
        AList& operator =(const AList& list); //assignment operator;
        virtual ~AList();
    public:
        void clear();
        int size() const{ return count;}
        bool empty() const{ return count==0;}
        void insert(int index, const T& item) throw(ListException);
        void remove(int index) throw(ListException);
        void retrieve(int index, T& item) const;
        void print() const;

        //void save(const std::string& filename) const throw(ListException); 
        //void restore(const std::string& filename) throw(ListException);
        
        
    private:
        void expand() throw(ListException); //enlarge the array by doubling the size
        T* base; //the base pointer to the array content
        int count; //the number of items in array
        int max_count; //the size of the current array
        
        //===========================
        // Interator Class Definition
        //===========================
    public:
        class iterator
        {
        public:
            iterator() : cur(-1), container(NULL) {}
            iterator(const AList* list, int idx) : cur(idx), container(list) {}
            ~iterator(){}
            
            //copy constructor
            iterator(const iterator& it)
            {
                *this = it;
            }
            
            
            //assignment copy operator
            iterator& operator =(const iterator& it)
            {
                if(this != &it)
                {
                    container = it.container;
                    cur = it.cur;
                }
                return *this;
            }
            
            //access a copy value
            //note that here we ALLOW modification on returned element
            T& operator*() throw(ListException)
            {
                if(!container || cur==-1)
                    throw ListException("uninitialized iterator");
                
                return container->base[cur];
            }
            
            iterator& operator++() throw(ListException)
            {
                if(cur==-1 || !container)
                    throw ListException("uninitialized iterator");
                
                //no effect if already at end of list
                if(cur < container->count)
                    cur++;
                return *this;
            }
            
            iterator& operator--() throw(ListException)
            {
                if(cur==-1 || !container)
                    throw ListException("uninitialized iterator");
                
                //no effect if cur already reaches 0
                if(cur > 0)  
                    cur--;
                return *this;
            }
            
            //comparison operator
            bool operator==(const iterator& rhs) const
            {
                if(cur == -1 || rhs.cur == -1 ||
                   !container || !(rhs.container)) //consider false if any one is -1
                    return false;
                else 
                if(container==rhs.container && cur == rhs.cur)
                    return true;
                else 
                    return false;
            }
            
            bool operator!=(const iterator& rhs) const
            {
                return !( this->operator==(rhs) ); 
            }
            
            
            //distance operator
            //give the Euclidean distance between two iterator
            int operator -(const iterator& rhs) const throw(ListException)
            {
                if(cur<0 || rhs.cur<0 || !container || !(rhs.container))
                    throw ListException("uninitialized iterator");
                return cur - rhs.cur; 
            }
            
            //offset from current iterator
            iterator operator +(int offset) const
            {
                if(cur<0 || !container )
                    throw ListException("uninitialized iterator");
                return iterator(container, cur + offset);
            }
            
            //offset from current iterator
            iterator operator -(int offset) const
            {
                return this->operator +(-offset);
            }
            
            /*
            //insert current node before rhs 
            iterator& operator >>(const iterator& rhs)
            {
                
                
            }
            
            //insert rhs right after current node 
            iterator& operator <<(const iterator& rhs)
            {
                
                
            }
            */
            
            /*
            //ordering comparison
            //return true if self points to smaller index than rhs
            bool operator <(const iterator& rhs) const throw(ListException)
            {
                if(cur<0 || rhs.cur<0 || !container || !(rhs.container))
                    throw ListException("uninitialized iterator");
                return (cur < rhs.cur);
            }
            
            bool operator >(const iterator& rhs) const throw(ListException)
            {
                if(cur<0 || rhs.cur<0 || !container || !(rhs.container))
                    throw ListException("uninitialized iterator");
                return (cur > rhs.cur);
            }
            
            bool operator <=(const iterator& rhs) const throw(ListException)
            {
                return (this->operator<(rhs)) || (this->operator==(rhs));
            }
             */
            
        private:
            const AList* container; //access to the container
            int cur; //index pointer
        };
        //friend class iterator; //allow iterator to access alist
        
        //first item iterator
        iterator begin() const
        {
            return iterator(this,0);
        }
        
        //end iterator 
        iterator end() const
        {
            return iterator(this,count); 
        }
        
        //last item iterator
        iterator last() const
        {
            return iterator(this,count-1);
        }
        
    };
    
    
    //
    //save array content to disk 
    //with format  [DATA] \n [DATA] \n ...
    //
    /*
    template<typename T>
    void AList<T>::save(const std::string& filename) const throw(ListException)
    {
        using namespace std;
        ofstream ofs;
        ofs.open(filename.c_str());
        
        if(ofs.fail())
            throw ListException("failed to open file for save");
     
        for(int i=0;i<count;i++)
        {
            ofs << base[i] << endl;
        }
        ofs.close();
    }
    
    template<typename T>
    void AList<T>::restore(const std::string& filename) throw(ListException)
    {
        using namespace std;
        T item;
        ifstream ifs;
        ifs.open(filename.c_str());
        
        if(ifs.fail())
            throw ListException("failed to open file for restore");
        
        clear(); //reset to default storage 
        
        //read in each item and insert into end of list 
        while(ifs >> item)
            insert(size(), item);
        
        ifs.close();
    }
    */
    
    //display content
    //@assume T adopts ostream << operator
    template<typename T>
    void AList<T>::print() const
    {
        std::cout << "max size = " << max_count << std::endl;
        std::cout << "total items = " << count << std::endl;
        for(int i=0;i<count;i++)
            std::cout << base[i] << "\t" << std::endl;
        
    }
    
    
    //
    // exponentially expanding the array size 2^n
    // check for memeory exhaustion
    template<typename T>
    void AList<T>::expand() throw(ListException)
    {
        T* newbase = new T[2*max_count];
        if(!newbase)
            throw ListException("expand run out of memory");
        
        //copy over
        for(int i=0;i<count;i++)
            newbase[i] = base[i];
        
        delete[] base;
        base = newbase;
        max_count = 2 * max_count;
    }
    
    //
    //insert item into the list 
    //@assume T adopts = assignment operator
    template<typename T>
    void AList<T>::insert(int index, const T& item) throw(ListException)
    {
        if(index < 0 || index > count) //can insert between beginning and end 
            throw ListException("insert index out of bound");
        
        //if array reach max size, expand array
        if( count + 1 > max_count)
            expand();

        //first move [index] ~ [count-1] rightwards
        for(int i=count-1;i>=index;i--)
            base[i+1] = base[i];
        
        base[index] = item;//then move item into [index]
        count++;

    }
    
    
    //
    //remove item from list 
    //@assume T adopts = assignment operator
    template<typename T>
    void AList<T>::remove(int index) throw(ListException)
    {
        if(index < 0 || index >= count)
            throw ListException("remove index out of bound");
        
        //move [index+1] ~ [count-1] leftwards
        for(int i=index;i<count-1;i++)
            base[i] = base[i+1];
        count--;
    }
    
    
    //retrieve item from list 
    //@assume T adapts = assignment operator
    template<typename T>
    void AList<T>::retrieve(int index, T& item) const
    {
        if(index < 0 || index >= count)
            throw ListException("insert index out of bound");
        
        item = base[index];
    }
    
    
    //clear up the array
    template<typename T>
    void AList<T>::clear()
    {
        //destroy existing content 
        if(base){
            delete[] base;
            base = NULL;
        }
        
        //reset to default array size and empty content
        base = new T[DEFAULT_NUMBERS];
        max_count = DEFAULT_NUMBERS;
        count = 0;
        
    }
    
   
    //
    //copy constructor 
    template<typename T>
    AList<T>::AList(const AList& list) : base(NULL), count(0), max_count(DEFAULT_NUMBERS)
    {
        *this = list;
    }
    
    //
    //assignment operator 
    //
    template<typename T>
    AList<T>& AList<T>::operator =(const AList& list)
    {
        if(this != &list)
        {
            //first free up existing content
            if(base){
                delete[] base;
                base = NULL;
            }
            
            base = new T[list.max_count];
            max_count = list.max_count;
            
            for(int i=0;i<list.count;i++)
                base[i] = list.base[i];
            
            count = list.count;
        }
        return *this;
    }

    
    //initialize with default array size and empty content
    //abey rules for RAII
    template<typename T>
    AList<T>::AList()
    {
        base = new T[DEFAULT_NUMBERS];
        max_count = DEFAULT_NUMBERS;
        count = 0;
    }
    
    //on destroy, release all memory
    template<typename T>
    AList<T>::~AList()
    {
        if(base){
            delete[] base;
            base = NULL;
        }
    }
    
    
    
}
#endif