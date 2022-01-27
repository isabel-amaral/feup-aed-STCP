#ifndef STCP_LINEGRAPH_H
#define STCP_LINEGRAPH_H

#include "MinHeap.h"
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

//TODO: ver sentidos linhas
class LineGraph {
    string lineCode;
    string lineName;
    struct Edge {
        double weight;
        int dest;
    };

    struct Node {
        string stopCode;
        string stopName;
        string zone;
        double latitude;
        double longitude;
        list<Edge> adj;
        double dist;
        int pred;
        bool visited;
    };

    int n;
    vector<Node> stops;
    map<string, int> stopsInfo;

public:
    LineGraph(const string &lineCode, const string &lineName, int n);
    string getLineCode() const;
    double getStopLatitude(int node) const;
    double getStopLongitude(int node) const;
    const map<string, int>& getStopsInfo() const;
    void setNode(const string& code, const string& name, const string& zone, const double& latitude, const double& longitude);
    void addEdge(int src, double weight, int dest);
    static double calculateDistance(double latitude1, double longitude1, double latitude2, double longitude2);
};

#endif //STCP_LINEGRAPH_H
