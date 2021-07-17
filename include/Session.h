#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "Tree.h"
#include <queue>

using namespace std;

class Agent;

enum TreeType {
    Cycle,
    MaxRank,
    Root
};

class Session {
public:
    Session(const std::string &path);

    Session(const Session &other); //copy constructor
    Session(Session &&other); //move constructor
    const Session &operator=(Session &other); //copy operator
    const Session &operator=(Session &&other); //move operator
    void clear();

    void copy(const Session &other);

    void move(const Session &other);

    virtual ~Session();

    void simulate();

    void addAgent(const Agent &agent);

    void setGraph(const Graph &graph);

    Graph &getGraph();

    int getCycle() const;

    bool isVirusCarriersEmpty();

    void bfs(Tree &tree);

    void enqueueInfected(int);

    int dequeueInfected();

    TreeType getTreeType() const;

    void setSpreading(bool val);

private:
    int cycle;
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;
    queue<int> virusCarriers;
    bool spreading;
};


#endif
;