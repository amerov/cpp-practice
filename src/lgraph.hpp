//
//  lgraph.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-24.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_lgraph_hpp
#define cpp_practice_lgraph_hpp

#include "alist.hpp"


/**
  Adjacent list implementation of ADT Directed Graph
 
  Vertices are stored in a vertice array  O(V)
  Eadh vertice correspond to a link list of outgoing edges  O(E)

 
  
  Suitable for space graph where |V| is significantly smaller than |E|
 
  - fast for accessing outgoing edges / reachable neighbors
  - slow for checking edge existence 
 
 
  Space Complexity - O(|V| + |E|)
 
 
 
 **/
namespace dennycd {
        
    /**
     D - element data type
     **/ 
    template<class D>
    class LGraph {
    public:
        
        
        typedef std::function<void(D srcV, D dstV, float w)> TraverseFunc;
        
        //edge
        struct GEdge {
            int vertice; //destination vertice
            float weight;
            GEdge(int v, float w = 0) : vertice(v), weight(w){}
            GEdge() : vertice(-1), weight(0){}
            
            bool operator==(const GEdge& e){
                return (vertice==e.vertice);
            }
        };
        
        //vertice
        struct GVertice {
            D data; //vertice data item
            AList<GEdge> edges; //a link list of vertice's outgoing edges
            GVertice(){}
            
            GVertice(const D& d) : data(d){}
            
            bool operator==(const D& v){
                return v == data;
            }
        };
        
    public:
        LGraph(){}
        ~LGraph(){}
        
        
        template<class DD>
        friend std::ostream& operator<<(std::ostream& oss, const LGraph<DD>& graph);
        
        void traverse(TraverseFunc func) const;
        bool insertV(const D& data);
        bool insertE(const D& srcV, const D& dstV, float weight);
        bool removeV(const D& key);
        bool removeE(const D& srcV, const D& dstV);        
        void neighbours(const D& key, AList<D>& neighbors);
        
    private:
        
        AList<GVertice> m_V; //a list of vertices 
    };
    
    template<class D>
    void LGraph<D>::traverse(TraverseFunc func) const {
        
        
        for(int i=0;i<m_V.size();i++){
            
            const GVertice& v = m_V.get(i);
            
            for(int j=0;j< v.edges.size();j++){
                D dstD = m_V.get( v.edges.get(j).vertice ).data;
                D srcD = v.data;
                float w = v.edges.get(j).weight; 
                func(srcD, dstD, w);
            }
        }
    }
    
    
    
    //query for all neighbor nodes adjacent to a vertex
    //assume constnat access to the vertice, '
    //worst case takes O(|V|) to copy all neighbors 
    template<class D>
    void LGraph<D>::neighbours(const D& key, AList<D>& neighbors){
        
        //assume constatnt time for locating the vertex
        int idx = m_V.find(key);
        assert(idx >= 0);
        
        //simply retrieve everythinig
        //O(|V|) in worst cases for a complete - fully connected graph
        int e = m_V[idx].size();
        for(int i=0;i<e;i++)
            neighbors.insert(0, m_V[idx][i]);

    }

    
    
    //assume constant access to find src and dst node
    //worst case takes O(|E|) for locating the edge and delete it
    // note that |E| may be far larger than |V| in cases mutlitple edges exist between two nodes
    //therefore the removal operation actually is bounded by |E| !!
    template<class D>
    bool LGraph<D>::removeE(const D& srcV, const D& dstV){
        //locate src vertice
        int idx = m_V.find(srcV);
        assert(idx>=0);
        
        int dstIdx = m_V.find(dstV);
        assert(dstIdx>=0);
        
        
        //removal taks O(|E|) 
        int eIdx = m_V[idx].edges.find(GEdge(dstIdx));
        assert(eIdx>=0);
        m_V[idx].edges.remove(eIdx);
        
        return true;
    }
    
    
    /**
      removeal 
     
      assume constant time f or locating the vertice 
      assume constant time for deleting the vertice entry 
     
       however, we will need to traversel all edges to remote  all edges linking to this node
        - all edges linking to this node 
        - all edges linking from this node
     
     **/
    template<class D>
    bool LGraph<D>::removeV(const D& key){
        
        //all outgoing edges are removed
        int idx = m_V.find(key);
        assert(idx>=0);
        m_V.remove(idx);
        
        for(int i=0;i<m_V.size();i++){
            for(int j=0; j < m_V[i].edges.size();j++){
                if(m_V[i].edges[j].vertice == idx){
                    m_V[i].edges.remove(j);
                    j--;
                }
            }
        }
        
        return true;
    }
    
    //runtime O(1) - assume
    //  constant time to locate the vertice - via index acess / or hash table imp of the vertice list
    //  constatnt time to add the edge (e.g. by appending to tail)
    ////insert an edge from srcV to dstV with weigth
    template<class D>
    bool LGraph<D>::insertE(const D& srcV, const D& dstV, float weight){
        
        //locate the src vertice
        int idx = m_V.find(srcV);
        assert(idx>=0);
        
        //add the edge
        m_V[idx].edges.insert((int)m_V[idx].edges.size(), GEdge(dstV, weight));
        return true;
    }

    //runtime O(1) - we simply add to the tail of the vertice list
    //insert a new vertice with its data (as key as well)
    template<class D>
    bool LGraph<D>::insertV(const D& data){
         m_V.insert((int)m_V.size(), GVertice(data));
        return true;
    }
    
    template<class DD>
    std::ostream& operator<<(std::ostream& oss, const LGraph<DD>& graph){
        oss << "{";
        graph.traverse([&](DD src, DD dst, float w){
            oss << "[" << src << "==>" << dst << "]" << "(" << w << ")";
        });
        oss << "}";
        return oss;
    }
}

#endif
