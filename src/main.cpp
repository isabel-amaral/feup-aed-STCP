#include <iostream>
#include "LoadData.h"

using namespace std;
int main() {
    Graph buses(2487);
    list<LineGraph> lines;

    LoadData loadData(buses, lines);
    buses = loadData.getBuses();
    lines = loadData.getLines();
    buses.setWalkingDistance(500);

    buses.getShortestPathChangingLines(41.15404794,-8.673866668, 41.17883946,-8.598663762);
    return 0;
}