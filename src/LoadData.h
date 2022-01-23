#ifndef STCP_LOADDATA_H
#define STCP_LOADDATA_H

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class LoadData {
private:
    Graph buses;
    void loadStops();
    void loadLines();
    void loadLinesInfo();
    void readInfoFromLine(const string& filename, string lineCode);

public:
    LoadData(const Graph &buses);

    Graph getBuses();
    void loadData();
};

#endif //STCP_LOADDATA_H
