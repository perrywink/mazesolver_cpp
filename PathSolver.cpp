#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver() {
    // TODO
}

PathSolver::~PathSolver() {
    // TODO
}

void PathSolver::forwardSearch(Env env) {
    Node* startNode = nullptr;
    Node* goalNode = nullptr;

    bool foundStart = findNode(env, SYMBOL_START, startNode);
    bool foundGoal = findNode(env, SYMBOL_GOAL, goalNode);

    NodeList* openList = nullptr;
    NodeList* closedList = nullptr;
    Node* nodeP = nullptr;
    Node* nodeQ = nullptr;

    //only execute the algo if start and goal nodes found
    if (foundStart && foundGoal) {

        //init lists
        openList = new NodeList();
        closedList = new NodeList();

        openList->addElement(startNode);

        //The 2 nodelists will never have the same length unless all the nodes have been explored
        //i.e. No more nodes to add and all nodes have been visited
        while (!nodeP->equals(*goalNode) || !openList->isEqualLength(*closedList)) {

        }

    }

    delete startNode;
    delete goalNode;
    delete openList;
    delete closedList;

}

NodeList* PathSolver::getNodesExplored() {
    return new NodeList(*this->nodesExplored);
}

NodeList* PathSolver::getPath(Env env) {
    // TODO
    return nullptr;
}

//Addtional functions

bool PathSolver::findNode(Env env, char targetNode, Node* foundNode) {
    bool isFound = false;
    for (int row = 0; row < ENV_DIM && !std::cin.eof(); row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            if (env[row][col] == targetNode) {
                isFound = true;
                foundNode = new Node(row, col, 0);
            }
        }
    }

    return isFound;
};

//-----------------------------