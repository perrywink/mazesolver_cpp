#include "NodeList.h"
#include <iostream>

NodeList::NodeList() {
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        nodes[i] = nullptr;
    }
    this->length = 0;
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
    for (int i = 0; i < other.getLength(); i++)
    {
        //Deep copy of nodes and length
        nodes[i] = new Node(*other.getNode(i));
        this->length = other.getLength();
    }

}

int NodeList::getLength() {
    return this->length;
}

void NodeList::addElement(Node* newPos) {
    //Append node ptr to end of array
    nodes[this->length] = new Node(*newPos);
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

bool NodeList::checkAllVisited() {
    bool allVisited = true;
    for (int i = 0; i < this->length; i++)
    {
        if (nodes[i]->getIsVisited() == false) {
            allVisited = false;
        }
    }
    return allVisited;

}

bool NodeList::contains(Node* node, bool checkDist) {
    bool contains = false;
    for (int i = 0; i < this->length; i++)
    {
        if (this->nodes[i]->equals(*node, checkDist)) {
            contains = true;
        }
    }
    return contains;
}

void NodeList::reverseNodesArray() {
    Node* tmp = nullptr;
    for (int low = 0, high = (this->length - 1); low < high; low++, high--) {
        tmp = nodes[low];
        nodes[low] = nodes[high];
        nodes[high] = tmp;
    }
    tmp = nullptr;

}