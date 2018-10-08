//
// Created by egorb on 02.11.2017.
//

#ifndef MAZE_GAME_H
#define MAZE_GAME_H

#include "maze.h"

#include "display.h"

class game {
    position pos;
    maze *curMaze;
    bool state;
    direction arrowTranslate(int d);
    void keyListenAndCall();
    void step(direction d);
    void surrender();
    void gameOver();
    void charachterStep(position prevPos);
    void charachterInit();
public:
    game(maze &o);
};

#endif //MAZE_GAME_H
