/**
REF http://discuss.leetcode.com/questions/236/spiral-matrix-ii
    http://leetcode.com/2010/05/printing-matrix-in-spiral-order.html
 
 
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
      for a rect of n edges, print clock-wise along its edge
     
      @ i - starting row index
      @ j - starting column index 
      @ m - row/column count
      @ count - current value count
     **/
    void _recursive_print(int i, int j, int m, int& count){
        if(m<=0) return;
        
        for(int k=0;k<m;k++)
            _matrix[i*_n + j + k] = count++;
        for(int k=1;k<m;k++)
            _matrix[(i+k)*_n + j + m - 1] = count++;
        for(int k=m-1;k>=0;k--)
            _matrix[ (i+m-1)*_n + j + k] = count++;
        for(int k=m-2;k>0;k--)
            _matrix[ (i+k)*_n + j ] = count++;
        
        _recursive_print(i+1, j+1, m-2, count);
    }
    
    
private:
    int _n;
    int* _matrix;
};

int main(int argc, char* argv[]){
    
    return 0;
}