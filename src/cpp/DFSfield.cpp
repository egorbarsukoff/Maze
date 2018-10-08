//
// Created by egorb on 18.11.2017.
//

#include <iostream>
#include "../DFSfield.h"

DFSfield::DFSfield(int col, int row) : ncol(col), nrow(row) {
    f = new cellState*[nrow];
    for (size_t i = 0; i < nrow; ++i) {
        f[i] = new cellState[ncol];
    }

}

DFSfield::~DFSfield() {
    for (size_t i = 0; i < nrow; ++i) {
        delete[] f[i];
    }
    delete[] f;
}

void DFSfield::cleanField() {
    for (size_t col = 0; col < ncol; ++col) {
        for (size_t row = 0; row < nrow; ++row) {
            if (f[row][col] != WALL)
                f[row][col] = SPACE;
        }
    }
}

void DFSfield::cleanPath() {
    std::stack<position>().swap(path);
}

DFSfield::neighbors DFSfield::unvisitedNeighb(position pos) {
    DFSfield::neighbors neighb;
    position newNeihb;
    if (allowDirection(UP, pos) && getCell(newNeihb = closerCell(UP, pos)) == SPACE) {
        neighb.add(newNeihb);
    }
    if (allowDirection(RIGHT, pos) && getCell(newNeihb = closerCell(RIGHT, pos)) == SPACE) {
        neighb.add(newNeihb);
    }
    if (allowDirection(DOWN, pos) && getCell(newNeihb = closerCell(DOWN, pos)) == SPACE) {
        neighb.add(newNeihb);
    }
    if (allowDirection(LEFT, pos) && getCell(newNeihb = closerCell(LEFT, pos)) == SPACE) {
        neighb.add(newNeihb);
    }
    return neighb;
}

bool DFSfield::allowDirection(DFSfield::direction d, position pos) {
    if (d == UP && pos.x < 1)
        return false;
    if (d == DOWN && pos.x > nrow - 2)
        return false;
    if (d == RIGHT && pos.y > ncol - 2)
        return false;
    if (d == LEFT && pos.y < 1)
        return false;
    return true;
}

position DFSfield::closerCell(DFSfield::direction d, position pos) {
    if (d == UP)
        return position(pos.x-1, pos.y);
    else if (d == RIGHT)
        return position(pos.x, pos.y+1);
    else if (d == DOWN)
        return position(pos.x+1, pos.y);
    else
        return position(pos.x, pos.y-1);
}

void DFSfield::traceback() {
    do  {
        path.pop();
    } while (unvisitedNeighb(path.top()).size == 0 && path.size() > 1);
}

void DFSfield::neighbors::add(position pos) {
    neighborsArray[size] = pos;
    ++size;
}

void DFSfield::createBlank() {
    for (int i = 0; i < nrow; ++i)
        for (int j = 0; j < ncol; ++j)
            f[i][j] = SPACE;
}
