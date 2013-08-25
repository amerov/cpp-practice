
///
//  CAQueue.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-09-21.
//  -
//
#ifndef ASTEMSOFT_ADT_CIRCULAR_ARRAY_QUEUE
#define ASTEMSOFT_ADT_CIRCULAR_ARRAY_QUEUE

#include <iostream>
#include <fstream> 

namespace astemsoft
{
    //CAQueue Exception
    class CAQueueException : public std::exception
    {
    public:
        CAQueueException(const std::string& msg = "") : message(msg){}
        ~CAQueueException() throw(){}
        const char* what() const throw()
        {
            return ("AstemSoft ADT CAQueue Exception: " + message).c_str();
        }
    private:
        std::string message;
    };
    
    /**
     Circular Array-Based ADT Queue Implementation
     
     the array has data segment and empty segment
     start and end positional pointers are used to track data segment
     insertion/deletion at both end of data requires constant time
     the array will dynamically grow in the order of 2^n upon full
     **/
    template<typename T>
    class CAQueue 
    {
    public:
        static const int DEFAULT_SIZE = 2; //initial default storage size
        
        CAQueue();
        CAQueue(const CAQueue& queue) throw(CAQueueException);
        CAQueue& operator =(const CAQueue& queue) throw(CAQueueException);
        virtual ~CAQueue();
        
        int size() const;
        bool empty() const;
        
        void enqueue(const T& item) throw(CAQueueException);
        void dequeue();
        void front(T& item) const throw(CAQueueException); 
        
        
        void print() const;
        void printAll() const; //print the whole array
        void clear();
        
        void save(const std::string& filename) const throw(CAQueueException); 
        void restore(const std::string& filename) throw(CAQueueException);
        
    private:
        bool indata(int cur) const; //condition check if a given index is within data segment
        void retrieve(int index, T& item) const throw(CAQueueException); //retrieve via index
        void expand() throw(CAQueueException);//enlarge array storage in order of 2
        
    private:
        T* base;  
        int start; //start position of data segment
        int end; //ending position of data segment
        int max_count; //current storage size of array
        
    };
    
    
    template<typename T>
    void CAQueue<T>::save(const std::string& filename) const throw(CAQueueException)
    {
        using namespace std;
        ofstream ofs;
        ofs.open(filename.c_str());
        
        if(ofs.fail())
            throw CAQueueException("failed to open file for save");
        
        T item;
        for(int i = 0; i< size(); i++)
        {
            retrieve(i, item);
            ofs << item << endl;
        }
        
        ofs.close();
    }
    
    
    template<typename T>
    void CAQueue<T>::restore(const std::string& filename) throw(CAQueueException)
    {
        using namespace std;
        T item;
        ifstream ifs;
        ifs.open(filename.c_str());
        
        if(ifs.fail())
            throw CAQueueException("failed to open file for restore");
        
        clear(); //reset to default storage 
        
        //read in each item and insert into end of list 
        while(ifs >> item)
            enqueue(item);
        
        ifs.close();
    }
    
    
    template<typename T>
    bool CAQueue<T>::indata(int cur) const
    {
        if(empty() || cur < 0)
            return false;
        else 
            if(start <= end && cur <= end && cur >= start)
                return true;
            else
                if(start > end && (cur >= start || cur <= end))
                    return true;
                else 
                    return false;
    }
    
    //append to end of the queue
    template<typename T>
    void CAQueue<T>::enqueue(const T& item) throw(CAQueueException)
    {
        if( size() == max_count)
            expand();
        
        start = (start==-1) ? 0 : start; //bootstrap case,otherwise unchange
        end = (end + 1) % max_count; //loop to next circular pos
        base[end] = item;
    }
    
    
    //take from front of queue
    template<typename T>
    void CAQueue<T>::dequeue()
    {
        if(empty())
            return;
        if(start == end)
            start = end = -1;  //empty case reached 
        else 
            start = (start + 1) % max_count; //normal, increase start pointer   
    }
    
    
    
    template<typename T>
    void CAQueue<T>::front(T& item) const throw(CAQueueException)
    {
        if(empty())
            throw CAQueueException("empty queue");
        else 
            item = base[start];
    }
    
    
    
    template<typename T>
    void CAQueue<T>::expand() throw(CAQueueException)
    {
        T* newbase = new T[2*max_count]; 
        if(!newbase)
            throw CAQueueException("expand out of memory");
        
        //copy old content to the begnining of new array
        int cur = start; //source position in old array
        int pos = 0; //copy position in new array
        int count = size(); //keep track of how many copied, 
        
        //in case full array copy, known when to stop whenever circulate back to start
        while(indata(cur) && pos < count)
        {
            newbase[pos++] = base[cur];  //copy the item
            cur = (cur + 1) % max_count; //move to next item in data 
        }
        
        //remove old array
        delete base;
        base = newbase;
        max_count = 2 * max_count;
        start = 0; 
        end = pos - 1;
    }
    
    template<typename T>
    void CAQueue<T>::retrieve(int index, T& item) const throw(CAQueueException)
    {
        if(empty() || index < 0 || index >= size())
            throw CAQueueException("index out of bound");
        
        item = base[ (start + index) % max_count ];
    }
    
    
    template<typename T>
    void CAQueue<T>::print() const
    {
        using namespace std;
        
        if(empty()){
            cout << "empty list" << endl;
            return;
        }
        
        int cur = start;
        int count = 0;
        do{
            cout << base[cur] << ",";
            cur = (cur+1) % max_count; //circular increase
            count++;
        }while(count < size());
        
        cout << endl;
    }
    
    template<typename T>
    void CAQueue<T>::printAll() const
    {
        using namespace std;
        cout << endl;
        for(int i=0; i<max_count; i++)
        {
            if( indata(i))
                cout << "[" << base[i] << "]"; 
            else 
                cout << "*";
        }
        cout << endl;
    }
    
    
    //reset content and shrink array to default size
    template<typename T>
    void CAQueue<T>::clear()
    {
        if(base){
            delete base;
            base = NULL;
        }
        
        max_count = DEFAULT_SIZE;
        start = end = -1;
        base = new T[DEFAULT_SIZE];
    }
    
    template<typename T>
    int CAQueue<T>::size() const
    {
        if(empty())
            return 0;
        
        if(end >= start)
            return (end - start + 1);
        else
            return (max_count + end - start + 1);
    }
    
    //if start/end both points to head, indicates empty case
    template<typename T>
    bool CAQueue<T>::empty() const
    {
        return (start == -1 && end == -1); 
    }
    
    template<typename T>
    CAQueue<T>& CAQueue<T>::operator =(const CAQueue<T>& queue) throw(CAQueueException)
    {
        if(this==&queue)
            throw CAQueueException("circular copy detectd");
        
        clear(); //reset list content
        
        //enqueue all items from queue
        T item;        
        for(int i=0; i < queue.size(); i++)
        {
            queue.retrieve(i,item);
            enqueue(item);
        }
        
        return *this;
    }
    
    template<typename T>
    CAQueue<T>::CAQueue(const CAQueue<T>& queue) throw(CAQueueException)
    {
        *this = queue;
    }
    
    template<typename T>
    CAQueue<T>::~CAQueue()
    {
        if(base){
            delete base;
            base = NULL;
        }
    }
    
    template<typename T>
    CAQueue<T>::CAQueue()
    {
        base = new T[DEFAULT_SIZE];
        max_count = DEFAULT_SIZE;
        start = end = -1; //invalid case while empty
    }
    
}
#endif