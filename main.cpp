#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env, char buffer[MAX_ENV_DIM][MAX_ENV_DIM], int numRows, int numCols);

void getDimensions(char buffer[MAX_ENV_DIM][MAX_ENV_DIM], int& numRows, int& numCols);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution, int numRows, int numCols);

// Milestone 4 Methods
Env make_env(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);


int main(int argc, char** argv) {
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    //buffer to store env readin
    char buffer[MAX_ENV_DIM][MAX_ENV_DIM];

    //read in file to recognize how many rows and cols
    int numRows = 0;
    int numCols = 0;
    getDimensions(buffer, numRows, numCols);

    //reset cin flags
    std::cin.clear();

    //allocate memory accordingly
    // Load Environment 
    Env env = make_env(numRows, numCols);

    readEnvStdin(env, buffer, numRows, numCols);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env, numRows, numCols);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored(numRows, numCols);

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env, numRows, numCols);

    printEnvStdout(env, solution, numRows, numCols);

    delete_env(env, numRows, numCols);
    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env, char buffer[MAX_ENV_DIM][MAX_ENV_DIM], int numRows, int numCols) {
    for (int row = 0; row < numRows && !std::cin.eof(); row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            env[row][col] = buffer[row][col];
        }
    }
}

void printEnvStdout(Env env, NodeList* solution, int numRows, int numCols) {
    //currNode and nextNode's memory will be handled when delete solution is called
    Node* currNode;
    Node* nextNode;
    //Solution assumes startNode and goalNode are included
    //i = 1 to start at node after startNode
    //getLength() - 1 to stop the iteration 1 node short of goalNode
    for (int i = 1; i < solution->getLength() - 1; i++)
    {
        //decide which character to assign env[row][col]
        currNode = solution->getNode(i);
        nextNode = solution->getNode(i + 1);

        if (nextNode->getRow() - currNode->getRow() == -1) {
            env[currNode->getRow()][currNode->getCol()] = SYMBOL_UP;
        }
        else if (nextNode->getRow() - currNode->getRow() == 1) {
            env[currNode->getRow()][currNode->getCol()] = SYMBOL_DOWN;
        }
        else if (nextNode->getCol() - currNode->getCol() == 1) {
            env[currNode->getRow()][currNode->getCol()] = SYMBOL_RIGHT;
        }
        else if (nextNode->getCol() - currNode->getCol() == -1) {
            env[currNode->getRow()][currNode->getCol()] = SYMBOL_LEFT;
        }
        else {
            std::cout << "Error: Unprintable Direction" << std::endl;
        }
    }

    for (int row = 0; row < numRows && !std::cin.eof(); row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            std::cout << env[row][col];
        }
        std::cout << std::endl;
    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
    nodeList->printNodeList();

    delete nodeList;
}

void getDimensions(char buffer[MAX_ENV_DIM][MAX_ENV_DIM], int& numRows, int& numCols) {
    int row = 0;
    int col = 0;
    int numNodes = 0;

    while (!std::cin.eof()) {
        std::cin.get(buffer[row][col]);
        if (buffer[row][col] != '\n' && !std::cin.eof()) {
            ++numNodes;
            ++col;
        }
        else {
            ++numRows;
            ++row;
            col = 0;
        }
    }

    numCols = numNodes / numRows;
}

Env make_env(const int rows, const int cols) {
    Env env = nullptr;

    if (rows >= 0 && cols >= 0) {
        env = new char* [rows];
        for (int i = 0; i != rows; ++i) {
            env[i] = new char[cols];
        }
    }

    return env;
}

void delete_env(Env env, int rows, int cols) {
    if (rows >= 0 && cols >= 0) {
        for (int i = 0; i != rows; ++i) {
            delete env[i];
        }
        delete env;
    }

    return;
}