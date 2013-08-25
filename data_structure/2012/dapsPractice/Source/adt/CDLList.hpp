//
//  CDLList.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-19.
//  -
//
#ifndef ASTEMSOFT_ADT_CIRCULAR_DOUBLE_LINK_LIST_CPP
#define ASTEMSOFT_ADT_CIRCULAR_DOUBLE_LINK_LIST_CPP

#include "List.hpp"
#include <stddef.h> //for NULL
#include <iostream> //for cout
#include <fstream> //for istream

namespace astemsoft 
{

    /**
     Circular Double Linked List 
     
     a dummy head node is used to eliminate head cases
     each node has both pre and next pointers
     last node and dummy head node link to each other, forming a circle
     **/
    template<typename T>
    class CDLList : public List<T>
    {  
    private:
        struct LNode
        {
            T item;
            LNode *pre;
            LNode *next;
        };
         
    public:
        CDLList();
        CDLList(const CDLList& list);
        virtual ~CDLList();
        CDLList& operator =(const CDLList& list) throw(ListException);

        void insert(int index, const T& item) throw(ListException);
        void remove(int index) throw(ListException);
        void retrieve(int index, T& item) const throw(ListException);
        void print() const;
        bool empty() const{return count==0;}
        int size() const{return count;}
        void save(const std::string& filename) const throw(ListException); 
        void restore(const std::string& filename) throw(ListException);
        void clear();
        
    private:
        //locate the ith node in list
        //if index==count, return head node
        LNode* find(int index) const
        {
            if(index < 0 || index > count)
                return NULL;
            
            LNode* cur = head;
            for(int i=0;i<=index;i++)
                cur = cur->next;
            
            return cur;
        }

    private:
        int count; 
        LNode *head;
        
    public:
        //local implemention of iterator class
        class iterator // : public ListIterator<T>
        {
        public:
            iterator() : cur(NULL),container(NULL) {}
            iterator(LNode* node, const CDLList* list) : cur(node),container(list){}
            ~iterator(){}
            
            iterator(const iterator& it)
            {
                *this = it;
            }
            
            //assignment copy operator
            iterator& operator =(const iterator& it)
            {
                if(this != &it)
                {
                    cur = it.cur;
                    container = it.container;
                }
                return *this;
            }
            
            //constant deferencing operator
            //provide a non-constant return type to allow modifing cur->item
            T& operator*() throw(ListException)
            {
                if(cur)
                    return cur->item;
                else 
                    throw ListException("dereferencing on uninitialized iterator");
            }
            
            //increment operator
            iterator& operator++()
            {
                cur = cur->next;
                return *this;
            }
            
            //decrement operator
            iterator& operator--()
            {
                cur = cur->pre;
                return *this;
            }
            
            //equalness operator
            bool operator==(const iterator& rhs) const
            {
                if(!cur || !rhs.cur) //consider false if any one is NULL
                    return false;
                else   
                    return (cur == rhs.cur);
            }
            
            bool operator!=(const iterator& rhs) const
            {
                return !( this->operator==(rhs) ); 
            }
            
            //offset from current iterator
            iterator operator +(int offset) const
            {
                LNode *newcur = cur;
                
                if(offset >= 0){
                    for(int i=0;i<offset;i++)
                        newcur = newcur->next;
                }
                else
                {
                    for(int i=0;i>offset;i--)
                        newcur = newcur->pre;
                }
                
                return iterator(newcur,container);
            }
            
            //offset from current iterator
            iterator operator -(int offset) const
            {
                return this->operator+(-offset);
            }
            
            //distance operator
            //give the Euclidean distance between two iterator
            //In a link-list implementation ,this operation has O(n) time complexity
            int operator -(const iterator& rhs) const throw(ListException)
            {
                if(!cur || !rhs.cur || !container || !(rhs.container) ||
                   (container!=rhs.container))
                    throw ListException("uninitialized iterator");
            
                
                //find index for each 
                int curIdx = 0;
                for(LNode* tmp = cur; tmp->pre!= container->head; tmp = tmp->pre)
                    curIdx++;
                
                int rhsIdx = 0;
                for(LNode* tmp = rhs.cur; tmp->pre!=rhs.container->head; tmp = tmp->pre)
                    rhsIdx++;

                return curIdx - rhsIdx;
            }
            
        
        private:
            const CDLList* container;
            LNode* cur; 
        };//iterator class

