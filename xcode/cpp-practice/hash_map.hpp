//
//  hash_map.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-24.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_hash_map_hpp
#define cpp_practice_hash_map_hpp

#include <vector>
#include <map>

namespace dennycd {
    
    /**
      A Bucket-based implementaion of HashMap 
     **/

    template<typename KEY, typename T, typename Hash>
    class HashMap : private std::vector< std::map< KEY,T> > {
    public:
        HashMap(const int maxBuckets);
        typename std::map<KEY,T>::const_iterator findItem(const KEY& key); //access the item pointer with the bucket holding the keyed item
        void insert(const KEY& key, const T& item); //insert with key
        int erase(const KEY& k); //return # of item removed        
        T& operator[](KEY& key); //retrieve item via key

        template<typename KK, typename TT, typename HH>
        friend std::ostream& operator<<(std::ostream& oss, const HashMap<KK,TT,HH>& map);
        
    private:
        Hash hash; 
    };
    

    
    template<typename KEY, typename T, typename Hash>
    HashMap<KEY, T, Hash>::HashMap(const int maxBuckets){
        this->resize(maxBuckets+1);
    }
 
    
    template<typename KEY, typename T, typename Hash>
    T& HashMap<KEY, T, Hash>::operator[](KEY& key){
        return at(hash(key))[key]; //hash to find index, then access via key again
    }
    
    template<typename KEY, typename T, typename Hash>
    typename std::map<KEY, T>::const_iterator HashMap<KEY, T, Hash>::findItem(const KEY& key){
        typename std::map<KEY, T>::const_iterator it;
        int idx = hash(key);
        it = this->at(idx).find(key);
        return it;
    }
    
    template<typename KEY, typename T, typename Hash>
    void HashMap<KEY, T, Hash>::insert(const KEY& key, const T& item){
        int idx = hash(key);
        this->at(idx)[key] = item;
    }
    
    template<typename KEY, typename T, typename Hash>
    int HashMap<KEY, T, Hash>::erase(const KEY& key){
        int idx = hash(key);
        return this->at(idx).erase(key);
    }
    
    
    template<int BASE>
    class IntegerModuloHash{
    public:
        int operator()(int key){
            return key % BASE;
        }
    };
    
    template<int BASE>
    class StringModuloHash{
    public:
        int operator()(std::string key){
            int ikey = 0;
            for(int i=0;i<key.length();i++)
                ikey += (ikey + key[i]) * 32;
            return ikey % BASE;
        }
    };
 
    template<typename KK, typename TT, typename HH>
    std::ostream& operator<<(std::ostream& oss, const HashMap<KK,TT,HH>& map){
        oss << "{";
        for(auto bucket : map){
            for(auto item = bucket.begin(); item!=bucket.end();item++){
                oss << "[" << item->first << "==>" << item->second << "]";
            }
        }
        oss << "}";
        return oss;
    }
}


#endif
