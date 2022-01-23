#include <iostream>
#include "LoadData.h"

using namespace std;
int main() {
    Graph graph(2487);
    LoadData loadData(graph);
    loadData.loadData();
    return 0;
}
