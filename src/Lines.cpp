#include "Lines.h"
#include <iostream>

Lines::Lines() {}

void Lines::setBuses(const Graph &buses) {
    this->buses = buses;
}

const list<LineGraph>& Lines::getLines() const {
    return lines;
}

void Lines::setLines(const list<LineGraph> &lines) {
    Lines::lines = lines;
}

void Lines::setWalkingDistance(double walkingDistance) {
    this->walkingDistance = walkingDistance;
}

//time complexity: O(N)
//N: N: nº de paragens da STCP
MinHeap<string, double> Lines::findClosestStops(double latitude, double longitude) {
    list<string> stopCodes;
    list<double> stopDistancesToOrigin;
    vector<string> s = buses.getStops();
    for (int v = 1; v < s.size(); v++) {  //O(N); N: number of stops in STCP
        //calculateDistance(): O(1)
        double distance = buses.calculateDistance(latitude, longitude, buses.getStopLatitude(v), buses.getStopLongitude(v));
        if (distance <= walkingDistance) {
            stopCodes.push_back(buses.getStopCode(v));
            stopDistancesToOrigin.push_back(distance);
        }
    }

    MinHeap<string, double> closestStops(stopCodes.size(), "");
    list<string>::iterator it1 = stopCodes.begin();
    list<double>::iterator it2 = stopDistancesToOrigin.begin();
    for (; it1 != stopCodes.end(); it1++) {  //O(N'); N': number of stops close to the given location (<N)
        closestStops.insert(*it1, *it2);
        it2++;
    }
    return closestStops;
}

//time complexity: O(L) * O(n)
//L: number of lines in STCP
//n: number of stops in line L
LineGraph Lines::findCorrespondingLine(string line, string stopCode) const {
    for (LineGraph l: lines) {  //O(L); L: number of lines in STCP
        if (l.getLineCode() == line) {
            vector<string> stops = l.getStops();
            for (string s: stops) //O(n); n: number of stops in line L
                if (s == stopCode)
                    return l;
        }
    }
}

//time complexity: O(Ns) * O(L) * O(n)
//Ns: number of stops close to starting position
//L: number of lines in STCP
//n: number of stops in line L
void Lines::getShortestPathWithinSameLine(double latitude1, double longitude1, double latitude2, double longitude2) {
    MinHeap<string, double> stopsNearStart = findClosestStops(latitude1, longitude1);  //O(N); N: number of stops in STCP
    MinHeap<string, double> stopsNearEnd = findClosestStops(latitude2, longitude2);   //O(N)
    int countStops;
    double distance = LONG_MAX;
    string fasterLine, startStop;

    while (stopsNearStart.getSize() != 0) {    //O(Ns); Ns: number of stops close to starting position
        string s = stopsNearStart.removeMin(); //O(log Ns)
        list<string> stopLines = buses.getStopLines(s);
        for (string l: stopLines) {
            if (l == "")
                continue;
            //O(L) * O(n) > O(log Ns)
            //L: number of lines in STCP; n: number of stops in line L
            LineGraph currentLine = findCorrespondingLine(l, s);
            //O(n + e) < O(L) * O(n)
            //n: number of stops in the current line; e: number of edges in the current line's graph (number of connections between stops)
            LineGraph::Result result = currentLine.findPathWithinSameLine(stopsNearEnd, currentLine.getStopsInfo().at(s));
            double d = result.distance;
            //walking distance from starting position to first stop
            if (d != LONG_MAX) { //O(1)
                d += Graph::calculateDistance(latitude1, longitude1,
                                              buses.getStopLatitude(buses.getStopsInfo().at(s)),
                                              buses.getStopLongitude(buses.getStopsInfo().at(s)));
                //walking distance from end position to last stop
                d += Graph::calculateDistance(latitude2, longitude2,
                                              buses.getStopLatitude(buses.getStopsInfo().at(result.endStop)),
                                              buses.getStopLongitude(buses.getStopsInfo().at(result.endStop)));
            }
            if (d < distance) {  //O(1)
                distance = d;
                countStops = result.count;
                fasterLine = l;
                startStop = s;
            }
        }
    }
    showShortestPathWithinSameLine(countStops, distance, fasterLine, startStop);
}

void Lines::showShortestPathWithinSameLine(int numStops, double distance, string line, string startStop) const {
    if (distance == LONG_MAX) {
        cout << "Nao foi encontrado nenhum caminho sem mudar de linhas.";
        return;
    }

    LineGraph l = findCorrespondingLine(line, startStop);
    cout << "Apanahe a linha " << l.getLineName() << " (" << line << ")." << endl;
    cout << "Chegara ao seu destino em " << numStops << " paragens." << endl;
    cout << "No total o percurso a percorrer sera de " << distance/1000 << " kilometros." << endl;
    cout << "Direcoes: " << endl << endl;

    vector<string> stops = l.getStops();
    bool foundStartStop = false;
    int count = 0;
    for (string stop: stops) {
        if (count == numStops)
            break;
        if (!foundStartStop) {
            if (stop == startStop) {
                foundStartStop = true;
                cout << "Caminhe ate " << buses.getStopName(buses.getStopsInfo().at(startStop)) << " (" << startStop << ")" << endl;
            }
            else
                continue;
        }
        else
            count++;
        cout << buses.getStopName(buses.getStopsInfo().at(stop)) << " (" << stop << ")." << endl;
    }
    cout << "Caminhe ate ao seu destino." << endl;
}
