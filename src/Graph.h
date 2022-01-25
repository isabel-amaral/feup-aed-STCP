#ifndef STCP_GRAPH_H
#define STCP_GRAPH_H

#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

class Graph {
    /**
     * cada edge representa um segmento de percurso de uma linha da STCP
     * mais especificamente, o percurso entre duas paragens consecutivas da mesma linha
     */
    struct Edge {
        /**
         * código da linha de autocarro
         */
        string lineCode;
        /**
         * distância entre duas paragens consecutivas de uma linha
         */
        double weight;
        /**
         * paragem de destino
         */
        int dest;
    };

    /**
     * Cada nó representa uma paragem de autocarro da STCP.
     */
    struct Node {
        /**
         * código da paragem de autocarro
         */
        string stopCode;
        /**
         * nome da paragem de autocarro
         */
        string stopName;
        /**
         * zona de tarifa em que a paragem se insere
         */
        string zone;
        /**
         * latitude da paragem
         */
        double latitude;
        /**
         * longitude da paragem
         */
        double longitude;

        /**
         * lista dos segmentos de percurso que partem da paragem em questão
         */
        list<Edge> adj;
        /**
         * atributo de auxílio ao algoritmo de Djikstra:
         * distância da paragem à origem do percurso
         */
        double dist;
        /**
         * atributo de auxílio ao algoritmo de Djikstra:
         * paragem predecedente da paragem em questão no percurso a ser considerado
         */
        int pred;
        /**
         * atributo de auxílio ao algoritmo de Djikstra:
         * se a menor distância até à paragem em questão já foi computada
         */
        bool visited;
    };

    /**
     * tamanho do grafo
     * cada paragem é representada internamente por um inteiro de 1 a n
     */
    int n;
    /**
     * todas as paragens da STCP respresentadas através de nós
     */
    vector<Node> stops;
    /**
     * estrutura de dados que mapeia o código de cada paragem ao respetivo inteiro usado para representar a paragem internamente
     */
    map<string, int> stopsInfo;
    /**
     * estrutura de dados que mapeia o código de cada linha ao respetivo nome
     */
    map<string, string> linesInfo;
    /**
     * distância máxima que o utilizador da STCP está disposto a andar para chegar a uma paragem
     */
    double walkingDistance;

public:
    Graph(int num);
    double getStopLatitude(int node) const;
    double getStopLongitude(int node) const;
    const map<string, int>& getStopsInfo() const;
    const map<string, string>& getLinesInfo() const;
    void setNode(const string& code, const string& name, const string& zone, const double& latitude, const double& longitude);
    /**
     * adiciona o código e nome de uma linha ao conjunto de linhas já existentes, representado por linesInfo
     * @param code código da linha a adicionar
     * @param name nome da linha a adicionar
     */
    void addLine(string code, string name);
    /**
     * adiciona um segmento de percurso, representado por uma edge, entre duas paragens consecutivas da mesma linha
     * @param src paragem de origem
     * @param code código da linha a que pertence o segmento de percurso
     * @param weight distância entre as duas paragens a ser consideradas
     * @param dest paragem de destino
     */
    void addEdge(int src, string code, double weight, int dest);
    void setWalkingDistance(double dist);
    static double calculateDistance(double latitude1, double longitude1, double latitude2, double longitude2);
    list<int> findClosestStops(double latitude, double longitude);
    int findClosestStop(double latitude, double longitude);

    //TODO: bfs, devolve nº de paragens
    void getMinimumStopsPath(double latitude, double longitude);
    //TODO: dijkstra com algumas restrições extra, devolve distância
    void getShortestPathWithinSameLine(double latitude, double longitude);
    //TODO: dijkstra clássico
    void getShortestPathChangingLines(double latitude, double longitude, double latitude2, double longitude2);
    //TODO: ?
    void getLowestLineChanges(double latitude, double longitude);

    //TODO: cout do nº de paragens e do caminho
    void showMinimumStopsPath() const;
    //TODO: cout da distância e do caminho
    void showShortestPathWithinSameLine() const;
    //TODO: cout da distânica, nº de vezes q muda de autocarro
    void showShortestPathChangingLines(list<int> path) const;
    //TODO: ?
    void showLowestLineChanges() const;
};

#endif //STCP_GRAPH_H
