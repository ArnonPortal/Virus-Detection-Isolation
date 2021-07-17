//
// Created by spl211 on 04/11/2020.
//

#include <iostream>
#include "../include/Graph.h"

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), infectedNodes(), infectedNodeNum(0) {
    for (int i = 0; (unsigned) i < edges.size(); i++) {
        infectedNodes.push_back(0);// 0 means healthy ( blue )
    }
};

Graph::Graph() : edges(), infectedNodes(), infectedNodeNum() {};

std::vector<std::vector<int>> &Graph::getEdges() {
    return edges;
}

int Graph::getInfectionStatus(int nodeInd) {
    return infectedNodes.at(nodeInd);

};

bool Graph::isInfected(int nodeInd) { return infectedNodes.at(nodeInd) == 2; }

bool Graph::wholeGraphInfected() {
    return (unsigned) infectedNodeNum == infectedNodes.size();
}

void Graph::infectNode(int nodeInd) {
    infectedNodes.at(nodeInd) = 2;
    infectedNodeNum++;
}

void Graph::setCarrier(int nodeInd) {
    infectedNodes.at(nodeInd) = 1;
}


