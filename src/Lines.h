#ifndef STCP_LINES_H
#define STCP_LINES_H

#include "Graph.h"
#include "LineGraph.h"
#include <set>

class Lines{
    Graph buses;
    list<LineGraph> lines;
    double walkingDistance;

public:
    Lines();
    const list<LineGraph>& getLines() const;
    void setLines(const list<LineGraph> &lines);
    void setBuses(const Graph &buses);
    void setWalkingDistance(double walkingDistance);
    MinHeap<string, double> findClosestStops(double latitude, double longitude);
    LineGraph findCorrespondingLine(string line, string stopCode) const;

    //TODO
    void getShortestPathWithinSameLine(double latitude1, double longitude1, double latitude2, double longitude2);
    //TODO: cout da distância e do caminho
    void showShortestPathWithinSameLine() const;
};

#endif //STCP_LINES_H
