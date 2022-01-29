#ifndef STCP_MENU_H
#define STCP_MENU_H

#include <iostream>
#include <stack>
#include "Graph.h"
#include "Lines.h"
#include "LoadData.h"

class Menu {
private:
    Graph buses;
    Lines lines;
    stack<int> lastMenu;
    int option;

public:
    Menu();
    void readOption(const unsigned& minOption, const unsigned& maxOption);
    void processOption(double latitude1, double longitude1);
    void menu0();
    void menu1();
    void menu2();
};

#endif //STCP_MENU_H