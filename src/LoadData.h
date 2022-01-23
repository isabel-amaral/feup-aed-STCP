#ifndef STCP_LOADDATA_H
#define STCP_LOADDATA_H

#include "Graph.h"

class LoadData {
private:
    Graph buses;
    void loadStops();
    void loadLines();
    void loadLinesInfo();

public:
    Graph getBuses();
    void loadData();
};

#endif //STCP_LOADDATA_H
