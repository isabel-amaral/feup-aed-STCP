#include <cmath>
#include <queue>
#include <iostream>
#include "Graph.h"

Graph::Graph() {}

Graph::Graph(int num) : n(num), stops(num+1) {
    this->walkingDistance = 0;
}

vector<string> Graph::getStops() const {
    vector<string> stops;
    for (Node n: this->stops)
        stops.push_back(n.stopCode);
    return stops;
}

string Graph::getStopCode(int node) const {
    return stops[node].stopCode;
}

string Graph::getStopName(int node) const {
    return stops[node].stopName;
}

string Graph::getStopZone(int node) const {
    return stops[node].zone;
}

double Graph::getStopLatitude(int node) const {
    return stops[node].latitude;
}

double Graph::getStopLongitude(int node) const {
    return stops[node].longitude;
}

const map<string, int>& Graph::getStopsInfo() const {
    return stopsInfo;
}

const map<string, string>& Graph::getLinesInfo() const {
    return linesInfo;
}

list<string> Graph::getStopLines(string node) const {
    list<string> lines;
    int index = stopsInfo.at(node);
    for (Edge e: stops[index].adj)
        lines.push_back(e.lineCode);
    return lines;
}

void Graph::setNode(const string &code, const string &name, const string &zone, const double &latitude, const double &longitude) {
    int nodeIndex = stopsInfo.size() + 1;
    stopsInfo.insert({code,nodeIndex});
    stops.at(nodeIndex).stopCode = code;
    stops.at(nodeIndex).stopName = name;
    stops.at(nodeIndex).zone = zone;
    stops.at(nodeIndex).latitude = latitude;
    stops.at(nodeIndex).longitude = longitude;
    stops.at(nodeIndex).longitude = longitude;
}

void Graph::addLine(string code, string name) {
    this->linesInfo.insert({code, name});
}

void Graph::addEdge(int src, string code, double weight, int dest) {
    if (src < 1 || src > n || dest < 1 || dest > n)
        return;
    stops[src].adj.push_back({code, weight, dest});
}

void Graph::setWalkingDistance(double dist) {
    this->walkingDistance = dist;
}

void Graph::addWalkingEdges(){
    int maxDistance = 50;
    for (int i = 1; i < stops.size()-1; i++) {
        for (int s = 1; s < stops.size(); s++) {
            double distance = calculateDistance(stops[i].latitude, stops[i].longitude, stops[s].latitude, stops[s].longitude);
            if (distance <= maxDistance && i != s){
                addEdge(i, "", distance, s);
            }
        }
    }
}

void Graph::addPositionNode(double latitude, double longitude, list<int> closestStops) {
    stops.resize(stops.size()+1);
    stops.back().latitude = latitude;
    stops.back().longitude = longitude;
    n++;
    for (auto aux: closestStops){
        double distance = calculateDistance(latitude, longitude, stops[aux].latitude, stops[aux].longitude);
        addEdge(stops.size()-1, "", distance, aux);
        addEdge(aux, "", distance, stops.size()-1);
    }
}

void Graph::removePositionNode(list<int> closestStops) {
    stops.resize(stops.size()-1);
    n--;
    for (auto aux: closestStops)
        stops[aux].adj.pop_back();
}

