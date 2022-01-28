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
    buses.setWalkingDistance(50);
    lines.setWalkingDistance(50);

    //feup -> casa: apanhar o 300
    //FEUP2: 41.17910277,-8.598681783
    //MATR1: 41.15138523,-8.621106659
    //lines.getShortestPathWithinSameLine(41.1792000,-8.598682200, 41.15138523,-8.621106659);
    //foz -> feup: apanhar o 204
    //MFZ2: 41.15404794,-8.673866668
    //FEUP1: 41.17883946,-8.598663762
    //lines.getShortestPathWithinSameLine(41.15406000,-8.673867000, 41.17884566,-8.598664000);
    //feup -> póvoa do varzim: não há caminho possível
    //lines.getShortestPathWithinSameLine(41.1792000,-8.598682200, 41.38714064162708, -8.759894741376126);

    //buses.getShortestPathChangingLines(41.15404794,-8.673866668, 41.17883946,-8.598663762);

    return 0;
}