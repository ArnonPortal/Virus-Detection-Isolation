#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <queue>

class Session;

class Tree {
public:
    Tree(int root);

    Tree(const Tree &other);

    const Tree &operator=(Tree &other);

    Tree(Tree &&other);

    const Tree &operator=(Tree &&other);

    virtual ~Tree();

    void clear();

    void copy(const Tree &other);

    void move(const Tree &other);

    void addChild(const Tree &child);

    static Tree *createTree(const Session &session, int rootLabel);

    virtual Tree *clone() const = 0;

    virtual int traceTree() = 0;

    std::vector<Tree *> getChildren();

    int getNode();

    int getRootDepth();

    void setRootDepth(int depth);

    void setMaxRankNode(Tree *newMaxRankNode);

protected:
    int node;
    std::vector<Tree *> children;
    int rootDepth;
    Tree *maxRankNode;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual Tree *clone() const;

    virtual int traceTree();

protected:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual Tree *clone() const;

    virtual int traceTree();

};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual Tree *clone() const;

    virtual int traceTree();

};

#endif
