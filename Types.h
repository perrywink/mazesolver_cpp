#ifndef COSC_ASSIGN_ONE_TYPES
#define COSC_ASSIGN_ONE_TYPES

#include <math.h> 


#define ENV_DIM                     20
#define NODE_LIST_ARRAY_MAX_SIZE    4*(ENV_DIM * ENV_DIM)

//Milestone 4 : Maximum Allowable Env Dimensions
#define MAX_ENV_DIM                     2000

// A 2D array to represent the environment or observations
// REMEMBER: in a environment, the location (x,y) is found by maze[y][x]!
typedef char** Env;

#define SYMBOL_WALL     '='
#define SYMBOL_EMPTY    '.'
#define SYMBOL_GOAL     'G'
#define SYMBOL_START    'S'

//Additional defines and enums
#define SYMBOL_UP      '^'
#define SYMBOL_DOWN    'v'
#define SYMBOL_LEFT    '<'
#define SYMBOL_RIGHT   '>'

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

#endif // COSC_ASSIGN_ONE_TYPES