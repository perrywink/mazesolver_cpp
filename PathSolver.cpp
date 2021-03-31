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

    bool foundStart = findNodeInEnv(env, SYMBOL_START, &startNode);
    bool foundGoal = findNodeInEnv(env, SYMBOL_GOAL, &goalNode);

    NodeList* openList = nullptr;
    NodeList* closedList = nullptr;
    Node* nodeP = nullptr;
    // Node* nodeQ = nullptr;

    //only execute the algo if start and goal nodes found
    if (foundStart && foundGoal) {

        //init lists
        openList = new NodeList();
        closedList = new NodeList();

        openList->addElement(startNode);


        //test findNextNodeP
        Node* testGoalNode = new Node(1, 3, 0);

        NodeList* testList = new NodeList();
        Node* testNode1 = new Node(3, 1, 0);
        Node* testNode2 = new Node(3, 2, 1);
        testList->addElement(testNode1);
        testNode1->setIsVisited(true);
        testList->addElement(testNode2);
        testNode2->setIsVisited(true);
        testList->addElement(new Node(4, 2, 2));
        Node* testNode3 = new Node(2, 2, 2);
        // testNode3->setIsVisited(true);
        testList->addElement(testNode3);
        testList->addElement(new Node(3, 3, 2));

        //maybe check for if openList is "empty" or not
        do {
            // if (findNextNodeP(&nodeP, openList, goalNode)) {
            if (findNextNodeP(&nodeP, testList, testGoalNode)) {
                nodeP->printNode();
            };
        } while (!nodeP->equals(*goalNode) || !openList->checkAllVisited());

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

bool PathSolver::findNodeInEnv(Env env, char targetNode, Node** foundNode) {
    bool isFound = false;
    for (int row = 0; row < ENV_DIM && !std::cin.eof(); row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            if (env[row][col] == targetNode) {
                isFound = true;
                *foundNode = new Node(row, col, 0);
            }
        }
    }
    return isFound;
};

bool PathSolver::findNextNodeP(Node** nodeP, NodeList* openList, Node* goalNode) {
    bool foundNodeP = true;
    *nodeP = nullptr;

    for (int i = 0; i < openList->getLength(); i++)
    {
        if (!openList->getNode(i)->getIsVisited()) {
            if (*nodeP == nullptr) {
                *nodeP = openList->getNode(i);

            }

            if ((*nodeP)->getEstimatedDist2Goal(goalNode) > openList->getNode(i)->getEstimatedDist2Goal(goalNode)) {
                *nodeP = openList->getNode(i);

            }
        }
    }

    if (*nodeP == nullptr) {
        foundNodeP = true;
    }


    return foundNodeP;
};

//-----------------------------