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
         * nome da linha de autocarro
         */
        string lineName;
        /**
         * distância entre duas paragens consecutivas de uma linha
         */
        int weight;
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
        long latitude;
        /**
         * longitude da paragem
         */
        long longitude;

        /**
         * lista dos segmentos de percurso que partem da paragem em questão
         */
        list<Edge> adj; //The list of outgoing edges (to adjacent nodes)
        /**
         * atributo de auxílio ao algoritmo de Djikstra:
         * distância da paragem à origem do percurso
         */
        int dist;
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
     * estrutura de dados que mapeia o nome de cada paragem ao respetivo inteiro usado para representar a paragem internamente
     */
    map<string, int> stopsInfo;

public:
    Graph(int num);
    /**
     * adiciona um segmento de percurso, representado por uma edge, entre duas paragens consecutivas da mesma linha
     * @param src paragem de origem
     * @param code código da linha a que pertence o segmento de percurso
     * @param name nome da linha a que pertence o segmento de percurso
     * @param weight distância entre as duas paragens a ser consideradas
     * @param dest paragem de destino
     */
    void addEdge(int src, string code, string name, int weight, int dest);
};

#endif //STCP_GRAPH_H
