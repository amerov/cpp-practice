/**
 A non-empty zero-indexed array A consisting of N integers is given. The array consists only of integers in the range [0..N−1]. Each element of the array can be treated as a pointer to another element of the array: if A[K] = M then element A[K] points to A[M].
 The array defines a sequence of jumps of a pawn as follows:
 initially, the pawn is located at position 0;
 on each jump the pawn moves from its current position K to A[K];
 the pawn jumps forever.
 Since the number of possible positions of the pawn is finite, eventually, after some initial sequence of jumps, the pawn enters a cycle. Compute the length of this cycle.
 For example, for the following array A:
 A[0] = 2    A[1] = 3    A[2] = 1
 A[3] = 1    A[4] = 3
 
 consecutive positions of the pawn are: 0, 2, 1, 3, 1, 3, 1, 3, ..., and the length of the cycle is 2.
 Write a function:
 int solution(int A[], int N);
 that, given a non-empty zero-indexed array A consisting of N integers in the range [0..N−1], returns the length of the cycle that the pawn eventually enters, as described above. For example, given the array shown above, the function should return 2.
 Assume that:
 N is an integer within the range [1..200,000];
 each element of array A is an integer within the range [0..N−1].
 Complexity:
 expected worst-case time complexity is O(N);
 expected worst-case space complexity is O(1), beyond input storage (not counting the storage required for input arguments).
 Elements of input arrays can be modified.
 Copyright 2009–2013 by Codility Limited. All Rights Reserved. Unauthorized copying, publication or disclosure prohibited.
 
 **/
#include <iostream>
#include <vector>
using namespace std;

/**
  given an array-based link list of size N, return the final cycle it enters
  array element in [0, N-1]
 
  Runtime O(N)
  Space O(1)
 **/

int solution(vector<int> &A) {

    int N = (int)A.size();
    
    //iterate through each list , mark each entry with its sequence in the list
    
    //for each visit, check if it is already visited,
        // if not yet, continue on,
        //otherwise, stop and count the sequence diff and return length
    
    int offset = N;
    int cur = 0; //init index
    int preIndex = 0;
    
    for(int i=0,next=0; i<N;i++){
        if(A[cur] < 0)
            return (i-offset-preIndex+1);
        
        next = A[cur];
        A[cur] = i - offset;  //the sequence counter (offset)
        preIndex = A[cur];
        cur = next;
    }
    
    return 0; //if 0 length
}



int main(int argc, char** argv)
{

    return 0;
}

