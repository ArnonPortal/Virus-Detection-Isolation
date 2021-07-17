//
// Created by spl211 on 04/11/2020.
//
#include "../include/Agent.h"
#include <queue>

using namespace std;

Agent::Agent() {}

Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd) {}

ContactTracer::ContactTracer() : Agent() {}

Agent *Virus::clone() const { return new Virus(*this); }

Agent *ContactTracer::clone() const { return new ContactTracer(*this); }

Agent::~Agent() {};

ContactTracer::~ContactTracer() {}

Virus::~Virus() {}

void Virus::act(Session &session) {
    bool spread = false;
    if (session.getGraph().getInfectionStatus(nodeInd) != 2)//If im a carrier but not sick --> make me sick and enqueue
    {
        session.getGraph().infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    for (int i = 0; !spread && (unsigned) i <
                               session.getGraph().getEdges().size(); i++)//go through all of nodeInd neighbors until you set carrier a healthy node (if there is one)
    {
        int isNeighbor = session.getGraph().getEdges().at(nodeInd).at(i);
        if (isNeighbor == 1 && session.getGraph().getInfectionStatus(i) == 0) {
            session.getGraph().setCarrier(i);
            Virus *newVirus = new Virus(i);
            session.addAgent(*newVirus);
            delete newVirus;
            session.setSpreading(true);
            spread = true;
        }
    }
}

void ContactTracer::act(Session &session) {
    if (!session.isVirusCarriersEmpty())  //if the queue is empty --> the CT has nothing to do
    {
        Tree *tree = Tree::createTree(session, session.dequeueInfected());
        session.bfs(*tree);
        int nodeToIsolate = tree->traceTree();
        delete tree;
        for (int i = 0; (unsigned) i < session.getGraph().getEdges().size(); i++) {
            session.getGraph().getEdges().at(nodeToIsolate).at(i) = 0;//Isolate
            session.getGraph().getEdges().at(i).at(nodeToIsolate) = 0;
        }

    }
}
