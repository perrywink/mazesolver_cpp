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
            if (findNextNodeP(nodeP, openList, closedList, goalNode)) {
                // iterate adjacent nodes clockwise
                for (int direction = UP; direction <= LEFT; direction++)
                {
                    //Assigns adjacent node to nodeQ
                    if (nodeP->getAdjNode(convertIntToDir(direction), nodeQ))
                    {
                        if (nodeQ->isValidAdjNode(env) &&
                            !closedList->contains(nodeQ, false) &&
                            !openList->contains(nodeQ, false))
                        {
                            nodeQ->setDistanceTraveled(nodeP->getDistanceTraveled() + 1);
                            openList->addElement(nodeQ);
                        };
                    };

                };
                closedList->addElement(nodeP);
            };
        } while (!nodeP->equals(*goalNode, false));

        //When there is no path to the goal node
        if (!(nodeP->equals(*goalNode, false))) {
            std::cout << "Error: No Available Path" << std::endl;
        }
        this->nodesExplored = new NodeList(*closedList);
    }

    //Memory Cleanup

    delete nodeQ;
    delete startNode;
    delete goalNode;
    delete openList;
    delete closedList;
}

NodeList* PathSolver::getNodesExplored() {
    return new NodeList(*this->nodesExplored);
}

NodeList* PathSolver::getPath(Env env) {
    NodeList* solution = new NodeList();
    //init currNode as last element in nodesExplored i.e. goalNode
    Node* currNode = nullptr;
    currNode = this->nodesExplored->getNode(nodesExplored->getLength() - 1);
    Node* nextNode = nullptr;
    int dist2Goal = currNode->getDistanceTraveled();

    solution->addElement(currNode);

    for (int i = 0; i < dist2Goal; i++)
    {
        for (int direction = UP; direction <= LEFT; direction++) {

            //nextNode gets instantiated in getAdjNode
            if (currNode->getAdjNode(convertIntToDir(direction), nextNode))
            {
                if (nextNode->isValidAdjNode(env))
                {
                    nextNode->setDistanceTraveled(currNode->getDistanceTraveled() - 1);
                    if (this->nodesExplored->contains(nextNode, true))
                    {
                        // delete currNode;
                        // currNode = new Node(*nextNode);

                        currNode = nextNode;
                        nextNode = nullptr;

                        solution->addElement(currNode);
                    }
                }
            }
            delete nextNode;
            nextNode = nullptr;
        }
    }

    delete currNode;
    solution->reverseNodesArray();

    NodeList* copySol = new NodeList(*solution);
    delete solution;
    return copySol;
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

bool PathSolver::findNextNodeP(Node*& nodeP, NodeList* openList, NodeList* closedList, Node* goalNode) {
    bool foundNodeP = true;
    //Resets node p from previous iteration
    nodeP = nullptr;

    for (int i = 0; i < openList->getLength(); i++)
    {
        if (!closedList->contains(openList->getNode(i), false)) {

            //Inits node p to be the first unvisited node in the list
            if (nodeP == nullptr) {
                //frees up previous nodeP allocation before reassignment
                // delete nodeP;
                // nodeP = new Node(*openList->getNode(i));
                nodeP = openList->getNode(i);
            }

            //Subsequent comparisons and reassignments to new nodes with smallest est dist
            if (nodeP->getEstimatedDist2Goal(goalNode) > openList->getNode(i)->getEstimatedDist2Goal(goalNode)) {
                // delete nodeP;
                // nodeP = new Node(*openList->getNode(i));
                nodeP = openList->getNode(i);
            }
        }
    }
    //No valid nodeP found
    if (nodeP == nullptr) {
        foundNodeP = false;
    }
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