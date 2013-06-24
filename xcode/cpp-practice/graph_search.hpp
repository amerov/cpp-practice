//
//  graph_search.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-24.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_graph_search_hpp
#define cpp_practice_graph_search_hpp

#include "alg_share.h"
#include "allist.hpp"
#include "astack.hpp"
#include "aqueue.hpp"

/**
  Collection of graph search algorithm
 **/
namespace dennycd {
    
    
    template<class GRAPH, class DATA>
    class GraphSearch{
        
    public:
        
        typedef std::function<void(const DATA& node)> TraverseFunc;

        
        static void breath_first_search_queue(GRAPH& graph, TraverseFunc func){
            AQueue<DATA> queue;
            DATA begin = graph.any();
            ALList<DATA> visited;
            
            //initial
            func(begin);
            queue.enqueue(begin);
            visited.insert(0,begin);
            
            while(!queue.empty()){
                
                DATA cur = queue.dequeue();
                
                //visit all neighbor and enqueue
                AList<DATA> neis;
                graph.neighbours(cur,neis);
                for(int i=0;i<neis.size();i++){
                    if(visited.find(neis[i]) == -1){
                        func(neis[i]);
                        visited.insert(0, neis[i]);
                        queue.enqueue(neis[i]);
                        
                    }
                }
                
            }
            
        }

        
        
        
        //stack based
        static void depth_first_search_stack(GRAPH& graph, TraverseFunc func){
            AStack<DATA> stack;
            DATA begin = graph.any();
            ALList<DATA> visited;
            
            
            //initial
            func(begin);
            stack.push(begin);
            visited.insert(0, begin);
            
            //until stack depleted
            while(!stack.empty()){
                
                DATA cur = stack.top();
                
                //if there is a neighbor not yet visited , visit it and stack up and descend down
                AList<DATA> neis;
                graph.neighbours(cur,neis);
                
                bool has_unvisited_neighbor = false;
                for(int i=0;i<neis.size();i++){
                    if(visited.find(neis[i]) == -1){
                        
                        //visit the neighbor and put it on top
                        func(neis[i]);
                        visited.insert(0, neis[i]);
                        stack.push(neis[i]);
                        has_unvisited_neighbor = true;
                        break;
                    }
                }
                
                //otherwise pop and retrack
                if(!has_unvisited_neighbor)
                    stack.pop();
                
            }
            
        }
        
        
        
        static void depth_first_search_recrusive(GRAPH& graph, TraverseFunc func){
            DATA begin = graph.any();
            ALList<DATA> visited;            
            _recursive_depth_first_search(graph, begin, visited, func);
        }
       
            
//        static void breath_frist_search_recursive(GRAPH& graph, TraverseFunc func){
//            DATA begin = graph.any();
//            ALList<DATA> visited;
//            ALList<DATA> future;
//            
//            //visit the first
//            func(begin);
//            visited.insert(0,begin);            
//            _recursive_breath_first_search(graph, begin, visited, func, future);
//        }
        
        
    private:
        
//        static void _recursive_breath_first_search(GRAPH& graph, const DATA& cur, ALList<DATA>& visited, TraverseFunc& func, ALList<DATA>& futureVisit){
//            assert(visited.find(cur)>=0);
//            futureVisit.clear();
//            
//            //traverse down all neis
//            AList<DATA> neis;
//            graph.neighbours(cur,neis);
//            
//            ALList<DATA> traveseList;
//            
//            for(int i=0;i<neis.size();i++){
//                if(visited.find(neis[i]) == -1){
//                    
//                    //visit the neighbor first
//                    func(neis[i]);
//                    visited.insert(0,neis[i]);
//                    
//                    //mark for traversal
//                    traveseList.insert(0, neis[i]);
//                }
//            }
//
//                
//            for(int i=0;i<traveseList.size();i++)
//                _recursive_breath_first_search(graph, traveseList[i], visited, func, futureVisit);
//            
//            
//            //visit the future list after all traversal
//            for(int i=0;i<futureVisit.size();i++){
//                if(visited.find(futureVisit[i])==-1){
//                    func(futureVisit[i]);
//                    visited.insert(0,futureVisit[i]);
//                }
//            }
//            
//        }
        
        
        static void _recursive_depth_first_search(GRAPH& graph, const DATA& cur, ALList<DATA>& visited, TraverseFunc& func){
            assert(visited.find(cur)==-1);
            
            //visit current
            func(cur);
            visited.insert(0, cur);
            
            //traverse down all neis
            AList<DATA> neis;
            graph.neighbours(cur,neis);
            
            for(int i=0;i<neis.size();i++){
                if(visited.find(neis[i]) == -1)
                    _recursive_depth_first_search(graph, neis[i], visited, func);
            }
        }
        
    };

    
    
    
    
}


#endif
