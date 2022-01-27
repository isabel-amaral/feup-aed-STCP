#include "LoadData.h"
using namespace std;

LoadData::LoadData(const Graph& buses, const list<LineGraph>& lines): buses(buses),  lines(lines) {
    loadStops();
    loadLines();
    loadLinesInfo();
    this->buses.addWalkingEdges();
}

const Graph& LoadData::getBuses() const {
    return buses;
}

const list<LineGraph>& LoadData::getLines() const {
    return lines;
}

void LoadData::loadStops() {
    ifstream f;
    string code, name, zone, text, tempText;
    double latitude, longitude;

    f.open("stops.csv");

    if (!f.is_open()) {
        cout << "O ficheiro nao existe." << endl;
        return;
    }
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
    string line;
    string code, name;

    f.open("lines.csv");
    if(!f.is_open()) {
        cout << "Ficheiro nao existe" << endl;
        return;
    }

    f.ignore(LONG_MAX, '\n');
    while(!f.eof()) {
        getline(f, code, ',');
        getline(f, name, '\n');
        buses.addLine(code, name);
    }
    f.close();
}

void LoadData::readInfoFromLine(const string& filename, string lineCode, string lineName) {
    ifstream f;
    string numStops;
    f.open(filename);
    if (!f.is_open()) {
        cout << "O ficheiro " << filename << " nao existe." << endl;
        return;
    }
    getline(f, numStops);
    LineGraph line(lineCode, lineName, stoi(numStops));

    int s, d;
    string sourceCode, destCode;
    double distance;

    getline(f, sourceCode);
    string startingStop = sourceCode;
    for (int i = 0; i < stoi(numStops)-1; i++) {
        getline(f, destCode);
        s = buses.getStopsInfo().at(sourceCode);
        d = buses.getStopsInfo().at(destCode);
        distance = Graph::calculateDistance(buses.getStopLatitude(s), buses.getStopLongitude(s),
                                           buses.getStopLatitude(d), buses.getStopLongitude(d));
        buses.addEdge(s, lineCode, distance, d);

        line.setNode(sourceCode, buses.getStopName(s),buses.getStopZone(s),
                     buses.getStopLatitude(s), buses.getStopLongitude(s));
        line.setNode(destCode, buses.getStopName(d),buses.getStopZone(d),
                     buses.getStopLatitude(d), buses.getStopLongitude(d));
        line.addEdge(line.getStopsInfo().at(sourceCode), distance, line.getStopsInfo().at(destCode));

        sourceCode = destCode;
    }

    //circular lines
    if ((lineCode == "300" || lineCode == "301" || lineCode == "302" || lineCode == "303") && stoi(numStops) != 0) {
        s = buses.getStopsInfo().at(sourceCode);
        d = buses.getStopsInfo().at(startingStop);
        distance = Graph::calculateDistance(buses.getStopLatitude(s), buses.getStopLongitude(s),
                                            buses.getStopLatitude(d), buses.getStopLatitude(d));
        buses.addEdge(s, lineCode, distance, d);
        line.setNode(sourceCode, buses.getStopName(s),buses.getStopZone(s),
                     buses.getStopLatitude(s), buses.getStopLongitude(s));
        line.setNode(destCode, buses.getStopName(d),buses.getStopZone(d),
                     buses.getStopLatitude(d), buses.getStopLongitude(d));
        line.addEdge(line.getStopsInfo().at(sourceCode), distance, line.getStopsInfo().at(destCode));
    }
    lines.push_back(line);
}

void LoadData::loadLinesInfo() {
    map<string, string>::const_iterator it;
    for (it = buses.getLinesInfo().begin(); it != buses.getLinesInfo().end(); it++) {
        ostringstream out0, out1;
        out0 << "line_" << it->first << "_0" << ".csv";
        readInfoFromLine(out0.str(), it->first, it->second);
        out1 << "line_" << it->first << "_1" << ".csv";
        readInfoFromLine(out1.str(), it->first, it->second);
    }
}
