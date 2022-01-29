#ifndef STCP_LINES_H
#define STCP_LINES_H

#include "Graph.h"
#include "LineGraph.h"
#include <set>

class Lines{
    /**
     * Grafo com a representação de todas as paragens e linhas dos autocarros da STCP.
     */
    Graph buses;
    /**
     * Lista de grafos menores, cada um dos quais representa uma linha da STCP com um determinado sentido.
     */
    list<LineGraph> lines;
    /**
     * Distância máxima que o utilizador da STCP está disposto a andar para chegar a uma paragem
     * ou para chegar da última paragem até ao seu destino.
     */
    double walkingDistance;

public:
    Lines();
    /**
     *
     * @return Lista de grafos que representam as várias linhas e respetivos sentidos da STCP.
     */
    const list<LineGraph>& getLines() const;
    /**
     * Atualiza as linhas a considerar após o load dos dados ser realizado.
     * @param lines Lista de grafos que representam as várias linhas e respetivos sentidos da STCP.
     */
    void setLines(const list<LineGraph> &lines);
    /**
     * Atualiza as linhas e paragens a considerar após o load dos dados ser realizado.
     * @param buses Grafo com a representação de todas as paragens e linhas dos autocarros da STCP.
     */
    void setBuses(const Graph &buses);
    /**
     * Define a distância máxima que o utilizador da STCP está disposto a andar para chegar a uma paragem.
     * @param walkingDistance é a distância máxima.
     */
    void setWalkingDistance(double walkingDistance);
    /**
     * Determina, com base no atributo walkingDistance, as paragens próximas a um determindado local, a partir da latitude e longitude do mesmo.
     * @param latitude é a latitude do local.
     * @param longitude é a longitude do local.
     * @return Fila de prioridade de pares (inteiro, double) que representam internamente respetivamente
     * cada uma das paragens próximas ao respetivo local e a distância entre a paragem e o local considerado.
     */
    MinHeap<string, double> findClosestStops(double latitude, double longitude);
    /**
     * Encontra na lista de grafos das linhas a linha correspondente ao código da linha pretendido
     * e que contenha uma determinada paragem (dado que existem duas linhas com o mesmo nome, correspondentes a sentidos opostos, na lista).
     * @param line código da linha
     * @param stopCode código da paragem
     * @return o grafo que representa a linha de código line e que contenha a paragem stopCode.
     */
    LineGraph findCorrespondingLine(string line, string stopCode) const;

    /**
     * Determina, com recurso ao algoritmo findPathWithinSameLine() da classe LineGraph o percurso mais curto sem mudar de linha.
     * @param latitude1 latitude do local de partida.
     * @param longitude1 longitude do local de partida.
     * @param latitude2 latitude do destino.
     * @param longitude2 longitude do destino.
     */
    void getShortestPathWithinSameLine(double latitude1, double longitude1, double latitude2, double longitude2);
    /**
     * Imprime informação sobre o percurso de uma local para outro sem nunca mudar de autocarro.
     * Imprime o nº de paragens e distância que o percorridas, o código e nome da linha que deve ser apanhada
     * e o código e nome das várias paragens por onde passa.
     * @param numStops nº de paragens percorridas.
     * @param distance distância percorrida.
     * @param line linha que será utilizada.
     * @param startStop paragem de início do percurso.
     */
    void showShortestPathWithinSameLine(int numStops, double distance, string line, string startStop) const;
};

#endif //STCP_LINES_H
