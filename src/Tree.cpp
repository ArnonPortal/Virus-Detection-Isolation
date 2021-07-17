//
// Created by spl211 on 04/11/2020.
//

#include <iostream>
#include "../include/Tree.h"
#include "../include/Session.h"
#include <queue>

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel), children(), rootDepth(0), maxRankNode() {};

Tree::Tree(const Tree &other) : node(), children(), rootDepth(), maxRankNode() { copy(other); }//copy constructor
const Tree &Tree::operator=(Tree &other)//copy assignment
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

Tree::Tree(Tree &&other) : node(), children(), rootDepth(), maxRankNode() //move constructor
{
    move(other);
    for (int i = 0; (unsigned) i < other.children.size(); i++)
        other.children.at(i) = nullptr;
}

const Tree &Tree::operator=(Tree &&other) //move assignment
{
    clear();
    move(other);
    for (int i = 0; (unsigned) i < other.children.size(); i++) {
        other.children.at(i) = nullptr;
    }
    return *this;
}

void Tree::copy(const Tree &other) {
    node = other.node;
    rootDepth = other.rootDepth;
    maxRankNode = other.maxRankNode;
    for (int i = 0; (unsigned) i < other.children.size(); i++) {
        Tree *newTree = other.children.at(i)->clone();
        children.push_back(newTree);
    }
}

Tree::~Tree() {
    clear();
}

void Tree::clear() {
    for (int i = 0; (unsigned) i < children.size(); i++) {
        delete (children.at(i));
        children.at(i) = nullptr;
    }
    children.clear();
    maxRankNode = nullptr;
}

void Tree::move(const Tree &other) {
    node = other.node;
    rootDepth = other.rootDepth;
    maxRankNode = other.maxRankNode;
    children = (vector<Tree*>(other.children));
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {};

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {};

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {};

Tree *CycleTree::clone() const { return new CycleTree(*this); }

Tree *MaxRankTree::clone() const { return new MaxRankTree(*this); }

Tree *RootTree::clone() const { return new RootTree(*this); }

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    Tree *output;

    if (session.getTreeType() == Cycle) {
        CycleTree *temp = new CycleTree(rootLabel, session.getCycle());
        output = temp;
    } else if (session.getTreeType() == MaxRank) {
        MaxRankTree *temp = new MaxRankTree(rootLabel);
        output = temp;
    } else {
        RootTree *temp = new RootTree(rootLabel);
        output = temp;
    }
    return output;
}

int Tree::getRootDepth() {
    return rootDepth;
}

void Tree::setRootDepth(int depth) {
    rootDepth = depth;
}

void Tree::setMaxRankNode(Tree *newMaxRankNode) {
    maxRankNode = newMaxRankNode;
}

std::vector<Tree *> Tree::getChildren() {
    return children;
}

int Tree::getNode() {
    return node;
}

int CycleTree::traceTree() {
    Tree *curr(this);
    for (int i = 0; i < currCycle; i++) {
        if (curr->getChildren().empty()) {
            return curr->getNode();
        }
        curr = curr->getChildren().at(0);
    }
    return curr->getNode();
}

int RootTree::traceTree() {
    return node;
}

int MaxRankTree::traceTree() {
    return maxRankNode->getNode();
}


