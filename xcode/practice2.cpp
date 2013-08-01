
/**
 Write a function
 int solution(const string &S);
 that, given a string S consisting of N characters containing a big-endian hexadecimal representation of a non-negative integer M, returns the number of bits set to 1 in the binary representation of number M.
 Assume that:
 N is an integer within the range [1..100,000];
 string S consists only of the following characters: "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E" and/or "F".
 For example, given S = "2F", the function should return 5, because string "2F" represents number 47, the binary representation of number 47 is 101111 and it contains five bits set to 1.
 Complexity:
 expected worst-case time complexity is O(N);
 expected worst-case space complexity is O(1) (not counting the storage required for input arguments).

 
 **/
#include <iostream>
#include <string>
#include <map>
#include <cassert>
using namespace std;

/**
 given a string of length N with hex representation of a int,
 return number of 1 bits
 
 Runtime O(N)
 Space   O(1)
 
 **/
int solution(const string &S) {
    
    std::map<char, int> HexBitMap;
    HexBitMap['0'] = 0;
    HexBitMap['1'] = 1;
    HexBitMap['2'] = 1;
    HexBitMap['3'] = 2;
    HexBitMap['4'] = 1;
    HexBitMap['5'] = 2;
    HexBitMap['6'] = 2;
    HexBitMap['7'] = 3;
    HexBitMap['8'] = 1;
    HexBitMap['9'] = 2;
    HexBitMap['A'] = 2;
    HexBitMap['B'] = 3;
    HexBitMap['C'] = 2;
    HexBitMap['D'] = 3;
    HexBitMap['E'] = 3;
    HexBitMap['F'] = 4;
    
    int N = (int)S.size();
    int one_bits = 0;

    for(int i=0;i< N;i++)
        one_bits += HexBitMap[S[i]];
    return one_bits;
}



int main(int argc, char** argv)
{
    cout << solution("FF") << endl;
    
    return 0;
}

