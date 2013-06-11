//
//  alist.h
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-10.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef __cpp_practice__alist__
#define __cpp_practice__alist__

#include <iostream>

namespace dennycd{
    
    const int ALIST_DEFAULT_SIZE = 2;
    
    /**
      Template-based Dynamic Array Implementation
      It uses geometric expansion with no shrinking
     
     T - basic element type
     K - key for the element 
     **/
    template<typename T>
    class AList{
    public:
        AList();
        AList(const AList& alist);
        AList(const std::initializer_list<T>& inits);
        virtual ~AList();
        AList& operator =(const AList& alist);
    public:
        
        size_t size() const{ return _count;}
        
        void insert(int index, const T& item);
        void remove(int index);
        
        
        //indexing (access via array index)
        const T& get(int index) const;
        void set(int index, const T& item);
        T& operator[](int index);
        
        //search via key, return idx >= 0 on found, -1 if not found
        template<typename K> int find(const K& key) const;

        //ostream
        template<typename TT>
        friend std::ostream& operator <<(std::ostream& oss, const AList<TT>& list);
        
        
    protected:
        T* _base; //dynamically alloced data
        size_t _count; //number of elements in base (starting at 0)
        size_t _size; //total capacity in base
        void _expand(); //expand the array
    };
    
    //==== cons / destructor

    template<typename T>
    std::ostream& operator <<(std::ostream& oss, const AList<T>& list){
        oss << "[";
        for(int i=0;i<list._count;i++){
            oss << list._base[i];
            if(i < list._count - 1) oss << ",";
        }
        oss << "]";
        return oss;
    }
    
    //default constructor
    template<typename T>
    AList<T>::AList(){
        _base = new T[ALIST_DEFAULT_SIZE];
        if(!_base) throw std::exception();
        _size = ALIST_DEFAULT_SIZE;
        _count = 0;
    }
    
    //initializer list constructor
    template<typename T>
    AList<T>::AList(const std::initializer_list<T>& inits)
    {
        //copy the list 
        _base = new T[inits.size()];
        if(!_base) throw std::exception();
        _size = inits.size();
        _count = _size;
        
        int i=0;
        for(auto elem = inits.begin(); elem!=inits.end(); elem++)
            _base[i++] = *elem;
    }
    
    //copy constructor
    template<typename T>
    AList<T>::AList(const AList& alist){
        _base = NULL;
        this->operator=(alist);
    }
    
    //copy overloader 
    template<typename T>
    AList<T>& AList<T>::operator =(const AList<T>& alist){
        if(this!=&alist){
            //free up existing
            if(_base!=NULL) delete[] _base;
            //copy over
            _base = new T[alist._size];
            if(!_base) throw std::exception();
            _size = alist._size;
            for(int i=0;i<alist._count;i++)
                _base[i] = alist._base[i]; 
            _count = alist._count;
        }
        return *this;
    }
    
    
    //virtual destructor
    template<typename T>
    AList<T>::~AList(){
        delete[] _base;
    }
    
    
    //=== public interface
    
    //O(1)
    template<typename T>
    T& AList<T>::operator[](int idx){
        if(idx < 0 || idx >= _count) throw  std::exception();
        return _base[idx];
    }
    
    template<typename T>
    const T& AList<T>::get(int idx) const{
        if(idx < 0 || idx >= _count) throw  std::exception();
        return _base[idx];
    }
    
    template<typename T>
    void AList<T>::set(int idx, const T& item){
        this->operator[](idx) = item;
    }
    

    //O(n)
    template<typename T>
    void AList<T>::remove(int idx){
        if(idx < 0 || idx >= _count) throw std::exception();
        
        //shift [idx+1 ... n-1] left by 1
        for(int i=idx;i<_count-1;i++)
            _base[i] = _base[i+1];
   
        _count -= 1;
    }
    
    //O(n)
    template<typename T>
    void AList<T>::insert(int idx, const T& item){
        if(_count + 1 > _size)
            _expand();
        
        //shift [idx ... n-1] right by 1 -  O(N)
        for(size_t i=_count;i>idx;i--)
            _base[i] = _base[i-1];
        
        //insert at idx
        _base[idx] = item;
        
        //incre
        _count += 1;
    }
    
    

    
    //==== private utilities
    
    //double the capacity
    // O(n)
    template<typename T>
    void AList<T>::_expand()
    {
        T* newbase = new T[_size*2];
        if(!newbase) throw std::exception();
        
        for(int i=0;i<_count;i++)
            newbase[i] = _base[i];
        _size = _size * 2;
        delete[] _base;
        _base = newbase;
    }
    
    
    //O(n) search
    template<typename T> template<typename K>
    int AList<T>::find(const K& key) const
    {
        int idx = -1;
        for(int i=0;i<_count;i++){
            if(_base[i] == key){
                idx = i;
                break;
            }
        }
        return idx;
    }
}
    
    
    
    
    
    
#endif /* defined(__cpp_practice__alist__) */
