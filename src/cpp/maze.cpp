//
// Created by egorb on 02.11.2017.
//

#include <iostream>
#include "../maze.h"
#include "../display.h"


maze::maze(size_t col, size_t row) : DFSfield(col*2 + 1, row*2 + 1){
    createBlank();
    path.push(position(1, 1));
    position last = path.top();
    for(int unvisitedCount = (ncol-1)*(nrow-1)/4; unvisitedCount > 1; --unvisitedCount) {
        f[path.top().x][path.top().y] = VISITED;
        neighbors neighb;
        if ((neighb = unvisitedNeighb(path.top())).size > 0) {
            position next_pos = neighb.neighborsArray[rand() % neighb.size];
            breakingStep(path.top(), next_pos);
            path.push(next_pos);
        } else {
            traceback();
            ++unvisitedCount;
        }
    }
    cleanField();
    cleanPath();
}


void maze::createBlank() {
    for(int i = 0; i < ncol; i++){
        for(int j = 0; j < nrow; j++){
            if((i % 2 != 0  && j % 2 != 0) && (i < ncol-1 && j < nrow-1))
                f[j][i] = SPACE;
            else
                f[j][i] = WALL;
        }
    }
}


void maze::breakingStep(position from, position to) {
    if (from.x == to.x) {
        f[from.x][(from.y + to.y)/2] = BREAKED;
    } else if (from.y == to.y) {
        f[(from.x + to.x)/2][from.y] = BREAKED;
    }
}

bool maze::checkMove(position from, position to) const {
    positionTransform(from);
    positionTransform(to);
    if (from.y == to.y) {
        if (f[(from.x + to.x)/2][from.y] != WALL)
            return true;
    } else if (from.x == to.x) {
        if (f[from.x][(from.y + to.y)/2]!= WALL)
            return true;
    }
    return false;
}

bool maze::checkEnd(position pos) const{
    return !(pos.y+1 != (ncol-1)/2 || pos.x+1 != (nrow-1)/2);
}

bool maze::allowDirection(direction d, position pos) {
    if (DFSfield::allowDirection(d, pos)) {
        pos = DFSfield::closerCell(d, pos);
        if (DFSfield::allowDirection(d, pos))
            return true;
    }
    return false;
}

position maze::closerCell(DFSfield::direction d, position pos) {
    pos = DFSfield::closerCell(d, pos);
    return DFSfield::closerCell(d, pos);
}

void maze::positionTransform(position &pos) const{
    pos.y =  pos.y*2 + 1;
    pos.x = pos.x*2 + 1;
}

int maze::wallType(position pos) {
    size_t i = pos.x, j = pos.y;
    if (i != 0 && i != nrow - 1 && j != 0 && j != ncol - 1) {
        if (f[i][j + 1] == WALL
            && f[i][j - 1] == WALL
            && f[i + 1][j] == WALL
            && f[i - 1][j] == WALL) {
            return 974;
        } else if ((f[i][j + 1] == WALL
                    || f[i][j - 1] == WALL)
                   && f[i + 1][j] != WALL
                   && f[i - 1][j] != WALL) {
            return 973;
        } else if (f[i][j + 1] != WALL
                   && f[i][j - 1] != WALL
                   && (f[i + 1][j] == WALL
                       || f[i - 1][j] == WALL)) {
            return 954;
        } else if (f[i][j + 1] != WALL
                   && f[i][j - 1] == WALL
                   && f[i + 1][j] != WALL
                   && f[i - 1][j] == WALL) {
            return 956;
        } else if (f[i][j + 1] != WALL
                   && f[i][j - 1] == WALL
                   && f[i + 1][j] == WALL
                   && f[i - 1][j] != WALL) {
            return 955;
        } else if (f[i][j + 1] == WALL
                   && f[i][j - 1] != WALL
                   && f[i + 1][j] == WALL
                   && f[i - 1][j] != WALL) {
            return 969;
        } else if (f[i][j + 1] == WALL
                   && f[i][j - 1] != WALL
                   && f[i + 1][j] != WALL
                   && f[i - 1][j] == WALL) {
            return 968;
        } else if (f[i][j + 1] == WALL
                   && f[i][j - 1] == WALL
                   && f[i + 1][j] == WALL
                   && f[i - 1][j] != WALL) {
            return 971;
        } else if (f[i][j + 1] == WALL
                   && f[i][j - 1] == WALL
                   && f[i + 1][j] != WALL
                   && f[i - 1][j] == WALL) {
            return 970;
        } else if (f[i][j + 1] == WALL
                   && f[i][j - 1] != WALL
                   && f[i + 1][j] == WALL
                   && f[i - 1][j] == WALL) {
            return 972;
        } else if (f[i][j + 1] != WALL
                   && f[i][j - 1] == WALL
                   && f[i + 1][j] == WALL
                   && f[i - 1][j] == WALL) {
            return 953;
        }
    } else if (i == 0 && !(j == 0 || j == ncol - 1)) {
        if (f[i + 1][j] == WALL) {
            return 971;
        } else {
            return 973;
        }
    } else if (i == nrow - 1 && !(j == 0 || j == ncol - 1)) {
        if (f[i - 1][j] == WALL) {
            return 970;
        } else {
            return 973;
        }
    } else if (j == 0 && !(i == 0 || i == nrow - 1)) {
        if (f[i][j + 1] == WALL) {
            return 972;
        } else {
            return 954;
        }
    } else if (j == ncol - 1 && !(i == 0 || i == nrow - 1)) {
        if (f[i][j - 1] == WALL) {
            return 953;
        } else {
            return 954;
        }
    } else if (i == 0 && j == 0) {
        return 969;
    } else if (i == 0 && j == ncol - 1) {
        return 955;
    } else if (i == nrow - 1 && j == 0) {
        return 968;
    } else if (i == nrow - 1 && j == ncol - 1) {
        return 956;
    }
}

void maze::printMaze() {
    gotoxy(0, 0);
    for (int i = 0; i < nrow; ++i) {
        for (int j = 0; j < ncol; ++j) {
            if (f[i][j] == WALL) {
                printf("%c", wallType(position(i, j)));
                if (wallType(position(i, j)) == 973 && (j % 2)) {
                    printf("%c%c",973, 973);
                }
            } else {
                printf(" ");
                if (j%2) {
                    printf("  ");
                }
            }
        }
        printf("\n");
    }
    gotoxy(getNCol()*4, getNRow()*2-1);
    printf(" ");
}
