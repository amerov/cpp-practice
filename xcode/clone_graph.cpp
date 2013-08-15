/**
  REF http://leetcode.com/2012/05/clone-graph-part-i.html
 
 Clone a graph. Input is a Node pointer. Return the Node pointer of the cloned graph.
 

**/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

//A graph is defined below:
struct Node {
    int data; //fake data value
    vector<Node*> neighbors;
    Node(int d) : data(d){}
};


class Solution{
public:
    Solution(Node* root){
        m_root = root;
    }
    
    Node* graph_copy(){
        m_visited.clear();
        return recursive_copy_dfs(m_root);
    }

    //breath first search using queue
    Node* bfs_graph_copy(Node* root){
        queue<Node*> qu;
        m_visited.clear();
        
        qu.push(root);
        
        while(!qu.empty()){
            //copy the top and add its neighbor
        }
    }
    
protected:
    

    
    
    Node* recursive_copy_dfs(Node* node){
        if(!node) return NULL;
        
        Node* cur = new Node(node->data);
        m_visited[node] = cur; //mark as visited
        
        for(Node* elem : node->neighbors){
            if(m_visited.count(elem)==0)
                cur->neighbors.push_back(recursive_copy_dfs(elem));
            else
                cur->neighbors.push_back(m_visited[elem]);
        }
        
        return cur;
    }
    
private:
    
    unordered_map<Node*, Node*> m_visited; //mapping from source node to new node
    Node* m_root;
};


int main(int argc, char** argv){
    
    
    
    return 0;
}