#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver {
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    //Milestone 4 Overloaded Functions
    void forwardSearch(Env env, int numRows, int numCols);
    bool findNodeInEnv(Env env, char targetNod, Node** foundNode, int numRows, int numCols);
    NodeList* getPath(Env env, int numRows, int numCols);
    NodeList* getNodesExplored(int numRows, int numCols);

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    // Private helper methods 

    // Converts integer into direction enums
    Direction convertIntToDir(int dirInt);

    // Finds the start and goal nodes in env
    bool findNodeInEnv(Env env, char targetNod, Node** foundNode);

    // Selects the next node P
    bool findNextNodeP(Node*& nodeP, NodeList* openList, NodeList* closedList, Node* goalNode);

};




#endif //COSC_ASSIGN_ONE_PATHSOLVER