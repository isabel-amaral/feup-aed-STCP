#include "Lines.h"

Lines::Lines() {}

void Lines::setBuses(const Graph &buses) {
    this->buses = buses;
}

const list<LineGraph>& Lines::getLines() const {
    return lines;
}

void Lines::setLines(const list<LineGraph> &lines) {
    Lines::lines = lines;
}

void Lines::setWalkingDistance(double walkingDistance) {
    this->walkingDistance = walkingDistance;
}

MinHeap<string, double> Lines::findClosestStops(double latitude, double longitude) {
    MinHeap<string, double> closestStops(buses.getStops().size(), "");
    for (int v = 1; v < buses.getStops().size(); v++) {
        double distance = buses.calculateDistance(latitude, longitude, buses.getStopLatitude(v), buses.getStopLongitude(v));
        if (distance <= walkingDistance)
            closestStops.insert(buses.getStopCode(v), distance);
    }
}

LineGraph Lines::findCorrespondingLine(string line, string stopCode) const {
    for (LineGraph l: lines) {
        if (l.getLineCode() == line) {
            vector<string> stops;
            for (string s: stops)
                if (s == stopCode)
                    return l;
        }
    }
}

void Lines::getShortestPathWithinSameLine(double latitude1, double longitude1, double latitude2, double longitude2) {
    MinHeap<string, double> stopsNearStart = findClosestStops(latitude1, longitude1);
    MinHeap<string , double> stopsNearEnd = findClosestStops(latitude2, longitude2);
    int countStops = INT_MAX;
    string fasterLine;

    while (stopsNearStart.getSize() != 0) {
        string s = stopsNearStart.removeMin();
        list<string> stopLines = buses.getStopLines(s);
        for (string l: stopLines) {
            LineGraph currentLine = findCorrespondingLine(l, s);
            int count = currentLine.findPath(stopsNearEnd, currentLine.getStopsInfo().at(s));
            if (count < countStops) {
                countStops = count;
                fasterLine = l;
            }
        }
    }
}

void Lines::showShortestPathWithinSameLine() const {
    //TODO
}
