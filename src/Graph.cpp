#include <cmath>
#include <queue>
#include <iostream>
#include "Graph.h"
#include "MinHeap.h"

Graph::Graph() {
    this->n = 0;
    this->stops = vector<Node>();
    this->stopsInfo.empty();
    this->linesInfo.empty();
    this->walkingDistance = 0;
}

Graph::Graph(int num) : n(num), stops(num+1) {
    this->walkingDistance = 0;
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

void Graph::setNode(const string &code, const string &name, const string &zone, const double &latitude, const double &longitude) {
    int nodeIndex = stopsInfo.size() + 1;
    Node stop;
    stop.stopCode = code;
    stop.stopName = name;
    stop.zone = zone;
    stop.latitude = latitude;
    stop.longitude = longitude;
    stops.push_back(stop);
    stopsInfo.insert({code, nodeIndex});
    /*
    stopsInfo.insert({code,nodeIndex});
    stops.at(nodeIndex).stopCode = code;
    stops.at(nodeIndex).stopName = name;
    stops.at(nodeIndex).zone = zone;
    stops.at(nodeIndex).latitude = latitude;
    stops.at(nodeIndex).longitude = longitude; */
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

void Graph::addPositionNode(double latitude, double longitude, list <int> closestStops) {
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

void Graph::removePositionNode(list <int> closestStops) {
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

void Graph::getMinimumStopsPath(double latitude1, double longitude1, double latitude2, double longitude2) {
    list <int> stopsNearStart = findClosestStops(latitude1, longitude1);
    list <int> stopsNearEnd = findClosestStops(latitude2, longitude2);
    vector<int> result;
    int lastMinDist = INT_MAX, start = 0, end = 0;

    for (auto i: stopsNearStart) {
        for (auto j: stopsNearEnd){
            bfs(i, j);
            if (stops[j].visited && stops[j].dist < lastMinDist){
                lastMinDist = stops[j].dist;
                start = i;
                end = j;
            }
        }
    }

    if (start == 0 && end == 0) showMinimumStopsPath(result); // Se não foi encontrado um caminho

    bfs(start, end);
    result.insert(result.begin(),end);
    int parent = stops.at(end).pred;
    while (parent != 0) {                                          // Enquanto não chegar a paragem inicial que é a única que possui parent = 0
        result.insert(result.begin(), parent);
        parent = stops.at(parent).pred;
    }
    showMinimumStopsPath(result);
}

void Graph::showMinimumStopsPath(vector<int> path) const {
    int lastStop = path.back();
    string lastLineBeforeWalking;

    if (!path.empty()){
        cout << "Caminhe ate " << stops[path.front()].stopCode << "-" << stops[path.front()].stopName << endl << endl;
        for (auto i = 0; i < path.size() -1; i++ ){
            int index = path[i];
            for (const auto& ad : stops[index].adj){
                if(ad.dest == path[i+1]){
                    if(!ad.lineCode.empty()){
                        cout << ad.lineCode << "-" << stops[index].stopName << " (" << stops[index].stopCode << ")" << endl;
                        lastLineBeforeWalking = ad.lineCode;
                        break;
                    }

                    else{
                        int nextStop = path[i+1];
                        cout << lastLineBeforeWalking << "-" << stops[index].stopName << " (" << stops[index].stopCode << ")" << endl << endl;
                        cout << "Caminhe ate " << stops[nextStop].stopName << " (" << stops[nextStop].stopCode << ")" << endl << endl;
                        break;
                    }
                }
            }
        }

        cout << lastLineBeforeWalking << "-" << stops[lastStop].stopName << " (" << stops[lastStop].stopCode << ")" << endl;
        cout << "Caminhe ate ao seu destino" << endl;
    }
}

void Graph::getShortestPathWithinSameLine(double latitude, double longitude) {
    //TODO
    showShortestPathWithinSameLine();
}

void Graph::showShortestPathWithinSameLine() const {

}

list<int> Graph::findClosestStops(double latitude, double longitude) {
    list<int> closestStops;
    for(int v = 1; v < stops.size(); v++) {
        stops[v].visited = false;
        if(calculateDistance(latitude, longitude, stops[v].latitude, stops[v].longitude) <= walkingDistance) {
            stops[v].dist = calculateDistance(latitude, longitude, stops[v].latitude, stops[v].longitude);
            closestStops.push_back(v);
        }
        else {
            stops[v].dist = LONG_MAX;
        }
    }
    return closestStops;
}

int Graph::findClosestStop(double latitude, double longitude) {
    double minDistance = LONG_MAX;
    int closestStopIndex;
    for(int v = 1; v < stops.size(); v++) {
        double distance = calculateDistance(latitude, longitude, stops[v].latitude, stops[v].longitude);
        if(distance < minDistance) {
            minDistance = distance;
            closestStopIndex = v + 1;
        }
    }
    return closestStopIndex;
}

void Graph::getShortestPathChangingLines(double latitude1, double longitude1, double latitude2, double longitude2) {
    list <int> stopsNearStart = findClosestStops(latitude1, longitude1);
    list <int> stopsNearEnd = findClosestStops(latitude2, longitude2);
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
        path.insert(path.begin(), parent);

        while (parent != originIndex) {
            parent = stops[parent].pred;
            path.insert(path.begin(), parent);
        }
    }
    removePositionNode(stopsNearEnd);
    removePositionNode(stopsNearStart);
    showMinimumStopsPath(path);
}

void Graph::showShortestPathChangingLines(list<int> path) const {
    for (auto p: path){
        cout << stops[p].stopCode << "-" << stops[p].stopName<<endl;
    }
}

void Graph::getLowestLineChanges(double latitude, double longitude) {
    //TODO
    showLowestLineChanges();
}

void Graph::showLowestLineChanges() const {

}

void Graph::bfs(int a, int b) {
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

    while (!aux.empty()) { // while there are still unprocessed nodes
        int u = aux.front(); aux.pop(); // remove first element of q
        for (auto e : stops[u]. adj) {
            int w = e.dest;
            if (!stops[w].visited) { // new node!
                aux.push(w);
                stops[w].visited = true;
                stops[w].dist = stops[u].dist + 1;
                stops[w].pred = u;
            }
        }
    }
}




