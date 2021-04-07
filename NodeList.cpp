#include "NodeList.h"
#include <iostream>

//Init Class Variable for NodeList
int NodeList::maxNodeListLen = DEFAULT_LIST_LEN;

// Original NodeList Constructor for Milestone 2-3
NodeList::NodeList()
{
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        nodes[i] = nullptr;
    }
    this->length = 0;
}

// Original NodeList Destructor for Milestone 2-3
// NodeList::~NodeList() {
//     //nodes cleanup
//     for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
//     {
//         if (nodes[i] != nullptr) {
//             delete nodes[i];
//             nodes[i] = nullptr;
//         };
//     }
// }

//Milestone 4 Destructor
NodeList::~NodeList()
{
    //nodes cleanup
    for (int i = 0; i < NodeList::maxNodeListLen; i++)
    {
        if (nodes[i] != nullptr)
        {
            delete nodes[i];
            nodes[i] = nullptr;
        };
    }
    delete nodes;
}

// Original NodeList Copy Constructor for Milestone 2-3
NodeList::NodeList(NodeList& other)
{
    this->length = other.getLength();
    for (int i = 0; i < this->length; i++)
    {
        //Deep copy of nodes and length
        nodes[i] = new Node(*other.getNode(i));
    }
}

int NodeList::getLength()
{
    return this->length;
}

void NodeList::addElement(Node* newPos)
{
    //Append node ptr to end of array
    nodes[this->length] = new Node(*newPos);
    ++(this->length);
}

Node* NodeList::getNode(int i)
{
    return nodes[i];
}

//Additional Methods
void NodeList::printNodeList()
{
    for (int i = 0; i < this->length; i++)
    {
        nodes[i]->printNode();
    }
};

bool NodeList::contains(Node* node, bool checkDist)
{
    bool contains = false;
    for (int i = 0; i < this->length; i++)
    {
        if (this->nodes[i]->equals(*node, checkDist))
        {
            contains = true;
        }
    }
    return contains;
}

void NodeList::reverseNodesArray()
{
    Node* tmp = nullptr;
    for (int low = 0, high = (this->length - 1); low < high; low++, high--)
    {
        tmp = nodes[low];
        nodes[low] = nodes[high];
        nodes[high] = tmp;
    }
    tmp = nullptr;
}

NodeList::NodeList(int numRows, int numCols)
{
    calcMaxNodeListLen(numRows, numCols);
    nodes = new Node * [maxNodeListLen];
    for (int i = 0; i < maxNodeListLen; i++)
    {
        nodes[i] = nullptr;
    }
    this->length = 0;
}

NodeList::NodeList(NodeList& other, int numRows, int numCols)
{
    calcMaxNodeListLen(numRows, numCols);
    nodes = new Node * [maxNodeListLen];
    this->length = other.getLength();
    for (int i = 0; i < this->length; i++)
    {
        //Deep copy of nodes and length
        nodes[i] = new Node(*other.getNode(i));
    }
}

void NodeList::calcMaxNodeListLen(int numRows, int numCols) {
    if (NodeList::maxNodeListLen == DEFAULT_LIST_LEN) {
        NodeList::maxNodeListLen = 4 * (numRows * numCols);
    }
}