//
// Created by egorb on 18.11.2017.
//

#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "maze.h"
#include "position.h"


class solver : public DFSfield{
    const maze *m;
    position getNeighbor();
    direction getDirection(position from, position to);
    int getLine(direction a, direction b);
public:
    void printSolution();
    solver(const maze &myMaze, position pos);
};

#endif //MAZE_SOLVER_H
