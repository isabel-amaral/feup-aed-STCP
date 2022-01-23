#include <cmath>
#include "Graph.h"

Graph::Graph(int num) : n(num), stops(num+1) {}

double Graph::getStopLatitude(int node) const {
    return stops[node].latitude;
}

double Graph::getStopLongitude(int node) const {
    return stops[node].longitude;
}

const map<string, int>& Graph::getStopsInfo() const {
    return stopsInfo;
}

const map<string, string>& Graph::getLinesInfo() const {
    return linesInfo;
}

void Graph::setNode(const string &code, const string &name, const string &zone, const double &latitude, const double &longitude) {
    int nodeIndex = stopsInfo.size() + 1;
    stopsInfo.insert({code,nodeIndex});
    stops.at(nodeIndex).stopCode = code;
    stops.at(nodeIndex).stopName = name;
    stops.at(nodeIndex).zone = zone;
    stops.at(nodeIndex).latitude = latitude;
    stops.at(nodeIndex).longitude = longitude;
}

void Graph::addLine(string code, string name) {
    this->linesInfo.insert({code, name});
}

void Graph::addEdge(int src, string code, double weight, int dest) {
    if (src < 1 || src > n || dest < 1 || dest > n)
        return;
    stops[src].adj.push_back({code, weight, dest});
}

double Graph::calculateDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
    double dLat = (latitude2 - latitude1) * M_PI / 180.0;
    double dLon = (longitude2 - longitude1) * M_PI / 180.0;

    latitude1 = (latitude1) * M_PI / 180.0;
    latitude2 = (latitude2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(latitude1) * cos(latitude2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void Graph::getMinimumStopsPath(double latitude, double longitude) {
    //TODO
    showMinimumStopsPath();
}

void Graph::showMinimumStopsPath() const {
    //TODO
}

void Graph::getShortestPathWithinSameLine(double latitude, double longitude) {
    //TODO
    showShortestPathWithinSameLine();
}

void Graph::showShortestPathWithinSameLine() const {

}

void Graph::getShortestPathChangingLines(double latitude, double longitude) {
    //TODO
    showShortestPathChangingLines();
}

void Graph::showShortestPathChangingLines() const {

}

void Graph::getLowestLineChanges(double latitude, double longitude) {
    //TODO
    showLowestLineChanges();
}

void Graph::showLowestLineChanges() const {

}