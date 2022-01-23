#include "LoadData.h"
#include "iostream"
#include "sstream"
#include <fstream>

using namespace std;

Graph LoadData::getBuses() {
    return buses;
}

void LoadData::loadStops() {
    buses = Graph(2487);
    ifstream f;
    string code, name, zone, text, tempText;
    double latitude, longitude;

    f.open("stops.csv");

    if (!f.is_open())
        cout << "O ficheiro nao existe." << endl;
    f.ignore(LONG_MAX, '\n');

    while (getline(f, text)){
        stringstream s(text);
        getline (s, code, ',');
        getline (s, name, ',');
        getline (s, zone, ',');
        getline (s, tempText, ',');
        latitude = stod(tempText);
        getline (s, tempText, ',');
        longitude = stod(tempText);
        buses.setNode(code, name, zone, latitude, longitude);
    }
    f.close();
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

