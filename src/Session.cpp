//
// Created by spl211 on 05/11/2020.
//

#include <fstream>
#include <iostream>
#include "../include/Session.h"
#include "../include/Agent.h"
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path) : cycle(0), g(), treeType(), agents(), virusCarriers(),
                                            spreading(true) {

    ifstream jsonFile(path);
    json j;
    jsonFile >> j;
    vector<vector<int>> tmp = j["graph"];
    g = Graph(tmp);
    for (int i = 0; (unsigned) i < j["agents"].size(); i++) {
        if (j["agents"].at(i).at(0) == "V") {
            Agent *newVirus = new Virus(j["agents"].at(i).at(1));
            agents.push_back(newVirus);
            g.setCarrier(j["agents"].at(i).at(1));
        } else {
            Agent *newCT = new ContactTracer();
            agents.push_back(newCT);
        }
    }
    if (j["tree"] == "C")
        treeType = Cycle;
    if (j["tree"] == "R")
        treeType = Root;
    if (j["tree"] == "M")
        treeType = MaxRank;
}


void Session::copy(const Session &other) {
    g = other.g;
    treeType = other.treeType;
    cycle = other.cycle;
    virusCarriers = other.virusCarriers;
    spreading = other.spreading;
    for (int i = 0; (unsigned) i < other.agents.size(); i++) {
        agents.push_back(other.agents.at(i)->clone());
    }
}

void Session::move(const Session &other) {
    g = other.g;
    treeType = other.treeType;
    cycle = other.cycle;
    virusCarriers = other.virusCarriers;
    spreading = other.spreading;
    agents = (vector<Agent *>(other.agents));
}

void Session::clear() {
    for (int i = 0; (unsigned) i < agents.size(); i++) {
        if (agents.at(i)) {
            delete agents.at(i);
        }
    }
    agents.clear();
}

Session::~Session()//destructor
{
    clear();
}

Session::Session(const Session &other)
        : cycle(), g(), treeType(), agents(), virusCarriers(), spreading()//copy constructor
{
    this->copy(other);
}

const Session &Session::operator=(Session &other) //copy assignment
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

Session::Session(Session &&other)
        : cycle(), g(), treeType(), agents(), virusCarriers(), spreading()//move constructor
{
    move(other);
    for (int i = 0; (unsigned) i < other.agents.size(); i++) {
        other.agents.at(i) = nullptr;
    }

}

const Session &Session::operator=(Session &&other) {//move assignment
    clear();
    move(other);
    for (int i = 0; (unsigned) i < other.agents.size(); i++) {
        other.agents.at(i) = nullptr;
    }
    return *this;
}

Graph &Session::getGraph() {
    return g;
}

int Session::getCycle() const {
    return cycle;
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::bfs(Tree &tree) {
    queue<Tree *> que = queue<Tree *>();//Queue initialization
    Tree *maxRankNode = &tree;//variant to find the maxRankNode during the creation of the bfs tree
    que.push(&tree);//inserting the first node to the queue
    std::vector<bool> bfsVisited;//a vector of visited nodes
    for (int i = 0; (unsigned) i < g.getEdges().size(); i++) {
        bfsVisited.push_back(false);
    }
    bfsVisited.at(tree.getNode()) = true;
    while (!que.empty()) {
        Tree *currNode = que.front();//pop the first node of the queue
        que.pop();
        int size = g.getEdges().at(currNode->getNode()).size();
        for (int j = 0; j < size; j++) {//go through his neighbors
            if (!bfsVisited.at(j) &&
                g.getEdges().at(currNode->getNode()).at(j) == 1) {//if we didnt visit this neighbor::
                bfsVisited.at(j) = true;//marking the node as visited
                Tree *child = Tree::createTree(*(this), j);//creating a new child and attaching him the father
                child->setRootDepth(currNode->getRootDepth());
                currNode->addChild(*child);
                que.push(currNode->getChildren().at(currNode->getChildren().size() - 1));
                delete (child);
            }
        }
        if (maxRankNode->getChildren().size() <
            currNode->getChildren().size()) {//this section is for tracking the maxRankedNode as defined in the assignment
            maxRankNode = currNode;
        } else if (maxRankNode->getChildren().size() == currNode->getChildren().size() &&
                   maxRankNode->getRootDepth() > currNode->getRootDepth()) {
            maxRankNode = currNode;
        }
    }
    tree.setMaxRankNode(maxRankNode);


}

TreeType Session::getTreeType() const {
    return treeType;
}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

void Session::enqueueInfected(int node) {
    virusCarriers.push(node);
}

int Session::dequeueInfected() {
    int output = virusCarriers.front();
    virusCarriers.pop();
    return output;
}

bool Session::isVirusCarriersEmpty() { return virusCarriers.empty(); }

void Session::simulate() {
    bool terminate = false;
    while (!terminate) {
        int currAgentsSize = agents.size();
        for (int i = 0; i < currAgentsSize; i++)
            agents.at(i)->act(*this);
        cycle++;
        if (g.wholeGraphInfected() ||
            !spreading) { //terminate if the whole graph infected or the infected nodes have no healthy neighbors to infect
            terminate = true;
        }
        setSpreading(false);
    }
    ofstream i("./output.json");
    json outputJ;
    outputJ["graph"] = g.getEdges();
    vector<int> infectedFinalStat;
    for (int i = 0; (unsigned) i < g.getEdges().size(); i++) {
        if (g.isInfected(i))
            infectedFinalStat.push_back(i);
    }
    outputJ["infected"] = infectedFinalStat;
    i << outputJ;
}

void Session::setSpreading(bool val) {
    spreading = val;
}
