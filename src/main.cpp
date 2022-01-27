#include <iostream>
#include "Graph.h"
#include "Lines.h"
#include "LoadData.h"

using namespace std;
int main() {
    Graph buses(2487);
    Lines lines;

    LoadData loadData(buses, lines.getLines());
    buses = loadData.getBuses();
    lines.setLines(loadData.getLines());
    lines.setBuses(buses);
    buses.setWalkingDistance(500);
    lines.setWalkingDistance(500);

    buses.getShortestPathChangingLines(41.15404794,-8.673866668, 41.17883946,-8.598663762);
    return 0;
}