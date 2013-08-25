//
//  Graph.hpp
//  dapsPractice
//
//  Created by Denny C. Dai on 10-10-01.
//  -
//
#ifndef ASTEMSOFT_ADT_GRAPH_HPP
#define ASTEMSOFT_ADT_GRAPH_HPP

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

#include "Stack.hpp"
#include "Queue.hpp"

#include "Set.hpp"
#include "SetASorted.hpp"
#include "BinaryTreeA.hpp"
#include "BinaryTreeL.hpp"

namespace astemsoft
{
    namespace adt
    {
        
        class GraphException : public std::exception
        {
        public:
            GraphException(const std::string& msg = "") : message(msg){}
            ~GraphException() throw(){}
            const char* what() const throw()
            {
                return ("AstemSoft ADT Graph Exception: " + message).c_str();
            }
        private:
            std::string message;
        };
        
        
        //Edge Node
        template<typename V, typename VKey, typename E>
        class GraphENode
        {
        public:
            GraphENode(){}
            GraphENode(const GraphENode& enode){ *this = enode;}
            GraphENode& operator =(const GraphENode& enode)
            {
                if(this!=&enode)
                {
                    item = enode.item;
                    begin = enode.begin;
                    end = enode.end;
                }
                return *this;
            }
            
            //note that the search key of an edge in the graph
            //is the end point value which uniquely identify the 
            //edge within a vertice node's edge set
            operator VKey() const
            {
                return end;
            }
            
            friend std::ostream& operator <<(std::ostream& oss, const GraphENode& e)
            {
                oss << "{" << e.item << "} => " << e.end << std::endl;
                return oss;
            }     
            friend std::ofstream& operator <<(std::ofstream& ofs, const GraphENode& v)
            {
                ofs << v.item << std::endl;
                return ofs;
            }
            friend std::ifstream& operator >>(std::ifstream& ifs, GraphENode& v)
            {
                ifs >> v.item;
                return ifs;
            }
            
        public:
            E item;
            VKey begin;//the start point of this edge
            VKey end; //the end point of this edge
        };
        
        
        //Vertice Node
        template<typename V, typename VKey, typename E>
        class GraphVNode
        {
        public:
            GraphVNode(){}
            GraphVNode(const GraphVNode& vnode){ *this = vnode;}
            GraphVNode& operator=(const GraphVNode& vnode)
            {
                if(this!=&vnode)
                {
                    item = vnode.item;
                    edges = vnode.edges;
                }
                return *this;
            }
            
            //type cast operator
            //enable automatic conversion from V item to its search key
            operator VKey() const
            {
                return (VKey)item;
            }
            
            friend std::ostream& operator <<(std::ostream& oss, const GraphVNode& v)
            {
                oss << "{" << v.item << "} : " << v.edges.size() << std::endl;
                return oss;
            }
            
            friend std::ofstream& operator <<(std::ofstream& ofs, const GraphVNode& v)
            {
                ofs << v.item << std::endl;
                return ofs;
            }
            
            friend std::ifstream& operator >>(std::ifstream& ifs, GraphVNode& v)
            {
                ifs >> v.item;
                return ifs;
            }
            
        public:
            V item;
            SetASorted< GraphENode<V,VKey,E> > edges;
            //BinaryTreeL< GraphENode<V, VKey, E> > edges;
            //BinaryTreeA< GraphENode<V, VKey, E> > edges;
        };        
        
        
        /**
         Generic Implementation of ADT Graph
         adjacent list implementation is used
         
         V          - payload item type on vertice
         VKey       - search key type for vertice
         E          - payload item type on edge
         **/
        template<typename V, typename VKey, typename E>
        class Graph
        {
        public:
            typedef GraphENode<V,VKey,E> ENode;
            typedef GraphVNode<V,VKey,E> VNode;
            enum TraverseType{
                DepthFirst,
                BreathFirst
            };
            
        public:
            Graph(){}
            virtual ~Graph(){}
            Graph(const Graph& g){ *this = g; }
            Graph& operator=(const Graph& g){ if(this!=&g){vset = g.vset;} return *this;}
            
            bool empty() const{return vset.empty();}
            int vertices() const{return vset.size();}
            int edges() const;
            
            void insertV(const V& item) throw(GraphException);//insert a unique keyed vertice
            bool existV(const VKey& key) const; //vertice existence for the given key
            void retrieveV(const VKey&k, V& item) const throw(GraphException);//retrieve keyed verice
            void removeV(const VKey& key) throw(GraphException);//remove vertice matching the given key
            
            //note that the edge shoud be directional
            void insertE(const VKey& begin, const VKey& end, const E& item) throw(GraphException); 
            bool existE(const VKey& begin, const VKey& end) const;
            void retrieveE(const VKey& begin, const VKey& end, E& item) const throw(GraphException);
            void removeE(const VKey& x, const VKey& y) throw(GraphException);
            void print() const;
            
            template<typename FUNC>
            void traverse(const VKey& start, FUNC& func, TraverseType type = BreathFirst) throw(GraphException); 
            
