#include "menu.h"

Menu::Menu() {
    option = 0;
    LoadData loader(buses);
    lastMenu.push(0);   //'0' representa o menu inicial/principal
    menu0();
}

void Menu::readOption(const unsigned& minOption, const unsigned& maxOption) {
    bool validOption;
    do {
        cin >> option;
        if (cin.fail()) {
            if (cin.eof()) {
                cout << "VOLTE SEMPRE." << endl;
                exit (1);
            }
            else {
                validOption = false;
                cout << "OPCAO INVALIDA! TENTE NOVAMENTE" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        else if ((minOption <= option &&  option <= maxOption) || option == 0) {
            validOption = true;
            cin.ignore(1000, '\n');
        }
        else {  // O utilizador introduziu um inteiro invalido
            validOption = false;
            cout << "OPCAO INVALIDA! TENTE NOVAMENTE. " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (!validOption);
}

void Menu::processOption(double latitude1, double longitude1) {
    switch (option) {
        case 0: menu0(); break;
        case 1: menu1(latitude1, longitude1); break;
        case 2: menu2(latitude1, longitude1); break;
    }
}

void Menu::menu0() {
    double latitude1, longitude1;

    cout << "1. Visualizar paragens perto de si" << endl;
    cout << "2. Visualizar percursos" << endl;
    cout << "0. Sair." << endl;
    cout << "\nESCOLHA UMA OPCAO:";
    readOption(0, 2);

    if (option) {
        lastMenu.push(0);
        processOption(latitude1, longitude1);
    }
    else {
        cout << "VOLTE SEMPRE.";
        exit (0);
    }
}

void Menu::menu1(double latitude1, double longitude1) {
    cout << "Indique a latitude a que se encontra: " << endl;
    cin >> latitude1;
    cout << "Indique a longitude a que se encontra: " << endl;
    cin >> longitude1;

    MinHeap<int, int> closestStops = buses.findClosestStops(latitude1, longitude1);

    cout << "Encontra-se a:" << endl;

    for (int i = 0; i < closestStops.getSize(); i++) {

    }

    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption(latitude1, longitude1);
}

void Menu::menu2(double latitude1, double longitude1) {
    double latitude2, longitude2, walkingDistance;

    cout << "1. Percurso que passa por menos paragens" << endl;
    cout << "2. Melhor percurso sem mudancas de linha" << endl;
    cout << "3. Melhor percurso com mudancas de linha" << endl;
    cout << "4. Percurso mais barato (que passa por menos zonas)" << endl;
    cout << "0. voltar" << endl;
    cout << "\nESCOLHA UMA OPCAO: ";
    readOption(0, 4);

    cout << "Indique a latitude a que se encontra: " << endl;
    cin >> latitude1;
    cout << "Indique a longitude a que se encontra: " << endl;
    cin >> longitude1;

    cout << "Indique a latitude de onde deseja dirigir-se: " << endl;
    cin >> latitude2;
    cout << "Indique a longitude de onde deseja dirigir-se: " << endl;
    cin >> latitude2;
    cout << "Que distancia esta disposto a percorrer a pe? " << endl;
    cin >> walkingDistance;
    buses.setWalkingDistance(walkingDistance);

    if(option == 1) {
        //buses.getShortestPathChangingLines(latitude1, longitude1, latitude2, longitude2);
        cout << "123" << endl;
    }

    else if(option == 2) {
        //buses.getShortestPathWithinSameLine(latitude1, longitude1);
        cout << "456" << endl;
    }

    else if(option == 3) {
        //buses.getShortestPathChangingLines(latitude1, longitude1, latitude2, longitude2);
        cout << "789" << endl;
    }

    else if(option == 4) {
        cout << "321" << endl;
    }

    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption(latitude1, longitude1);
}