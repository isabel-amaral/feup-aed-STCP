#include "LoadData.h"
using namespace std;

Graph LoadData::getBuses() {
    return buses;
}

void LoadData::loadStops() {
    //TODO
}

void LoadData::loadLines() {
    //TODO
}

void LoadData::loadLinesInfo() {
    //TODO
}

void LoadData::loadData() {
    loadStops();
    loadLines();
    loadLinesInfo();
}

