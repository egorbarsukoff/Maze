#include <conio.h>
#include "../game.h"
#include "../solver.h"


game::game(maze &o) : curMaze(&o), pos(position(0, 0)) {
    charachterInit();
    state = true;
    while (state && !curMaze->checkEnd(pos)){
        keyListenAndCall();
    }
    printf("Game over!");
}

void game::keyListenAndCall() {
    enum direction {LEFT = 75, UP = 72, RIGHT = 77, DOWN = 80};
    int a = getch();
    if (a == 0 || a == 0xE0)
        a = getch();
    if     (a == LEFT ||
            a == RIGHT ||
            a == UP ||
            a == DOWN)
        step(arrowTranslate(a));
    else if (a == 27)
        gameOver();
    else if (a == 68)
        surrender();
}

direction game::arrowTranslate(int d) {
    switch (d) {
        case 75:
            return LEFT;
        case 72:
            return UP;
        case 77:
            return RIGHT;
        case 80:
            return DOWN;
    }
}

void game::step(direction d) {
    position prevPos = pos;
    bool moveAllowed = false;
    if (d == LEFT && (moveAllowed = curMaze->checkMove(pos, position(pos.x, pos.y-1))))
        pos = position(pos.x, pos.y-1);
    else if (d == RIGHT && (moveAllowed = curMaze->checkMove(pos, position(pos.x, pos.y+1))))
        pos = position(pos.x, pos.y+1);
    else if (d == UP && (moveAllowed = curMaze->checkMove(pos, position(pos.x-1, pos.y))))
        pos = position(pos.x-1, pos.y);
    else if (d == DOWN && (moveAllowed = curMaze->checkMove(pos, position(pos.x+1, pos.y))))
        pos = position(pos.x+1, pos.y);
    if (moveAllowed)
        charachterStep(prevPos);
}

void game::surrender() {
    solver(*curMaze, pos).printSolution();
    state = false;
}

void game::gameOver() {
    state = false;
}

void game::charachterInit() {
    gotoxy(2, 1);
    printf("c");
    gotoxy(0, curMaze->getNRow()*2+2);
    hideCursor();
}

void game::charachterStep(position prevPos) {
    gotoxy(prevPos.y*4+2, prevPos.x*2+1);
    printf(" ");
    gotoxy(pos.y*4+2, pos.x*2+1);
    printf("c");
    gotoxy(0, curMaze->getNRow()*2+2);
    hideCursor();
}