    public:
        //return first item
        iterator begin() const
        {
            return iterator(head->next, this);
        }
        
        //head node indicates end 
        iterator end() const
        {
            return iterator(head,this);
        }
        
        iterator last() const
        {
            return iterator(head->pre, this);
        }
    };

    
    //restore list from disk file with format [DATA] \n [DATA] \n ...
    //
    template<typename T>
    void CDLList<T>::restore(const std::string& filename) throw(ListException)
    {
        using namespace std;
        ifstream ifs;
        ifs.open(filename.c_str());
        
        if(ifs.fail())
            throw ListException();
        
        clear(); 
        
        //iteratively add next disk item to end of list
        T item;
        while(ifs >> item)
            insert(size(),item);
    }
    
    /**
     save link list to disk file format [DATA] \n [DATA] \n ...
     **/
    template<typename T>
    void CDLList<T>::save(const std::string& filename) const throw(ListException)
    {
        using namespace std;
        ofstream ofs;
        ofs.open(filename.c_str());
        
        if(ofs.fail())
            throw ListException("failed to open file for save");
        
        for(LNode* cur=head->next; cur!=head; cur=cur->next)
        {
            ofs << cur->item << endl;
        }
        
        ofs.close();
    }
    
    //@assume T implements ostream << operator
    template<typename T>
    void CDLList<T>::print() const
    {
        std::cout << "total size = " << count << std::endl;
        LNode* cur = head->next;
        while(cur!=head)
        {
            std::cout << cur->item << std::endl;
            cur = cur->next;
        }
        std::cout << std::endl;
    }

    template<typename T>
    void CDLList<T>::retrieve(int index, T& item) const throw(ListException)
    {
        LNode* cur = find(index);
        if(cur == NULL || cur == head)
            throw ListException("index out of bound");
        
        item = cur->item;
    }
    
    template<typename T>
    void CDLList<T>::remove(int index) throw(ListException)
    {
        LNode* cur = find(index);
        if(cur==NULL || cur==head)
            throw ListException("index out of bound");
        
        //update neighbors
        cur->pre->next = cur->next;
        cur->next->pre = cur->pre;
        
        //remove node
        cur->pre = cur->next = NULL;
        delete cur; 
        cur = NULL;
        
        count--;
    }
    
    template<typename T>
    void CDLList<T>::insert(int index, const T& item) throw(ListException)
    {
        //consider case to insert at the end, which index == count 
        LNode* cur = find(index);
        if(cur==NULL)
            throw ListException("index out of bound");
        
        //insert node in front of cur
        LNode* tmp = new LNode;
        tmp->item = item;
        tmp->pre = cur->pre;
        tmp->next = cur;
        
        //update neighbors
        cur->pre->next = tmp;
        cur->pre = tmp;
        
        count++;
    }
    
    // empty the list
    // pre: the head node exist
    template<typename T>
    void CDLList<T>::clear() 
    {
        LNode* cur = head->next;
        
        while(cur!=head)
        {
            head->next = cur->next;
            cur->next->pre = head;
            
            delete cur;
            cur = head->next;
        };
        
        count = 0;
    }

    //default constructor
    template<typename T>
    CDLList<T>::CDLList()
    {
        head = new LNode; //dummy head
        head->pre = head->next = head;
        count = 0;
    }
    
    //copy constructor
    template<typename T>
    CDLList<T>::CDLList(const CDLList& list)  
    {
        head = new LNode; 
        head->pre = head->next = head;
        count = 0;

        //ignore circular copy exception here
        try{
            *this = list;
        }
        catch(ListException e){} 
    }

    
    // copy list
    // pre: head node must already exist
    template<typename T>
    CDLList<T>& CDLList<T>::operator =(const CDLList<T>& list)  throw(ListException)
    {
        if(this != &list)
        {
            clear();
            
            //iteratively add item to the end of myself
            LNode *cp = list.head->next;
            while(cp != list.head)
            {
                insert(size(),cp->item);
                cp = cp->next;
            }
        }
        else
            throw ListException("circular copy detected");

        return *this;
    }

    template<typename T>
    CDLList<T>::~CDLList()
    {
        clear();
        
        if(head){
            delete head;
            head = NULL;
        }
    }



}
#endif