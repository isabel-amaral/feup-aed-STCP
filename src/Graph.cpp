#include "Graph.h"

Graph::Graph(int num) : n(num), stops(num+1) {}

void Graph::addEdge(int src, string code, string name, int weight, int dest) {
    if (src < 1 || src > n || dest < 1 || dest > n)
        return;
    stops[src].adj.push_back({code, name, weight, dest});
}