double Graph::calculateDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
    double dLat = (latitude2 - latitude1) * M_PI / 180.0;
    double dLon = (longitude2 - longitude1) * M_PI / 180.0;

    latitude1 = (latitude1) * M_PI / 180.0;
    latitude2 = (latitude2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(latitude1) * cos(latitude2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}

void Graph::bfsDistance(int a, int b) {
    queue<int> aux;

    for (int i = 1; i < stops.size(); i++){
        stops[i].visited = false;
        stops[i].pred = -1;
    }
    stops[b].dist = INT_MAX;
    stops[a].dist = 0;
    stops[a].visited = true;
    stops[a].pred = 0;
    aux.push(a);

    while (!aux.empty()) {
        int u = aux.front(); aux.pop();
        for (auto e : stops[u]. adj) {
            int w = e.dest;
            if (!stops[w].visited) { // novo no
                aux.push(w);
                stops[w].visited = true;
                stops[w].dist = stops[u].dist + 1;
                stops[w].pred = u;
            }
        }
    }
}

void Graph::bfsZone(int a, int b) {
    queue<int> aux;

    for (int i = 1; i < stops.size(); i++){
        stops[i].visited = false;
        stops[i].pred = -1;
    }
    stops[b].numZones = INT_MAX;
    stops[a].numZones = 0;
    stops[a].visited = true;
    stops[a].pred = 0;
    aux.push(a);

    while (!aux.empty()) {
        int u = aux.front(); aux.pop();
        for (auto e : stops[u]. adj) {
            int w = e.dest;
            if (!stops[w].visited) {
                if (stops[w].zone == stops[u].zone) stops[w].numZones = stops[u].numZones;
                else stops[w].numZones = stops[u].numZones + 1;
                stops[w].visited = true;
                stops[w].pred = u;
                aux.push(w);
            }
        }
    }
}

void Graph::getMinimumStopsPath(double latitude1, double longitude1, double latitude2, double longitude2) {
    list<int> stopsNearStart = findClosestStops(latitude1, longitude1);
    list<int> stopsNearEnd = findClosestStops(latitude2, longitude2);
    vector<int> result;
    int lastMinDist = INT_MAX, start = 0, end = 0;

    for (auto i: stopsNearStart) {
        for (auto j: stopsNearEnd){
            bfsDistance(i, j);
            if (stops[j].visited && stops[j].dist < lastMinDist){
                lastMinDist = stops[j].dist;
                start = i;
                end = j;
            }
        }
    }

    double distance1 = 0, distance2 = 0;
    if (start == 0 && end == 0){    // Se foi encontrado um caminho
        showMinimumStopsPath(result, distance1, distance2);
        return;
    }
    bfsDistance(start, end);
    result.insert(result.begin(), end);
    int parent = stops.at(end).pred;
    while (parent != 0) {  // Enquanto não chegar a paragem inicial que é a única que possui parent = 0
        result.insert(result.begin(), parent);
        parent = stops.at(parent).pred;
    }


    if (!result.empty()){
        distance1 = calculateDistance(latitude1, longitude1, getStopLatitude(result.front()), getStopLongitude(result.front()));
        distance2 = calculateDistance(latitude2, longitude2, getStopLatitude(result.back()), getStopLongitude(result.back()));
    }
    showMinimumStopsPath(result, distance1, distance2);

}

void Graph::showMinimumStopsPath(vector<int> path, double distance1, double distance2) const {
    if (path.empty()){
        cout << "Nao foi encontrado nenhum caminho." << endl;
        return;
    }
    cout << "\nEste caminho passa por um total de " << stops[path.back()].dist + 1 << " paragens." << endl;
    showPath(path, distance1, distance2);
}

list<int> Graph::findClosestStops(double latitude, double longitude) {
    list<int> closestStops;
    for (int v = 1; v < stops.size(); v++) {
        stops[v].visited = false;
        if (calculateDistance(latitude, longitude, stops[v].latitude, stops[v].longitude) <= walkingDistance) {
            stops[v].dist = calculateDistance(latitude, longitude, stops[v].latitude, stops[v].longitude);
            closestStops.push_back(v);
        }
        else
            stops[v].dist = LONG_MAX;
    }
    return closestStops;
}

void Graph::getShortestPathChangingLines(double latitude1, double longitude1, double latitude2, double longitude2) {
    list<int> stopsNearStart = findClosestStops(latitude1, longitude1);
    list<int> stopsNearEnd = findClosestStops(latitude2, longitude2);
    addPositionNode(latitude1, longitude1, stopsNearStart);
    addPositionNode(latitude2, longitude2, stopsNearEnd);
    MinHeap<int, double> visitedStops(stops.size(), -1);

    for (int i = 1; i < stops.size(); i++) {
        stops[i].visited = false;
        stops[i].dist = INT_MAX;
        stops[i].pred = -1;
    }

    int originIndex = stops.size() - 2;
    int destinationIndex = stops.size() - 1;
    stops[originIndex].dist = 0;
    stops[originIndex].pred = originIndex;
    visitedStops.insert(originIndex, stops[originIndex].dist);

    while (visitedStops.getSize() > 0) {
        int u = visitedStops.removeMin();
        stops[u].visited = true;
        for (const Edge &e: stops[u].adj) {
            int v = e.dest;
            double w = e.weight;
            double newDist = stops[u].dist + w;

            if (!stops[v].visited) {
                stops[v].pred = u;
                stops[v].dist = newDist;
                stops[v].visited = true;
                visitedStops.insert(v, newDist);
            } else if (newDist < stops[v].dist) {
                stops[v].pred = u;
                stops[v].dist = newDist;
                visitedStops.decreaseKey(v, newDist);
            }
        }
    }

    vector<int> path;
    if (stops[destinationIndex].visited) {
        int parent = stops[destinationIndex].pred;
        while (parent != originIndex) {
            path.insert(path.begin(), parent);
            parent = stops[parent].pred;
        }
    }
    removePositionNode(stopsNearEnd);
    removePositionNode(stopsNearStart);
    double distance1, distance2;
    if (!path.empty()){
        distance1 = stops[path.front()].dist;
        distance2 = calculateDistance(latitude2, longitude2, getStopLatitude(path.back()), getStopLongitude(path.back()));
    }
    showShortestPathChangingLines(path, distance1, distance2);
}

void Graph::showShortestPathChangingLines(vector<int> path, double distance1, double distance2) const {
    if (path.empty()){
        cout << "Nao foi encontrado nenhum caminho." << endl;
        return;
    }
    cout << "\nEste caminho percorre um total de " << stops[path.back()].dist + distance2 << " metros." << endl;
    showPath(path, distance1, distance2);
}

void Graph::getLowestZoneChanges(double latitude1, double longitude1, double latitude2, double longitude2) {
    list<int> stopsNearStart = findClosestStops(latitude1, longitude1);
    list<int> stopsNearEnd = findClosestStops(latitude2, longitude2);
    addPositionNode(latitude1, longitude1, stopsNearStart);
    addPositionNode(latitude2, longitude2, stopsNearEnd);
    int originIndex = stops.size() - 2;
    int destinationIndex = stops.size() - 1;
    vector<int> path;

    bfsZone(originIndex, destinationIndex);

    if (stops[destinationIndex].visited) {
        int parent = stops[destinationIndex].pred;
        while (parent != originIndex) {
            path.insert(path.begin(), parent);
            parent = stops[parent].pred;
        }
    }
    removePositionNode(stopsNearEnd);
    removePositionNode(stopsNearStart);
    double distance1, distance2;
    if (!path.empty()){
        distance1 = calculateDistance(latitude1, longitude1, getStopLatitude(path.front()), getStopLongitude(path.front()));
        distance2 = calculateDistance(latitude2, longitude2, getStopLatitude(path.back()), getStopLongitude(path.back()));
    }
    showLowestZoneChanges(path, distance1, distance2);
}

void Graph::showLowestZoneChanges(vector<int> path, double distance1, double distance2) const {
    if (path.empty()){
        cout << "Nao foi encontrado nenhum caminho." << endl;
        return;
    }
    cout << "\nEste caminho passa por um total de" << stops[path.back()].numZones << " zona(s)." << endl;
    showPath(path, distance1, distance2);
}

void Graph::showPath(vector<int> path, double distance1, double distance2) const {
    int lastStop = path.back();
    string lastLine = "0";

    cout << "Caminhe " << distance1 << " metros ate " << stops[path.front()].stopCode << "-" << stops[path.front()].stopName << endl << endl;
    for (auto i = 0; i < path.size() -1; i++) {
        int index = path[i];
        for (const auto& ad : stops[index].adj){
            if (ad.dest != path[i+1])
                continue;
            string line = ad.lineCode;
            if (!line.empty()) {
                if (line != lastLine){
                    if (index != path.front()){
                        cout << lastLine << "-" << stops[index].stopName << " (" << stops[index].stopCode << ")" << " - " << stops[index].zone << endl << endl;
                        cout << "Descer em " << stops[index].stopName << " (" << stops[index].stopCode << ")" << endl;
                    }
                    cout << "Esperar pela linha " << line << endl << endl;
                    lastLine = line;
                }
                cout << line << "-" << stops[index].stopName << " (" << stops[index].stopCode << ")" << " - " << stops[index].zone << endl;
                break;
            }
            else {
                int nextStop = path[i+1];
                cout << lastLine << "-" << stops[index].stopName << " (" << stops[index].stopCode << ")" << " - " << stops[index].zone << endl << endl;
                cout << "Caminhe ate " << stops[nextStop].stopName << " (" << stops[nextStop].stopCode << ")" << endl << endl;
                break;
            }
        }
    }

    cout << lastLine << "-" << stops[lastStop].stopName << " (" << stops[lastStop].stopCode << ")" << " - " << stops[lastStop].zone << endl << endl;
    cout << "Descer em " << stops[lastStop].stopName << " (" << stops[lastStop].stopCode << ")" << endl;
    cout << "Caminhe " << distance2 << " metros ate ao seu destino." << endl;
}





