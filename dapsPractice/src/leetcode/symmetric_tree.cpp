/**
 REF http://discuss.leetcode.com/questions/274/symmetric-tree
 

 Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
 
 For example, this binary tree is symmetric:
 
 1
 / \
 2   2
 / \ / \
 3  4 4  3
 But the following is not:
 1
 / \
 2   2
 \   \
 3    3
 Note:
 Bonus points if you could solve it both recursively and iteratively.
 
**/

#include <iostream>
#include <cassert>
#include <queue>
#include <stack>

/**
  Given a tree, to check whether it is symmetric
 
  - in-order traversal, the result string is symmetric (reverse is identical)
 **/

using namespace std;

struct Node {
    Node*   lchild;
    Node*   rchild;
    int     key;
    Node(Node* l, Node* r, int k) : lchild(l), rchild(r), key(k){}
};


class Solution{
public:
    Solution(Node* root){
        _root = root;
    }
    
    bool symmetric(){
        queue<int> q;
        stack<int> stk;
        _inorder_traverse(_root, q, stk);
        
        while (!stk.empty()) {
            if(stk.top()!=q.front()) return false;
            stk.pop();
            q.pop();
        }
        
        return true;
    };
    
protected:
    void _inorder_traverse(Node* node, queue<int>& queue, stack<int> & stk){
        if(!node) return;
        _inorder_traverse(node->lchild, queue, stk);
        queue.push(node->key);
        stk.push(node->key);
        _inorder_traverse(node->rchild, queue, stk);
    }
    
private:
    Node* _root;
};



int main(int argc, char *argv[]){
    
    /**
     
     1
     / \
     2   2
     / \ / \
     3  4 4  3
     
     **/
    
    Node* n3 = new Node(NULL,NULL,3);
    Node* n4 = new Node(NULL,NULL,4);
    Node* n2 = new Node(n3,n4,2);
    
    
    Node* m3 = new Node(NULL,NULL,3);
    Node* m4 = new Node(NULL,NULL,4);
    Node* m2 = new Node(m4,m3,2);
    
    Node* root = new Node(n2,m2,1);
    
    Solution sol(root);
    
    cout << (sol.symmetric() ? "symmetric" : "not symmetric") << endl;
    assert(sol.symmetric());
    
    
    return 0;
}


