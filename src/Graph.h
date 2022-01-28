#ifndef STCP_GRAPH_H
#define STCP_GRAPH_H

#include "MinHeap.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
using namespace std;

class Graph {
    /**
     * Cada edge representa um segmento de percurso de uma linha da STCP
     * mais especificamente, o percurso entre duas paragens consecutivas da mesma linha.
     */
    struct Edge {
        /**
         * Código da linha do autocarro.
         */
        string lineCode;
        /**
          * Distância entre duas paragens consecutivas de uma linha.
          */
        double weight;
        /**
         * Paragem de destino.
         */
        int dest;
    };

    /**
     * Cada nó representa uma paragem de autocarro da STCP.
     */
    struct Node {
        /**
        * Código da paragem de autocarro.
        */
        string stopCode;
        /**
         * Nome da paragem de autocarro.
         */
        string stopName;
        /**
         * Zona de tarifa em que a paragem se insere.
         */
        string zone;
        /**
         * Latitude da paragem.
         */
        double latitude;
        /**
         * Longitude da paragem.
         */
        double longitude;

        /**
          * Lista dos segmentos de percurso que partem da paragem em questão.
          */
        list<Edge> adj;
        /**
         * Atributo de auxílio ao algoritmo de Djikstra:
         * distância da paragem à origem do percurso.
         */
        double dist;
        /**
         * Atributo de auxílio ao algoritmo de Djikstra:
         * paragem predecedente da paragem em questão no percurso a ser considerado.
         */
        int pred;
        /**
         * Atributo de auxílio ao algoritmo de Djikstra:
         * se a menor distância até à paragem em questão já foi computada.
         */
        bool visited;
    };

    /**
   * Tamanho do grafo.
   * Cada paragem é representada internamente por um inteiro de 1 a n.
   */
    int n;
    /**
     * Todas as paragens da STCP respresentadas através de nós.
     */
    vector<Node> stops;
    /**
     * Estrutura de dados que mapeia o código de cada paragem ao respetivo inteiro usado para representar a paragem internamente.
     */
    map<string, int> stopsInfo;
    /**
     * Estrutura de dados que mapeia o código de cada linha ao respetivo nome.
     */
    map<string, string> linesInfo;
    /**
     * Distância máxima que o utilizador da STCP está disposto a andar para chegar a uma paragem.
     */
    double walkingDistance;

public:
    Graph();
    Graph(int num);

    /**
     *
     * @return Vetor de inteiros que representam internamente cada uma das paragens (nós) do grafo.
     */
    vector<string> getStops() const;
    /**
     *
     * @param node nó do grafo.
     * @return Código de uma determinada paragem (nó) do grafo.
     */
    string getStopCode(int node) const;
    /**
     *
     * @param node nó do grafo.
     * @return Nome de uma determinada paragem (nó) do grafo.
     */
    string getStopName(int node) const;
    /**
     *
     * @param node nó do grafo.
     * @return  Zona de tarifa em que uma determinada paragem (nó) se insere.
     */
    string getStopZone(int node) const;
    /**
     *
     * @param node nó do grafo.
     * @return Latitude de uma determinada paragem (nó) do grafo.
     */
    double getStopLatitude(int node) const;
    /**
     *
     * @param node nó do grafo.
     * @return Longitude de uma determinada paragem (nó) do grafo.
     */
    double getStopLongitude(int node) const;

