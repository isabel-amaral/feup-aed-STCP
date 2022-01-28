#include "LineGraph.h"
#include <cmath>
#include <queue>
using namespace std;

LineGraph::LineGraph(const string &lineCode, const string &lineName, int n) :
                        lineCode(lineCode), lineName(lineName), n(n), stops(n+1) {}

string LineGraph::getLineCode() const {
    return lineCode;
}

const vector<string>& LineGraph::getStops() const {
    vector<string> stops;
    for (Node n: this->stops)
        stops.push_back(n.stopCode);
    return stops;
}

double LineGraph::getStopLatitude(int node) const {
    return this->stops[node].latitude;
}

double LineGraph::getStopLongitude(int node) const {
    return this->stops[node].longitude;
}

const map<string, int>& LineGraph::getStopsInfo() const {
    return stopsInfo;
}

void LineGraph::setNode(const string &code, const string &name, const string &zone, const double &latitude, const double &longitude) {
    int nodeIndex = stopsInfo.size() + 1;
    stopsInfo.insert({code,nodeIndex});
    stops.at(nodeIndex).stopCode = code;
    stops.at(nodeIndex).stopName = name;
    stops.at(nodeIndex).zone = zone;
    stops.at(nodeIndex).latitude = latitude;
    stops.at(nodeIndex).longitude = longitude;
}

void LineGraph::addEdge(int src, double weight, int dest) {
    if (src < 1 || src > n || dest < 1 || dest > n)
        return;
    stops[src].adj.push_back({weight, dest});
}

double LineGraph::calculateDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
    double dLat = (latitude2 - latitude1) * M_PI / 180.0;
    double dLon = (longitude2 - longitude1) * M_PI / 180.0;

    latitude1 = (latitude1) * M_PI / 180.0;
    latitude2 = (latitude2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(latitude1) * cos(latitude2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}

//bfs
int LineGraph::findPath(const MinHeap<string, double>& stopsNearEnd, int source) {
    for (Node n: stops)
        n.visited = false;

    bool foundCloseStop = false;
    int count = 0;
    queue<int> q;
    q.push(source);
    stops[source].visited = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (Edge e: stops[u].adj) {
            if (!stops[e.dest].visited) {
                if (!foundCloseStop && stopsNearEnd.hasKey(stops[e.dest].stopCode))
                        foundCloseStop = true;
                else if (foundCloseStop && !stopsNearEnd.hasKey(stops[e.dest].stopCode))
                    break;
                q.push(e.dest);
                stops[e.dest].visited = true;
                count++;
            }
        }
    }
    return count;
}