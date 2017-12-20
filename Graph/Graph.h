#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <functional>


namespace gdwg {

    template <typename N, typename E> 
    class Graph {

    public:
        //default graph, initialise the empty garph
        Graph(){}
        
        //destructor of the graph
        ~Graph(){clear();}

        Graph(const Graph &graph); //copy constructor  
        Graph(Graph &&graph); //move constructor       

        Graph& operator=(const Graph &g); //copy assignment operator    
        Graph& operator=(Graph &&graph); //move assignment operator    

        bool addNode(const N& val); //add node       
        bool addEdge(const N& src, const N& dst, const E& w); // add egde  

        bool replace(const N& oldData, const N& newData); // replace function      
        void mergeReplace(const N& oldData, const N& newData);  //merge replace function

        void deleteNode(const N& node) noexcept;
        void deleteEdge(const N& src, const N& dst, const E& w) noexcept;

        bool isNode(const N& val) const;
        bool isConnected(const N& src, const N& dst) const;

        void clear() noexcept;
        void printNodes() const;
        void printEdges(const N& val) const;

        //fake iterator----------------
        void begin() const;
        bool end() const;
        void next() const;
        const N& value() const;
        

    private:
        
        struct Edge;
         
        struct Node
        {
            //the value of the node
            N val;
            //a vector of shared pointer of outgoing edges, all edges' from node is the current not
            std::vector<std::shared_ptr<Edge>> edges;

            //node construtor
            Node(){}
            Node(const N& v) {
                val = v;                
            }

            //node destructor
            ~Node(){edges.clear();}
         
        };

        struct Edge 
        {
            //from and to node as the weak pointer, before we access it we have to check the expierd and lock()
            std::weak_ptr<Node> from;
            std::weak_ptr<Node> to;
            //weight of the edge
            E weight;

            //constructor
            Edge(){}
            Edge(std::shared_ptr<Node> fr, std::shared_ptr<Node> t, E we){
                weight = we;
                from = fr;
                to = t;
            }
            
            //destructor
            ~Edge(){
                from.reset();
                to.reset();
            }

        };
        //the graph is a vector of shared pointer node list
        std::vector<std::shared_ptr<Node>> nodeList;
        //a helper funtion to find the node and return its reference
        auto getNode(const N& val) const -> decltype(nodeList.begin());
        //a mutable vector iterator to implement the fake iterator
        mutable typename std::vector<std::shared_ptr<Node>>::const_iterator graphIt;
        
    };

    #include "Graph.tem"
}
#endif