    list<string> getStopLines(string node) const;
    /**
     *
     * @return Estrutura de dados que mapeia o código de cada paragem ao respetivo inteiro
     * usado para representar a paragem internamente.
     */
    const map<string, int>& getStopsInfo() const;
    /**
     *
     * @return Estrutura de dados que mapeia o código de cada linha ao respetivo nome.
     */
    const map<string, string>& getLinesInfo() const;
    /**
     * Adiciona um novo nó (paragem) ao grafo.
     * @param code é o código da paragem.
     * @param name é o nome da paragem.
     * @param zone é a zona onde se localiza a paragem.
     * @param latitude é a latitude da paragem.
     * @param longitude é a longitude da paragem.
     */
    void setNode(const string& code, const string& name, const string& zone, const double& latitude, const double& longitude);
    /**
     * Adiciona o código e nome de uma linha ao conjunto de linhas já existentes, representado por linesInfo.
     * @param code código da linha a adicionar.
     * @param name nome da linha a adicionar.
     */
    void addLine(string code, string name);
    /**
     * Adiciona um segmento de percurso, representado por uma edge, entre duas paragens consecutivas da mesma linha.
     * @param src paragem de origem.
     * @param code código da linha a que pertence o segmento de percurso.
     * @param weight distância entre as duas paragens a ser consideradas.
     * @param dest paragem de destino.
     */
    void addEdge(int src, string code, double weight, int dest);
    /**
     * Define a distância máxima que o utilizador da STCP está disposto a andar para chegar a uma paragem.
     * @param dist é a distância máxima.
     */
    void setWalkingDistance(double dist);
    /**
     * Adiciona segmentos de percurso (edges) entre paragens "vizinhas" (que estão a menos de 50 metros).
     */
    void addWalkingEdges();
    /**
     * Acrescenta ao grafo, um novo nó que representa o local de partida/chegada do utilizador e
     * também novos segmentos de percurso(edges) entre o local e as várias paragens(stops) próximas ao mesmo.
     * @param latitude latitude do local de partida/chegada do utilizador.
     * @param longitude longitude do local de partida/chegada do utilizador.
     * @param closestStops lista que contém todas as paragens próximas ao respetivo local.
     */
    void addPositionNode(double latitude, double longitude, list<int> closestStops);
    /**
     * Remove do grafo o nó posição (referente ao local de partida/chegada do utilizador)
     * e todas as edges adicionais entre este nó e as paragens que se encontram na sua proximidade.
     * @param closestStops é a lista que contém todas as paragens próximas ao respetivo local.
     */
    void removePositionNode(list<int> closestStops);
    /**
     * Calcula a distância entre dois pontos da Terra a partir de suas latitudes e longitudes.
     * @param latitude1 latitude do ponto 1.
     * @param longitude1 longitude do ponto 1
     * @param latitude2 latitude do ponto 2.
     * @param longitude2 longitude do ponto 2.
     * @return Distância entre os dois pontos.
     */
    static double calculateDistance(double latitude1, double longitude1, double latitude2, double longitude2);
    /**
     * Determina, com base no atributo walkingDistance, as paragens próximas à um determindado local, a partir da latitude e longitude do mesmo.
     * @param latitude latitude do local.
     * @param longitude longitude do local.
     * @return Lista de inteiros que representam internamente cada uma das paragens próximas ao respetivo local.
     */
    list<int> findClosestStops(double latitude, double longitude);
    /**
     *
     * Determina, com base no atributo walkingDistance, a paragem mais próxima à um determindado local, a partir da latitude e longitude do mesmo.
     * @param latitude latitude do local.
     * @param longitude longitude do local.
     * @return Inteiro referente a representação interna da paragem mais próxima ao local.
     */
    int findClosestStop(double latitude, double longitude);
    //TODO: DOCUMENTACAO
    void bfs(int a, int b);
    /**
     * Determina, com recurso ao bfs, qual o caminho entre dois locais (partida e destino) que passa por menos paragens.
     * @param latitude1 latitude do local de partida.
     * @param longitude1 longitude do local de partida.
     * @param latitude2 latitude do destino.
     * @param longitude2 longitude do destino.
     */
    void getMinimumStopsPath(double latitude1, double longitude1, double latitude2, double longitude2);
    /**
     *
     * Determina, com recurso ao algoritmo de dijkstra, qual o caminho entre dois locais (partida e destino) percorre menor distância.
     * @param latitude1 latitude do local de partida.
     * @param longitude1 longitude do local de partida.
     * @param latitude2 latitude do destino.
     * @param longitude2 longitude do destino.
     */
    void getShortestPathChangingLines(double latitude, double longitude, double latitude2, double longitude2);
    // TODO: DOCUMENTACAO; QUE ALGORITMO USOU-SE ETC
    void getLowestLineChanges(double latitude, double longitude);
    //TODO: MELHORAR O COUT: INDICAR QUE DEVE MUDAR DE AUTOCARRO E IMPRIMIR O NUMERO DE PARAGENS QUE IRÁ PERCORRER
    /**
     * Imprime na tela o número de paragens e o caminho que o utilizador deve seguir de modo a percorrer menos paragens possíveis.
     * @param path Lista de inteiros que representam internamente cada uma das paragens que fazem parte do caminho.
     */
    void showMinimumStopsPath(vector<int> path) const;
    //TODO: cout da distânica, nº de vezes q muda de autocarro
    /**
     * Imprime na tela a distância, o número de vezes que muda de autocarro e o respetivo
     * caminho que o utilizador deve seguir de modo a percorrer menor distância possível.
     * @param path Lista de inteiros que representam internamente cada uma das paragens que fazem parte do caminho.
     */
    void showShortestPathChangingLines(list<int> path) const;
    //TODO: IMPLEMENTACAO
    /**
     * Imprime na tela a distância, o número de vezes que muda de autocarro e o respetivo
     * caminho que o utilizador deve seguir de modo a efetuar menos mudanças de autocarro (linha) possíveis.
     */
    void showLowestLineChanges() const;
};

#endif //STCP_GRAPH_H
