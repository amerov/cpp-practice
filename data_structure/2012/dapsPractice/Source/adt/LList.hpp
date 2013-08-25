//
//  LList.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-15.
//  -
//
// Linked List Definition File 
#ifndef ASTEMSOFT_LINKED_LIST_HPP
#define ASTEMSOFT_LINKED_LIST_HPP

#include "List.hpp"
#include <stddef.h> //for NULL
#include <iostream> //for cout
#include <fstream> //for istream

//#include <cassert> //for asssert()
//#include <stdexcept> //for out_of_range exception

namespace astemsoft
{

    // Pointer Based Link List Class Implementation
    // should make a circular doubly linked list !!
    template<typename T>
    class LList : public List<T>
    {
    private:
        //generic link list node type 
        struct LNode
        {
            T item;
            LNode *next;
        };
        
        
    public:
        LList();
        LList(const LList& aList);
        virtual ~LList(){clear();}
        LList& operator =(const LList& aList);  //assignment operator
        
        void insert(int index, const T& newItem) throw(ListException);
        void remove(int index) throw(ListException); 
        void retrieve(int index, T& dataItem) const throw(ListException); 
        void print() const; 
        void clear(); 
        bool empty() const{return count==0;}
        int size() const{return count;}

        void save(const std::string& filename) const throw(ListException); //save link list to file
        void restore(const std::string& filename) throw(ListException); //load link list from file
        
        
        //Ordered Link List Operations
    public:
        void insertAscendRecursive(const T& newItem); //recursive version of ascending insertion sort
        void insertAscend(const T& item);//add item to the list following sorted order
        void removeWithKey(const T& key);//remove a LNode that equals to the given key value
    private:
        //recursive traversal print
        void print_recursive(const LNode*  ptr) const; //recursively print the link list
        void print_recursive_reverse(const LNode* ptr) const;//recursively print the list in reverse order 
        void insert_recursive_ascend(LNode*& ptr, const T& item);//recursive insertion func
        
        //
        //locate the ith node in the list
        // return null, if index < 0 or > length-1
        //
        LNode* find(int index) const
        {
            if(index < 0 || index > count -1)
                return NULL;
            
            LNode* cur = head;
            int pos = 0;
            while(cur)
            {
                if(index==pos)
                    return cur;
                cur = cur->next;
                pos++;
            }
            
            return NULL;
        }
        

    private:
        int count; //number of items in list
        LNode *head;  //header of the link list 
        
    };
    
    
    
    //
    //recursive ascending insert
    //
    template<typename T>
    void LList<T>::insertAscendRecursive(const T& newItem)
    {
        insert_recursive_ascend(head, newItem);
    }
    
    
    //
    // insert item to the asending sorted list pointed by ptr
    // @assume item implements  >  larger than opeator
    //
    template<typename T>
    void LList<T>::insert_recursive_ascend(LNode*& ptr, const T& item)
    {
        //either empty list, insert directly
        //or insert before the encountered larger item
        if(ptr==NULL || ptr->item > item)
        {
            LNode *p = new LNode;
            p->item = item;
            p->next = ptr;
            ptr = p;
            count++;
            
        }
        else                //less or equal case, continue down the list
            insert_recursive_ascend(ptr->next, item); 
    }
    
    
    /**
     Traverse through the list 
     and print them to standard output
     **/
    template<typename T>
    void LList<T>::print() const
    {
        using namespace std;
        LNode *cur = head;
        while  (cur!=NULL)
        {
            cout << cur->item << ",";
            cur = cur->next;
        }
        cout << endl;
    }
    
    
    template<typename T> 
    void LList<T>::print_recursive(const LNode* ptr) const
    {
        if(ptr)
        {
            std::cout << ptr->item << ",";
            print_recursive(ptr->next);
        }    
    }
    
    template<typename T> 
    void LList<T>::print_recursive_reverse(const LNode* ptr) const
    {
        if(ptr)
        {
            print_recursive_reverse(ptr->next);
            std::cout << "," << ptr->item ;
        }
    }
    
    
    //
    // save link list content to disk file in format [DATA] \n [DATA] \n ..
    // existing file will be emptize and overriden
    // @assume T implements/accpets  ofstream <<  streaming operator 
    //
    template<typename T> 
    void LList<T>::save(const std::string& filename) const throw(ListException)
    {
        using namespace std;
        ofstream ofs;
        ofs.open(filename.c_str());
        
        if(ofs.fail())
            throw ListException("failed to open file for save");
        
        for(LNode *cur = head; cur!=NULL; cur=cur->next)
        {
            ofs << cur->item << endl;
        }
        
        ofs.close();
    }
    
