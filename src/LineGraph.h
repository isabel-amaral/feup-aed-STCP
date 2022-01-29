#ifndef STCP_LINEGRAPH_H
#define STCP_LINEGRAPH_H

#include "MinHeap.h"
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

class LineGraph {
    /**
     * Código da linha do autocarro.
     */
    string lineCode;
    /**
     * Nome da linha do autocarro.
     */
    string lineName;
    /**
     * Cada edge representa um segmento de percurso entre duas paragens consecutivas da linha em questão.
     */
    struct Edge {
        /**
         * Distância entre duas paragens consecutivas de uma linha.
         */
        double weight;
        /**
         *  Paragem de destino.
         */
        int dest;
    };

    /**
     * Cada nó representa uma paragem de autocarro da STCP que oertence à linha em questão.
     */
    struct Node {
        /**
         * Código da paragem de autocarro.
         */
        string stopCode;
        /**
         * Lista dos segmentos de percurso que partem da paragem em questão.
         */
        list<Edge> adj;
        /**
         * Atributo de auxílio ao Bfs:
         * número de zonas percorridas desde a origem do percurso.
         */
        bool visited;
    };

    /**
    * Tamanho do grafo.
    * Cada paragem é representada internamente por um inteiro de 1 a n.
     */
    int n;
    /**
     * Todas as paragens da linha em questão respresentadas através de nós.
     */
    vector<Node> stops;
    /**
     * Estrutura de dados que mapeia o código de cada paragem ao respetivo inteiro usado para representar a paragem internamente.
     */
    map<string, int> stopsInfo;

public:
    LineGraph(const string& lineCode, const string& lineName, int n);

    /**
     *
     * @return Código da linha do autocarro.
     */
    string getLineCode() const;
    /**
     *
     * @return Nome da linha do autocarro.
     *
     */
    const string& getLineName() const;
    /**
     *
     * @return Vetor de inteiros que representam internamente cada uma das paragens (nós) do grafo.
     */
    vector<string> getStops() const;
    /**
     *
     * @return Estrutura de dados que mapeia o código de cada paragem ao respetivo inteiro
     * usado para representar a paragem internamente.
     */
    const map<string, int>& getStopsInfo() const;
    /**
     * Adiciona um novo nó (paragem) ao grafo.
     * @param code é p código da paragem
     */
    void setNode(const string &code);
    /**
     * Adiciona um segmento de percurso, representado por uma edge, entre duas paragens consecutivas da mesma linha.
     * @param src inteiro que representa a paragem de origem.
     * @param weight distância entre as duas paragens a ser consideradas.
     * @param dest inteiro que representa a paragem de destino.
     */
    void addEdge(int src, double weight, int dest);

    struct Result {
        int count;
        double distance;
        string endStop;
    };
    /**
     * //TODO
     * @param stopsNearEnd fila de prioridade com todas as paragens próximas do ponto final
     * a ser consideradas como possíveis paragens de destino
     * @param source pragaem onde o algoritmo será iniciado
     * @return //TODO
     */
    Result findPathWithinSameLine(const MinHeap<string, double>& stopsNearEnd, int source);
};

#endif //STCP_LINEGRAPH_H