            bool local_search(const VKey& start, const VKey& target, TraverseType type = BreathFirst);
            
        private:
            template<typename FUNC> 
            void traverse_depth_first(const VKey& start, FUNC& func, SetASorted<VKey>& visits);
            
            template<typename FUNC> 
            void traverse_breath_first(const VKey& start, FUNC& func, SetASorted<VKey>& visits, Queue<VKey> queue);
            
            //TODO: use generic ADT Set Type 
            //BinaryTreeL< VNode > vset;
            //BinaryTreeA< VNode > vset;
            SetASorted<VNode> vset;
        };
        
        

        ///local search operator
        namespace graph{
            template<typename V, typename VKey, typename E>
            struct LocalSearcher
            {
                LocalSearcher() : terminate(false){}
                void operator()(const GraphVNode<V,VKey,E>& vtx)
                {
                    if( (VKey)vtx == target)
                        terminate = true;
                }
                
                //flag whether search shall terminate
                //the boolean type caster shall always
                //be implemented to control the process of a graph traversal
                operator bool() const
                {
                    return terminate;
                }
                
            
                VKey target; //target key to search for
                bool terminate; //indicate if the search shall stop
            };
        }
        template<typename V, typename VKey, typename E>
        bool Graph<V, VKey, E>::local_search(const VKey& start, const VKey& target, 
                                             TraverseType type)
        {
            graph::LocalSearcher<V, VKey, E> ls;
            ls.target = target;
            
            try{
                SetASorted<VKey> visits;
                Queue<VKey> queue;
                
                if(type==DepthFirst)
                    traverse_depth_first(start,ls,visits);
                else
                    traverse_breath_first(start,ls,visits,queue);
            }
            catch(SetException e)
            {
                return false; //on exception, consider not found
            }
            
            return (bool)ls;
        }
        
        template<typename V, typename VKey, typename E>
        template<typename FUNC>
        void Graph<V, VKey, E>::traverse(const VKey& start, FUNC& func, TraverseType type) throw(GraphException)
        {
            try{
                SetASorted<VKey> visits;
                if(type==DepthFirst)
                    traverse_depth_first(start,func,visits);
                else 
                if(type==BreathFirst)
                {
                    Queue<VKey> queue;
                    travese_breath_first(start,func,visits,queue);
                }
                
            }
            catch(SetException e)
            {
                throw GraphException(e.what());
            }
        }
        
        //
        // Non-recursive Version of Breath First Traversal Using 
        //
        // a key queue is used to maintain nodes to be traversed on each layer
        //
        // a termination flag is used to indicate wether the traversal shall stop
        // to suppor this, the function object shall support type casting to a boolean value
        template<typename V, typename VKey, typename E>
        template<typename FUNC>
        void Graph<V, VKey, E>::traverse_breath_first(const VKey& start, FUNC& func, 
                                                      SetASorted<VKey>& visits,
                                                      Queue<VKey> queue)
        {
            visits.template insert<VKey>(start);
            queue.enqueue(start);
            bool terminate = false; //termination flag to indicate when to stop execution
            
            VKey curK;
            while(!queue.empty() && !terminate)
            {
                //dequeue and process it
                queue.dequeue(curK);
                vset.update(func,curK);
                
                //enqueue all unvisited neighbor nodes
                VNode curV;
                vset.retrieve(curK,curV);
                for(int i=0;i<curV.edges.size();i++)
                {
                    //mark all unvisited neighbors as visited and enqueue
                    if(! visits.exist( (VKey)(curV.edges[i]) )){
                        visits.template insert<VKey>( (VKey)(curV.edges[i]) ); 
                        queue.enqueue( (VKey)(curV.edges[i]) ); 
                    }
                }
                
                terminate = (bool)func; //check if we shall stop
            }
        }
        
        //
        // Recursive Version of Depth first Traversal of the ADT Graph
        // See DAPS Chapter 13. Page 698 for discussion (alternatively using stack for non-recursion)
        // a list is maintained to keep track of visited nodes
        template<typename V, typename VKey, typename E>
        template<typename FUNC>
        void Graph<V, VKey, E>::traverse_depth_first(const VKey& curK, FUNC& func, SetASorted<VKey>& visits)
        {
            vset.update(func,curK); //process the current key node
            visits.template insert<VKey>(curK); //mark as visited
            
            //functional object shall impement this to indicate whether 
            //to prematurely terminate the traversal
            if((bool)func)
               return;
            
            //interate down for each edge's end vertice 
            VNode curV;
            vset.retrieve(curK,curV);
            for(int i=0;i<curV.edges.size();i++)
            {
                if( ! visits.exist( (VKey)(curV.edges[i]) ))
                    traverse_depth_first( (VKey)(curV.edges[i]),func,visits);
            }
        }
        
        //================BASIC GRAPH MANIPULATION METHODS=============================
        
        //remove edge functional object 
        namespace graph{
            template<typename V, typename VKey, typename E>
            struct printVE 
            {
                void operator()(const GraphVNode<V,VKey,E>& vtx) 
                {
                    std::cout << vtx.item << std::endl;
                    vtx.edges.print();
                }
            };
        }
        
