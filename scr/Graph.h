#ifndef STCP_GRAPH_H
#define STCP_GRAPH_H

class Graph {
    struct Edge {
        int dest;   //Destination node
        int weight; //An integer weight
    };

    struct Node {
        list <Edge> adj; //The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        string name;
    };

    int n;               //Graph size (vertices are numbered from 1 to n)
    bool hasDir;         //false: undirected; true: directed
    vector <Node> nodes; //The list of nodes being represented

public:
    //Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);
    //Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);
}

#endif //STCP_GRAPH_H
