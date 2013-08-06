/**
REF http://discuss.leetcode.com/questions/236/spiral-matrix-ii
 
 Given an integer n, generate a square matrix filled with elements from 1 to n^2 in spiral order.
 
 For example,
 Given n = 3,
 
 You should return the following matrix:
 [
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
 ]
 
**/

//struct Position{
//    int i;
//    int j;
//};


class Solution {
public:
    Solution(int n){
        _n = n;
        _matrix = new int[n*n];
        for(int i=0;i<n*n;i++)
            _matrix[i] = 0;
    }
    
    ~Solution(){
        delete[] _matrix;
    }
    
    
    
    const int* get_matrix(){

        return _matrix;
    };
    
    
protected:
    
    /**
      given current pos, infer the next index to move into
     **/
    int next_move(int cur){
        int i = cur / _n;
        int j = cur % _n;
        
        //move rightwards
        if(i-1<0 || _matrix[i-1]>0)  //north invalid
            if(j+1 < _n && _matrix[j+1]==0) //east valid
                return i*_n+j+1;
            else{
                if(i+1 < _n && _matrix[])
            }
        
        
        
    }
    
private:
    int _n;
    int* _matrix;
};

int main(int argc, char* argv[]){
    
    return 0;
}