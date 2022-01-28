#ifndef STCP_LOADDATA_H
#define STCP_LOADDATA_H

#include "Graph.h"
#include "LineGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class LoadData {
private:
    Graph buses;
    list<LineGraph> lines;

    void loadStops();
    void loadLines();
    void loadLinesInfo();
    void readInfoFromLine(const string& filename, string lineCode, string lineName);

public:
    LoadData(const Graph &buses, const list<LineGraph>& lines);
    const Graph& getBuses() const;
    const list<LineGraph>& getLines() const;
};

#endif //STCP_LOADDATA_H
