#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
    this->isVisited = false;
}

Node::~Node() {
    // TODO
}

int Node::getRow() {
    return this->row;
}

int Node::getCol() {
    return this->col;
}

int Node::getDistanceTraveled() {
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal) {
    int rowDiff = this->row - goal->getRow();
    int colDiff = this->col - goal->getCol();
    int manhDist = abs(rowDiff) + abs(colDiff);
    return manhDist + this->dist_traveled;
}

//Additional Methods
Node::Node(Node& other) {
    this->row = other.getRow();
    this->col = other.getCol();
    this->dist_traveled = other.getDistanceTraveled();
    this->isVisited = other.getIsVisited();
};

void Node::printNode() {
    std::cout << "Node - row: " << this->row
        << ", col: " << this->col
        << ", dist_traveled:" << this->dist_traveled << std::endl;
};

bool Node::equals(Node& other, bool checkDist) {
    bool isEqual = false;
    if (this->row == other.getRow() &&
        this->col == other.getCol())
    {
        isEqual = true;
    }
    if (checkDist) {
        if (this->dist_traveled != other.getDistanceTraveled()) {
            isEqual = false;
        }
    }
    return isEqual;
};

bool Node::getIsVisited() {
    return this->isVisited;
}

void Node::setIsVisited(bool isVisited) {
    this->isVisited = isVisited;
}

bool Node::isWall(Env env) {
    bool isWall = false;
    if (env[this->row][this->col] == SYMBOL_WALL) {
        isWall = true;
    }
    return isWall;
};

bool Node::isValidAdjNode(Env env) {
    bool isValid = false;
    //Assumption made that all nodes in the closed list have been marked as visited
    //Assumption made that maze will always be enclosed in walls
    if (!this->isWall(env) && !this->getIsVisited()) {
        isValid = true;
    }
    return isValid;
};

bool Node::getAdjNode(Direction direction, Node** adjNodePtr) {
    bool adjNodeFound = true;

    //Note that this method assumes that the appropiate dist_travelled will be given after
    if (direction == UP) {
        *adjNodePtr = new Node(this->row - 1, this->col, this->dist_traveled);
    }
    else if (direction == RIGHT) {
        *adjNodePtr = new Node(this->row, this->col + 1, this->dist_traveled);
    }
    else if (direction == DOWN) {
        *adjNodePtr = new Node(this->row + 1, this->col, this->dist_traveled);
    }
    else if (direction == LEFT) {
        *adjNodePtr = new Node(this->row, this->col - 1, this->dist_traveled);
    }
    else {
        adjNodeFound = false;
        std::cout << "Error: Invalid Direction Given" << std::endl;
    }

    adjNodePtr = nullptr;
    delete adjNodePtr;
    return adjNodeFound;
};

//--------------------------------                             