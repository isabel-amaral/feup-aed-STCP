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

void Lines::getShortestPathWithinSameLine(double latitude1, double longitude1, double latitude2, double longitude2) {
    MinHeap<int, int> closestStops = buses.findClosestStops(latitude1, longitude1);
    //TODO
}

void Lines::showShortestPathWithinSameLine() const {
    //TODO
}
