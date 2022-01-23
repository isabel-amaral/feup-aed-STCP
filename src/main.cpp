#include <iostream>
#include "LoadData.h"

using namespace std;
int main() {
    Graph buses(2487);
    LoadData loadData(buses);
    buses = loadData.getBuses();
    return 0;
}
