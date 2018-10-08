//
// Created by egorb on 23.10.2017.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include "position.h"

#include "DFSfield.h"

#include <cstdlib>


class maze : public DFSfield {
    int wallType(position pos);
    void positionTransform(position &pos) const;
    void breakingStep(position from, position to);
    void createBlank();
public:
    int getNCol() const {return (ncol-1)/2;}
    int getNRow() const {return (nrow-1)/2;}
    position closerCell(direction d, position pos);
    bool allowDirection(direction d, position pos);
    void printMaze();
    bool checkMove(position from, position to) const;
    bool checkEnd(position pos) const;
    maze(size_t col, size_t row);
};


#endif //MAZE_MAZE_H
