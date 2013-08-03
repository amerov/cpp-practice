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
};

//return paths
typedef std::vector<std::vector<int>> Paths;




/**
  given a tree, find all paths whose value sum equals to the given sum
 **/
void get_sum(const int& targetSum,  int curSum, const Node* node, Paths& paths){
    if(!node) return;
    
    curSum = targetSum + node->value;
    if(curSum == targetSum){
        //enter [root ... cur node] into path
        vector<int> path;
        
    }
    
    //value could be 0 or negative, so should further check 
    get_sum(targetSum, curSum, node->lchild, paths);
    get_sum(targetSum, curSum, node->rchild, paths);
}


int main(int argc, char** argv)
{

    return 0;
}