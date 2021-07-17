#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);

    Graph();

    std::vector<std::vector<int>> &getEdges();

    void infectNode(int nodeInd);

    void setCarrier(int nodeInd);

    bool isInfected(int nodeInd);

    int getInfectionStatus(int nodeInd);

    bool wholeGraphInfected();

private:
    std::vector<std::vector<int>> edges;
    std::vector<int> infectedNodes; //contain the status of each node: 0-healthy, 1-carrier, 2-infected
    int infectedNodeNum; //number of red(infected) nodes
}

#endif
;