        template<typename V, typename VKey, typename E>
        void Graph<V, VKey, E>::print() const
        {
            std::cout << "AstemSoft ADT GRAPH: " 
            << vertices() << " vertices " << edges() << " edges " << std::endl;
            
            graph::printVE<V, VKey, E> pve;
            vset.traverse(pve);
            //SetASorted<VKey> visits;
            //Queue<VKey> queue;
            //traverse_breath_first(vset[0], pve, visits, queue);
            //traverse_depth_first((VKey)(vset[0]), pve, visits);
            
            
            std::cout << "END OF AstemSoft ADT GRAPH" << std::endl;
        }
        
        //remove edge functional object 
        namespace graph{
            template<typename V, typename VKey, typename E>
            struct removeE 
            {
                void operator()(GraphVNode<V,VKey,E>& vtx) 
                {
                    //remove edge node matching the end point
                    (vtx.edges).remove(end);
                }
                VKey end;
            };
        }
        template<typename V, typename VKey, typename E>
        void Graph<V, VKey, E>::removeE(const VKey& begin, const VKey& end) throw(GraphException)
        {
            try{
                graph::removeE<V, VKey, E> re;
                re.end = end;
                vset.update(re,begin);//search for begin nod and operate on it
            }
            catch(SetException e)
            {
                throw GraphException(e.what());
            }
            
        }
        
        
        template<typename V, typename VKey, typename E>
        void Graph<V, VKey, E>::retrieveE(const VKey& begin, const VKey& end, E& item) const throw(GraphException)
        {
            try{
                VNode vnode;
                vset.retrieve(begin,vnode);
                ENode enode;
                (vnode.edges).retrieve(end,enode);
                item = enode.item;
            }
            catch(SetException e)
            {
                throw GraphException(e.what());
            }
        }
        
        template<typename V, typename VKey, typename E>
        bool Graph<V, VKey, E>::existE(const VKey& begin, const VKey& end) const
        {
            try{
                VNode vnode;
                vset.retrieve(begin,vnode);
                ENode enode;
                (vnode.edges).retrieve(end,enode);
            }
            catch(SetException e)
            {
                return false;
            }
            
            return true;
        }
        
        //TODO : the functional object must not be defined inside a function
        // otherwise, strange link error occurs while looking for the function 
        //call operator!!
        ////sum up total number of edges during traversal
        namespace graph{
            template<typename V, typename VKey, typename E>
            struct EdgeCounter
            {
                void operator()(const GraphVNode<V,VKey,E>& vtx)
                {
                    count += vtx.edges.size();
                }
                int count;
            };
        }
        template<typename V, typename VKey, typename E>
        int Graph<V, VKey, E>::edges() const
        {
            graph::EdgeCounter<V,VKey,E> ec;
            ec.count = 0;
            vset.traverse(ec);
            return ec.count;
        }
        
        
        //function object for adding outbound edge to a vertice node
        namespace graph{
            template<typename V, typename VKey, typename E>
            struct addE{
                //add an edge node into the new vnode
                void operator()( GraphVNode<V,VKey,E>& vnode)
                {
                    (vnode.edges).template insert<VKey>(enode);
                }
                GraphENode<V,VKey,E> enode;
            };
        }
        template<typename V, typename VKey, typename E>
        void Graph<V, VKey, E>::insertE(const VKey& begin, const VKey& end, const E& item) throw(GraphException)
        {
            graph::addE<V,VKey,E> ae;
            ae.enode.item = item;
            ae.enode.begin = begin;
            ae.enode.end = end;
            
            //update the begin vertice's edge set
            try{
                vset.update(ae,begin);
            }
            catch(SetException e)
            {
                throw GraphException(e.what());
            }
        }
        
        
        ///==========VERTICES BASIC OPERATIONS======================================
        template<typename V, typename VKey, typename E>
        void Graph<V, VKey, E>::removeV(const VKey& key) throw(GraphException)
        {
            try{
                vset.remove(key);
            }
            catch(SetException e)
            {
                throw GraphException(e.what());
            }
        }
        
        template<typename V, typename VKey, typename E>
        void Graph<V, VKey, E>::retrieveV(const VKey&key, V& item) const throw(GraphException)
        {
            try{
                VNode vnode;
                vset.retrieve(key,vnode);
                item = vnode.item;
            }
            catch(SetException e)
            {
                throw GraphException(e.what());
            }
        }
        
        template<typename V, typename VKey, typename E>
        bool Graph<V, VKey, E>::existV(const VKey& key) const
        {
            try{
                VNode vnode;
                vset.retrieve(key,vnode);
            }
            catch(SetException e)
            {
                return false;
            }
            return true;
        }
        
        template<typename V, typename VKey, typename E>
        void Graph<V, VKey, E>::insertV(const V& item) throw(GraphException)
        {
            try{
                VNode node;
                node.item = item;
                vset.template insert<VKey>(node);
            }
            catch(SetException e)
            {
                throw GraphException(e.what());
            }
        }
        
        
    }
}
#endif