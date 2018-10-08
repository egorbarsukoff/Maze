//
// Created by egorb on 02.11.2017.
//

#ifndef MAZE_DISPLAY_H
#define MAZE_DISPLAY_H

#include <cstdio>
#include <windows.h>

#include "position.h"
#include "maze.h"


void gotoxy(int x, int y);
void hideCursor();
void setConsoleSize(int x, int y);
void displayInfo(int y);

#endif //MAZE_DISPLAY_H
