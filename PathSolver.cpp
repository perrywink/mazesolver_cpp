#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver() {
    nodesExplored = nullptr;
}

PathSolver::~PathSolver() {
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env) {
    Node* startNode = nullptr;
    Node* goalNode = nullptr;

    bool foundStart = findNodeInEnv(env, SYMBOL_START, &startNode);
    bool foundGoal = findNodeInEnv(env, SYMBOL_GOAL, &goalNode);

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

        do {
            if (findNextNodeP(&nodeP, openList, goalNode)) {
                // iterate adjacent nodes clockwise
                for (int direction = UP; direction <= LEFT; direction++)
                {
                    //Assigns adjacent node to nodeQ
                    if (nodeP->getAdjNode(convertIntToDir(direction), &nodeQ)) {
                        nodeQ->setDistanceTraveled(nodeP->getDistanceTraveled() + 1);
                        if (nodeQ->isValidAdjNode(env) && !openList->contains(nodeQ, false)) {
                            openList->addElement(nodeQ);
                        };
                        delete nodeQ;
                    };
                };
                nodeP->setIsVisited(true);

                closedList->addElement(nodeP);
            };


        } while (!(nodeP->equals(*goalNode, false)) && !(openList->checkAllVisited()));

        if (!(nodeP->equals(*goalNode, false)) && openList->checkAllVisited()) {
            std::cout << "Error: No Available Path" << std::endl;
        }
        this->nodesExplored = new NodeList(*closedList);
    }


    //Memory Cleanup
    nodeP = nullptr;
    nodeQ = nullptr;
    delete startNode;
    delete goalNode;
    delete openList;
    delete closedList;

}

NodeList* PathSolver::getNodesExplored() {
    return  new NodeList(*this->nodesExplored);
}

NodeList* PathSolver::getPath(Env env) {
    NodeList* solution = new NodeList();
    Node* currNode = this->nodesExplored->getNode(nodesExplored->getLength() - 1);
    Node* nextNode = nullptr;
    int dist2Goal = currNode->getDistanceTraveled();

    solution->addElement(currNode, dist2Goal);

    for (int i = 1; i <= dist2Goal; i++)
    {
        for (int direction = UP; direction <= LEFT; direction++) {
            //adjNode gets instantiated in getAdjNode
            if (currNode->getAdjNode(convertIntToDir(direction), &nextNode)) {
                nextNode->setDistanceTraveled(currNode->getDistanceTraveled() - 1);
                if (nextNode->isValidAdjNode(env))
                {
                    if (this->nodesExplored->contains(nextNode, true))
                    {
                        nextNode->printNode();
                        solution->addElement(nextNode, dist2Goal - i);
                        currNode = nullptr;
                        currNode = nextNode;
                        nextNode = nullptr;
                    }
                }

            }
        }
    }
    return solution;
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

bool PathSolver::findNextNodeP(Node** ptrNodeP, NodeList* openList, Node* goalNode) {
    bool foundNodeP = true;
    *ptrNodeP = nullptr;

    for (int i = 0; i < openList->getLength(); i++)
    {
        if (!openList->getNode(i)->getIsVisited()) {
            if (*ptrNodeP == nullptr) {
                *ptrNodeP = openList->getNode(i);

            }

            if ((*ptrNodeP)->getEstimatedDist2Goal(goalNode) > openList->getNode(i)->getEstimatedDist2Goal(goalNode)) {
                *ptrNodeP = openList->getNode(i);

            }
        }
    }

    if (*ptrNodeP == nullptr) {
        foundNodeP = true;
    }

    ptrNodeP = nullptr;
    return foundNodeP;
};

Direction PathSolver::convertIntToDir(int dirInt) {
    //Set to default value of UP first
    Direction direction = UP;
    if (dirInt == 0) {
        direction = UP;
    }
    else if (dirInt == 1) {
        direction = RIGHT;
    }
    else if (dirInt == 2) {
        direction = DOWN;
    }
    else if (dirInt == 3) {
        direction = LEFT;
    }
    else {
        std::cout << "Error: No Such Direction";
    }

    return direction;
};


//-----------------------------