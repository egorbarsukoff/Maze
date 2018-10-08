//
// Created by egorb on 18.11.2017.
//

#ifndef MAZE_FIELD_H
#define MAZE_FIELD_H

#include "position.h"

class DFSfield {
protected:
    struct neighbors{
        position neighborsArray[4];
        short size;
        neighbors() : size(0) {};
        void add(position pos);
    };
    enum cellState {WALL, SPACE, BREAKED, VISITED};
    enum direction {RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3};
    cellState **f;
    int ncol, nrow;
    positionChain path;
    void cleanField();
    void cleanPath();
    void traceback();
    cellState getCell(position pos) { return f[pos.x][pos.y];}
    neighbors unvisitedNeighb(position pos);
    virtual position closerCell(direction d, position pos);
    virtual bool allowDirection(direction d, position pos);
    virtual void createBlank();

public:
    virtual int getNCol() const {return ncol;}
    virtual int getNRow() const {return nrow;}
    DFSfield(int ncol, int nrow);
    virtual ~DFSfield();
};

#endif //MAZE_FIELD_H
