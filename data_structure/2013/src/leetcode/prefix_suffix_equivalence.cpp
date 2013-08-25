/**
 
 A prefix of a string S is any leading contiguous part of S. For example, the string "codility" has the following prefixes: "", "c", "co", "cod", "codi", "codil", "codili", "codilit" and "codility". A prefix of S is called proper if it is shorter than S.
 A suffix of a string S is any trailing contigous part of S. For example, the string "codility" has the following suffixes: "", "y", "ty", "ity", "lity", "ility", "dility", "odility" and "codility". A suffix of S is called proper if it is shorter than S.
 Write a function:
 int solution(const string &S);
 that, given a string S consisting of N characters, returns the length of the longest string that is both a proper prefix of S and a proper suffix of S. The function should return −1 if no such string exists.
 For example, given S = "abbabba" the function should return 4, because:
 proper prefixes of S are: "", "a", "ab", "abb", "abba", "abbab", "abbabb";
 proper suffixes of S are: "", "a", "ba", "bba", "abba", "babba", "bbabba";
 string "abba" is both a proper prefix and a proper suffix of S;
 this is the longest such string.
 For example, given S = "codility" the function should return 0, because:
 string "" is both a proper prefix and a proper suffix of S;
 this is the longest such string.
 Complexity:
 expected worst-case time complexity is O(N);
 expected worst-case space complexity is O(N) (not counting the storage required for input arguments).
 Assume that:
 the length of S is within the range [0..1,000,000];
 string S consists only of lower-case letters (a−z).
 Copyright 2009–2013 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited.
 
 
 **/

#include <iostream>
#include <string>
using namespace std;


/**
 the length of S is within the range [0..1,000,000];
 string S consists only of lower-case letters (a−z).

 check if there exist an identical prefix and suffix in the string
 
 @return -1 if no such
 
  RunTime O(N)
  Space   O(N)
 **/
int solution(const string &S) {
    int length = 0;
    int N = (int)S.size();
    int pre = 0;
    int suf = N - 1;
    while(true){
        if(S[pre] == S[suf]){
            length++;
            pre++;
            suf--;
        }
        else break;
    }
    
    return length==0 ? -1 : length;
}


int main(int argc, char** argv)
{
    
    return 0;
}

