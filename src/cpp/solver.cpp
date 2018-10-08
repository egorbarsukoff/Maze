//
// Created by egorb on 23.10.2017.
//

#include <iostream>
#include "../solver.h"
#include "../display.h"

solver::solver(const maze &myMaze, position pos) :
        DFSfield(myMaze.getNCol(), myMaze.getNRow()),
        m(&myMaze) {
    createBlank();
    path.push(pos);
    while (!m->checkEnd(path.top())) {
        f[path.top().x][path.top().y] = VISITED;
        position next_pos;
        if ((next_pos = getNeighbor()) != path.top()) {
            path.push(next_pos);
        } else {
            traceback();
        }
    }
    cleanField();
}

position solver::getNeighbor() {
    neighbors n = unvisitedNeighb(path.top());
    for(int i = 0; i < n.size; ++i) {
        if (m->checkMove(path.top(), n.neighborsArray[i]))
            return n.neighborsArray[i];
    }
    return path.top();
}

DFSfield::direction solver::getDirection(position from, position to) {
    if (from.y == to.y) {
        if (from.x + 1 == to.x)
            return DOWN;
        if (from.x == to.x + 1)
            return UP;
    }
    if (from.x == to.x) {
        if (from.y + 1 == to.y)
            return LEFT;
        if (from.y == to.y + 1)
            return RIGHT;
    }
}

int solver::getLine(DFSfield::direction a, DFSfield::direction b) {
    if (a == LEFT && b == LEFT || a == RIGHT && b == RIGHT)
        return 196;
    if (a == LEFT && b == UP || a == DOWN && b == RIGHT)
        return 217;
    if (a == UP && b == LEFT || a == RIGHT && b == DOWN)
        return 218;
    if (a == LEFT && b == DOWN || a == UP && b == RIGHT)
        return 191;
    if (a == DOWN && b == LEFT || a == RIGHT && b == UP)
        return 192;
    if (a == UP && b == UP)
        return 179;
    if (a == DOWN && b == DOWN)
        return 179;

}

void solver::printSolution() {
    auto t_path = path;
    direction *d = new direction[path.size()];
    position prevPos = position(t_path.top().x, t_path.top().y+1);
    for (int i = t_path.size() - 1; !t_path.empty() && i >= 0; --i) {
        d[i] = getDirection(prevPos, t_path.top());
        prevPos = t_path.top();
        t_path.pop();
    }
    t_path = path;
    for (int i = t_path.size() - 1; !t_path.empty() && i > 0; --i) {
        gotoxy(t_path.top().y*4 + 2, t_path.top().x*2 + 1);
        printf("%c", getLine(d[i], d[i-1]));
        t_path.pop();
    }
    gotoxy(0, m->getNRow()*2+2);
    hideCursor();
    delete[] d;
}