    //
    // construct list from disk file 
    // disk file in format [DATA] \n [DATA] \n ..
    //
    // @assume T implements ifstream >> streaming operator 
    //
    template<typename T> 
    void LList<T>::restore(const std::string& filename) throw(ListException)
    {
        using namespace std;
        T item;
        ifstream ifs;
        ifs.open(filename.c_str());
        
        if(ifs.fail())
            throw ListException("failed to open file for load");
        
        //clear up existing list
        clear();
        
        while(ifs >> item)
        {
            LNode *p = new LNode;
            p->item = item;
            p->next = NULL;
            
            if(!head)
                head = p;
            
            count++; //increment size count
        }
        
        ifs.close();
    }
    
    
    template<typename T> 
    void LList<T>::insert(int index, const T& newItem) throw(ListException)
    {
        //out of bound
        if(index < 0 || index > count)   //allow append to end
            throw ListException("insert index out of range");
        
        //insert at begin case
        if(index==0)
        {
            LNode* p = new LNode;
            p->item = newItem;
            p->next = head;
            head = p;
        }
        //intermediate or end case
        else
        {
            //locate previoys node
            LNode* pre = find(index-1);
            
            //move in the new node
            LNode* p = new LNode;
            p->item = newItem;
            p->next = pre->next;
            pre->next = p;
        }
        
        count++;
    }
    
    //
    //remove item via index
    //
    template<typename T> 
    void LList<T>::remove(int index) throw(ListException)
    {
        //out of bound
        if(index < 0 || index > count -1 )
            throw ListException("remove index out of range");
        
        //remove first node
        if(index==0)
        {
            LNode *p = head;
            head = head->next;
            p->next = NULL;
            delete p; p = NULL;
        }
        //remove intermediate or last node
        else
        {
            LNode* pre = find(index-1);
            LNode* cur = pre->next;
            pre->next = cur->next;
            
            cur->next = NULL;
            delete cur; cur = NULL;
        }
        
        count--;
    }
    
    
    //
    //retrieve item via index
    //
    template<typename T> 
    void LList<T>::retrieve(int index, T& dataItem) const throw(ListException)
    {
        LNode* cur = find(index);
        if(cur==NULL)
            throw ListException("retrieve index out of range");
        else 
            dataItem = cur->item;
    }
    
    //
    // copy constructor
    // a deep copy of all list nodes
    // @assume T supports = copy operator
    // 
    template<typename T>
    LList<T>::LList(const LList<T>& aList) : count(0), head(NULL)
    {
        *this = aList;
    }
    
    
    template<typename T>
    LList<T>& LList<T>::operator =(const LList& aList)
    {
        if(this!=&aList)
        {
            clear(); 
            
            head = NULL; 
            count = 0;
            LNode *cur = aList.head; //pointer to current node to copy in aList
            LNode* tmp = NULL, *pre = NULL; //a temp pointer
            
            while(cur)
            {
                //construct new node
                tmp = new LNode;
                tmp->item = cur->item;
                tmp->next = NULL;
                
                //first node copied
                if(!head){
                    head = tmp;
                    pre = tmp; //pre is the head node
                }
                //connnect pre node to new node
                else{
                    pre->next = tmp;
                    pre = tmp;
                }
                
                //move to next copy node
                cur = cur->next;
            }
            
            count = aList.count;

        }
        return *this;
    }
    
    //
    //default constructor
    //
    template<typename T>
    LList<T>::LList() : count(0), head(NULL)
    {
    }
    
    
    //
    // remove all nodes and reset poitner
    //
    template<typename T>
    void LList<T>::clear()
    {
        LNode *pre = NULL, *cur = head;
        while(cur)
        {
            //travers next
            pre = cur; 
            cur = cur->next;
            
            //remove previous node
            pre->next = NULL;
            delete pre;
            pre = NULL;
        }
        
        head = NULL; 
        //tail = NULL;
        count = 0;
    }
    
    
    
    // removal with exact key match
    // @assume no key duplication
    // @assume T implements == opeator
    template<typename T>
    void LList<T>::removeWithKey(const T& key)
    {
        //locate LNode to remove
        LNode *pre = NULL, *cur = head;
        while(cur && !(cur->item == key)) //check equalness
        {
            pre = cur;
            cur = cur->next;
        }
        
        //LNode found 
        if(cur)
        {
            if(pre)
                pre->next = cur->next; //intermediate/final node
            else 
                head = cur->next;  //remove the head LNode
            
            //destroy node
            cur->next = NULL;
            delete cur;
            cur = NULL;
            
            count--;
        }
        
    }
    
    //
    // insertion in a sorted order 
    // requires that T describes > operator
    // default to use ascending order 
    template<typename T>
    void LList<T>::insertAscend(const T& item)
    {
        //locate LNode to remove
        LNode *pre = NULL, *cur = head;
        while(cur && item > cur->item)
        {
            pre = cur;
            cur = cur->next;
        }
        
        //create the new LNode
        LNode *newN = new LNode;
        newN->item = item;
        
        //insertion at intermediate or final LNode 
        if(pre)  
        {
            newN->next = cur;
            pre->next = newN;
        }
        //insertion at head LNode
        else    
        {
            newN->next = head;
            head = newN;
        }
        
        count++;
    }
    
    
}
#endif 