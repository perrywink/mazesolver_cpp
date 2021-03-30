#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
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
    int manhDist = abs(rowDiff) - abs(colDiff);
    return manhDist + this->dist_traveled;
}

//Additional Methods
Node::Node(Node& other) {
    this->row = other.getRow();
    this->col = other.getCol();
};

void Node::printNode() {
    std::cout << "Node - row: " << this->row
        << ", col: " << this->col
        << ", dist_traveled:" << this->dist_traveled << std::endl;
};

//--------------------------------                             