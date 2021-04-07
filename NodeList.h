#ifndef COSC_ASSIGN_ONE_NODELIST
#define COSC_ASSIGN_ONE_NODELIST

#include "Types.h"
#include "Node.h"

class NodeList {
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Desctructor
    NodeList();
    ~NodeList();

    // Copy Constructor
    // Produces a DEEP COPY of the NodeList
    NodeList(NodeList& other);

    // Number of elements in the NodeList
    int getLength();

    // Add a COPY node element to the BACK of the nodelist.
    void addElement(Node* newNode);

    // Get a pointer to the ith node in the node list
    Node* getNode(int i);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    //Print NodeList
    void printNodeList();

    //Check if all nodes in NodeList is in closedList
    bool checkAllVisited();

    bool contains(Node* node, bool checkDist);

    void reverseNodesArray();

    //NodeList Constructor and Deconstructor Overload for Milestone 4
    NodeList(int numRows, int numCols);

    //NodeList Copy Constructo for Milestone 4
    NodeList(NodeList& other, int numRows, int numCols);


private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // NodeList: list of node objects
    // You may assume a fixed size for M1, M2, M3
    Node** nodes;

    // Number of nodes currently in the NodeList
    int length;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    //Milestone 4 dynamic Nodelist maxLen
    static int maxNodeListLen;
    //Calculates the max NodeList Length for the given env dimensions
    void calcMaxNodeListLen(int numRows, int numCols);
};


#endif //COSC_ASSIGN_ONE_NODELIST