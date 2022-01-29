#include "LineGraph.h"
#include <cmath>
#include <queue>
using namespace std;

LineGraph::LineGraph(const string &lineCode, const string &lineName, int n) :
                        lineCode(lineCode), lineName(lineName), n(n), stops(n+1) {}

string LineGraph::getLineCode() const {
    return lineCode;
}

const string& LineGraph::getLineName() const {
    return lineName;
}

vector<string> LineGraph::getStops() const {
    vector<string> stops;
    for (Node n: this->stops)
        stops.push_back(n.stopCode);
    return stops;
}

const map<string, int>& LineGraph::getStopsInfo() const {
    return stopsInfo;
}

void LineGraph::setNode(const string &code) {
    int nodeIndex = stopsInfo.size() + 1;
    stopsInfo.insert({code,nodeIndex});
    stops.at(nodeIndex).stopCode = code;
}

void LineGraph::addEdge(int src, double weight, int dest) {
    if (src < 1 || src > n || dest < 1 || dest > n)
        return;
    stops[src].adj.push_back({weight, dest});
}

//bfs
LineGraph::Result LineGraph::findPathWithinSameLine(const MinHeap<string, double>& stopsNearEnd, int source) {
    for (Node n: stops)
        n.visited = false;

    bool foundCloseStop = false;
    string lastStopFound;
    int count = 0;
    double distance = 0;
    queue<int> q;
    q.push(source);
    stops[source].visited = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (Edge e: stops[u].adj) {
            if (!stops[e.dest].visited) {
                if (!foundCloseStop && stopsNearEnd.hasKey(stops[e.dest].stopCode)) {
                    foundCloseStop = true;
                    lastStopFound = stops[e.dest].stopCode;
                }
                else if (foundCloseStop) {
                    if (!stopsNearEnd.hasKey(stops[e.dest].stopCode))
                        break;
                    lastStopFound = stops[e.dest].stopCode;
                }
                q.push(e.dest);
                stops[e.dest].visited = true;
                count++;
                distance += e.weight;
            }
        }
    }

    Result result;
    result.count = count;
    if (count >= n - source)
        result.distance = LONG_MAX;
    else
        result.distance = distance;
    result.endStop = lastStopFound;
    return result;
}
