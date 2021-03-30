#include "NodeList.h"
#include <iostream>

NodeList::NodeList() {
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        nodes[i] = nullptr;
    }
}

NodeList::~NodeList() {
    //nodes cleanup
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        if (nodes[i] != nullptr) {
            delete nodes[i];
        };
    }
}

NodeList::NodeList(NodeList& other) {
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        //Deep copy of nodes
        nodes[i] = new Node(*other.getNode(i));
    }
}

int NodeList::getLength() {
    return this->length;
}

void NodeList::addElement(Node* newPos) {
    //Append node ptr to end of array
    nodes[this->length] = newPos;
    ++(this->length);
}

Node* NodeList::getNode(int i) {
    return nodes[i];
}

//Additional Methods
void NodeList::printNodeList() {
    for (int i = 0; i < this->length; i++)
    {
        nodes[i]->printNode();
    }
};

bool NodeList::isEqualLength(NodeList& other) {
    bool isEqualLength = false;
    if (this->length == other.getLength()) {
        isEqualLength = true;
    }
    return isEqualLength;
};