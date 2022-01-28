#include <iostream>
#include "Graph.h"
#include "Lines.h"
#include "LoadData.h"
#include "Menu.h"
#include "Graph.h"

using namespace std;
int main() {
    cout << "BEM-VINDO AOS SERVICOS STCP" << endl;
    Menu m = Menu();

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

    //buses.getShortestPathChangingLines(41.15404794,-8.673866668, 41.17883946,-8.598663762);
    //buses.getMinimumStopsPath(41.17986835,-8.588496841, 41.18221828,-8.596427581); // start= enx2, end = asp4;
    //buses.getMinimumStopsPath(41.17672431,-8.620723124, 41.17883946,-8.598663762);// start = bra4, end = feup1 //
    //buses.getMinimumStopsPath(41.22070233,-8.713217906, 41.23691113,-8.670278173);//CBNM2 - AEPT1 (aeroporto)
    //cout << buses.calculateDistance(41.22489589,-8.680421418, 41.22599092,-8.681291011) << endl;//ror2, frx19
    //cout << buses.calculateDistance(41.22487609,-8.680290837, 41.22599092,-8.681291011) << endl;//ror1, frx19
    //cout << buses.calculateDistance(41.22618383,-8.680843002, 41.22599092,-8.681291011);// frxi3, frxi9
    //cout << buses.calculateDistance(41.18041933,-8.622049614, 41.17672431,-8.620723124);
    //buses.getMinimumStopsPath(41.17975194,-8.628611164,41.17190078,-8.616842818); //mst3-mtb3
    //buses.getMinimumStopsPath(41.17933489,-8.651703915, 41.18221828,-8.596427581); //ruela- asprela4

    return 0;
}

