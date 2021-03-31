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

    bool foundStart = findNodeInEnv(env, SYMBOL_START, startNode);
    bool foundGoal = findNodeInEnv(env, SYMBOL_GOAL, goalNode);

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

        //maybe check for if openList is "empty" or not
        while (!nodeP->equals(*goalNode) || !openList->checkAllVisited()) {

            
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

bool PathSolver::findNodeInEnv(Env env, char targetNode, Node* foundNode) {
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

bool PathSolver::findNextNodeP(Node* nodeP, NodeList* openList, Node* goalNode){
    bool foundNodeP = false;
    Node* nextNode = nullptr;
    Node* currNode = nullptr;
    //FIXME: magic num
    nodeP = openList->getNode(0);
    for (int i = 0; i < openList->getLength(); i++)
    {
        nextNode = openList->getNode(i+1);
        currNode = openList->getNode(i);
        if(currNode->getEstimatedDist2Goal(goalNode) > nextNode->getEstimatedDist2Goal(goalNode)){
            if (!nextNode->getIsVisited()){
                
            }
        }
    }
    delete currNode;
    delete nextNode;

    return foundNodeP;
};

//-----------------------------