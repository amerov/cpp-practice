/**
  Path Sum II 
 
 http://discuss.leetcode.com/questions/279/path-sum-ii
 
 Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
 
 For example:
 Given the below binary tree and sum = 22,
             5
             / \
             4   8
             /   / \
             11  13  4
             /  \    / \
             7    2  5   1
 return
             [
             [5,4,11,2],
             [5,8,4,5]
             ]
 
 **/

#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;

//tree node
struct Node{
    Node*   lchild;
    Node*   rchild;
    int     value;
    Node(Node* l, Node* r, int v) : lchild(l), rchild(r), value(v){}
};

//return paths
typedef std::vector<int> Path;
typedef std::vector<Path> Paths;

class Solution {
public:
    Solution(int targetSum, Node* root){
        _targetSum = targetSum;
        _root = root;
    }
    
    Paths find_paths(){
        _paths.clear();
        get_sum(0, _root, {});
        return _paths;
    }
    
    
protected:
    
    //recursively find all equal-sum paths
    void get_sum(int curSum, const Node* node, Path curPath){
        if(!node) return;
        
        curSum = _targetSum + node->value;
        curPath.push_back(curSum);
        
        if(curSum == _targetSum)
            _paths.push_back(curPath);
        
        //value could be 0 or negative, so should further check
        get_sum(curSum, node->lchild, curPath);
        get_sum(curSum, node->rchild, curPath);
    }
    
    
private:
    Paths _paths;
    int _targetSum;
    Node* _root;
};





int main(int argc, char** argv)
{
    /**
     
         5
         / \
         4   8
         /   / \
         11  13  4
         /  \    / \
         7    2  5   1
     
     **/

    Node* n7 = new Node(NULL,NULL,7);
    Node* n2 = new Node(NULL,NULL,2);
    Node* n5 = new Node(NULL,NULL,5);
    Node* n1 = new Node(NULL,NULL,1);
    
    Node* n11 = new Node(n7,n2,11);
    Node* n13 = new Node(NULL,NULL,13);
    Node* n4 = new Node(n5,n1,4);

    Node* n4_dup = new Node(n11,NULL,4);
    Node* n8 = new Node(n13,n4,8);

    Node* root = new Node(n4_dup,n8,7);
    
    Solution sol(22, root);
    Paths paths = sol.find_paths();
    
    for(Path& p : paths){
        cout << "[";
        for(int& v : p) cout << v << ",";
        cout << "]" << endl;
    }
    
    
    
    return 0;
}





