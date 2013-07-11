//
//  trie.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 7/10/2013.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_trie_hpp
#define cpp_practice_trie_hpp

#include <vector>
#include <string>

namespace dennycd{
    /**
     A Trie Tree Implementation
     
     Alphabet set describes  |R|
     
     - node value is an alphabet in R
     - internal node has branching degree |R|
     
     Trie tree is a table with String key and Arbitrary Value type
     
     **/
    
    //alphabet set defines a set of unique characters
    typedef std::vector<std::string> Alphabet;
    
    /**
     A trie node
     **/
    template<class Value>
    struct TrieNode{
    public:
        TrieNode(char k, int alphabets);//init with key and alphabet count
        ~TrieNode();
        
        void set_data(const Value& d);
        
    private:
        char            _key; //
        TrieNode**      _childs; //child array
        int             _alphabets; //alphabet count
        Value           _data; //data value
        bool            _empty; //flag for data presence
    };
    
    template <class Value>
    class Trie {
    public:
    };
    
    
    //=== implementation detail===
    template<class Value>
    TrieNode<Value>::TrieNode(char k, int alphabets){
        _empty = true;
        _key = k;
        _alphabets = alphabets;
        _childs = new TrieNode*[alphabets];
        for(int i=0;i<_alphabets;i++)
            _childs[i] = NULL;
    }
    
    //recursive destructor
    template<class Value>
    TrieNode<Value>::~TrieNode(){
        for(int i=0; i<_alphabets; i++){
            if(_childs[i]){
                delete _childs[i]; //recursive delete
                _childs[i] = NULL;
            }
        }
        delete[] _childs;
    }
    
}









#endif