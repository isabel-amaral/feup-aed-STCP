#include "Menu.h"

Menu::Menu() {
    cout << "BEM-VINDO AOS SERVICOS STCP" << endl;
    option = 0;

    buses = Graph(2487);
    LoadData loadData(buses, lines.getLines());
    buses = loadData.getBuses();
    lines.setLines(loadData.getLines());
    lines.setBuses(buses);

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

void Menu::processOption() {
    switch (option) {
        case 0: menu0();
            break;
        case 1: menu1();
            break;
        case 2: menu2();
            break;
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
        processOption();
    }
    else {
        cout << "VOLTE SEMPRE.";
        exit (0);
    }
}

void Menu::menu1() {
    double distance, latitude1, longitude1;
    cout << "Indique quantos metros esta disposto a andar ate a paragem: " << endl;
    cin >> distance;
    buses.setWalkingDistance(distance);
    cout << "Indique a latitude a que se encontra: " << endl;
    cin >> latitude1;
    cout << "Indique a longitude a que se encontra: " << endl;
    cin >> longitude1;
    cout << "Encontra-se a: " << endl;

    list<int> closestStops = buses.findClosestStops(latitude1, longitude1);
    for (list<int>::iterator it = closestStops.begin(); it != closestStops.end(); it++) {
        cout << Graph::calculateDistance(latitude1, longitude1,
                                         buses.getStopLatitude(*it),
                                         buses.getStopLongitude(*it));
        cout << " metros de: " << buses.getStopName(*it) << " (" << buses.getStopCode(*it) << ")" << endl;
    }

    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption();
}

void Menu::menu2() {
    double latitude1, longitude1, latitude2, longitude2, walkingDistance;

    cout << "1. Percurso que passa por menos paragens" << endl;
    cout << "2. Percurso mais curto sem mudancas de linha" << endl;
    cout << "3. Percurso mais curto com mudancas de linha" << endl;
    cout << "4. Percurso mais barato (que passa por menos zonas)" << endl;
    cout << "0. voltar" << endl;
    cout << "ESCOLHA UMA OPCAO: ";
    readOption(0, 4);

    if(option == 0) {
        menu0();
    }

    cout << "Indique a latitude a que se encontra: " << endl;
    cin >> latitude1;
    cout << "Indique a longitude a que se encontra: " << endl;
    cin >> longitude1;

    cout << "Indique a latitude do local para onde se deseja dirigir: " << endl;
    cin >> latitude2;
    cout << "Indique a longitude do local para onde se deseja dirigir: " << endl;
    cin >> longitude2;
    cout << "Indique quantos metros esta disposto a andar ate a paragem: " << endl;
    cin >> walkingDistance;
    buses.setWalkingDistance(walkingDistance);
    lines.setWalkingDistance(walkingDistance);

    if (option == 1)
        buses.getMinimumStopsPath(latitude1, longitude1, latitude2, longitude2);

    else if (option == 2)
        lines.getShortestPathWithinSameLine(latitude1, longitude1, latitude2, longitude2);

    else if (option == 3)
        buses.getShortestPathChangingLines(latitude1, longitude1, latitude2, longitude2);
    else if (option == 4)
        buses.getLowestZoneChanges(latitude1, longitude1, latitude2, longitude2);

    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption();
}