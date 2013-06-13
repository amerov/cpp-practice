//
//  radix_sort.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-13.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_radix_sort_hpp
#define cpp_practice_radix_sort_hpp

#include "alg_share.h"
#include "alist.hpp"

namespace dennycd {
 
    //get the dth least significant digit on val
    char _get_digit(int d_max, int d, const std::string& val){
       
        std::string tempVal = val;
        while(tempVal.length() < d_max)
            tempVal += ' ';
        
        int pos = (int)tempVal.length() - (d_max-d+1);
        return tempVal.at(pos);
    }
    
    
    //get the dth least significant digit on val
    int _get_digit(int d_max, int d, const int& val){
        
        int ret;
        int temp = val;
        for(int i= d_max; i >=d; i--){
            ret = temp % 10;
            temp = floor(temp/10);
        }
        
        return ret;
    }
    
    /**
      Integer radix sort 
     
     
     
     
     
     **/
    template<typename D, typename E = int>
    void radix_sort_int(D& data){
        
        int n = (int)data.size();
        
        AList< AList<E> > groups; 
        for(int i=0;i<10;i++)
            groups.insert(0,AList<E>());
        
        
        //infer the longest digit
        int max_digit = 0;
        for(int i=0;i<n;i++){
            E val = data[i];
            int digit = 0;
            do{
                val = floor(val / 10);
                digit++;
            }while(val >= 1);
        
            if(digit > max_digit)
                max_digit = digit;
        }
        
//        std::cout << "max digit " << max_digit << std::endl;
        
        for(int d = max_digit; d >= 1; d--){

            //clean up group
            for(int i=0;i<10;i++) groups[i].clear();
            
            //move into 10 bucket while preserving the order
            for(int i=0;i<n;i++){
                int val = _get_digit(max_digit, d, data[i]);
                groups[val].insert((int)groups[val].size(), data[i]);
            }
            
            //merge the group back into data
            data.clear();
            for(int g=0;g<groups.size();g++){
                AList<E> group = groups[g];
                for(int e=0;e<group.size();e++){
                    data.insert((int)data.size(), group[e]);
                }
            }
            
            
        }
        
    }

    
    template<typename D, typename E = std::string>
    void radix_sort_string(D& data){
        using namespace std;
        int n = (int)data.size();
        
        std::string alphabet = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        AList<AList<std::string>> groups;
        for(int i=0;i<alphabet.length();i++)
            groups.insert(0, AList<std::string>());
        
        
        int max_digit = 0;
        for(int i=0;i<n;i++){
            if(data[i].length() > max_digit)
                max_digit = (int)data[i].length();
        }
        
        
        for(int d = max_digit; d >= 1; d--){
            
//            cout << "grouping digit " << d << endl;
            
            //clean up group
            for(int i=0;i<groups.size();i++) groups[i].clear();
            
            //move into 10 bucket while preserving the order
            for(int i=0;i<n;i++){
                char val = _get_digit(max_digit, d, data[i]); //
//                cout << "digit for " << data[i] << " is " << val << endl;
                
                int pos = (int)alphabet.find(val);
                assert(pos!=std::string::npos);
                
                try{
                    groups[pos].insert((int)groups[pos].size(), data[i]);
                }catch(std::exception e){
//                    std::cout << "exception" << std::endl;
                }
            }
            
//            cout << "merging" << endl;
            
            //merge the group back into data
            data.clear();
            for(int g=0;g<groups.size();g++){
                AList<E> group = groups[g];
                for(int e=0;e<group.size();e++){
                    data.insert((int)data.size(), group[e]);
                }
            }
            
            
        }
        
        
    }
}













#endif
