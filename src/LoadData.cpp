#include "LoadData.h"
#include "iostream"
#include "sstream"
#include <fstream>

using namespace std;

Graph LoadData::getBuses() {
    return buses;
}

void LoadData::loadStops() {
    //TODO
}

void LoadData::loadLines() {
    ifstream f;
    istringstream iss;
    string line;
    string code, name;

    f.open("lines.csv");
    if(!f.is_open())
        cout << "Ficheiro nao existe" << endl;

    f.ignore(LONG_MAX, '\n');
    while(!f.eof()) {
        getline(f, code, ',');
        getline(f, name, '\n');
        buses.addLine(code, name);
    }

    f.close();
}

void LoadData::loadLinesInfo() {
    //TODO
}

void LoadData::loadData() {
    loadStops();
    loadLines();
    loadLinesInfo();
}

