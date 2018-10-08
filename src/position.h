//
// Created by egorb on 02.11.2017.
//

#ifndef MAZE_POSITION_H
#define MAZE_POSITION_H

#include <cstdio>
#include <stack>


enum direction {RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3};

struct position {
    size_t x;
    size_t y;
    position closerCell(direction d);
    position(size_t tx, size_t ty);
    bool operator==(const position &rhs) const;
    bool operator!=(const position &rhs) const;
    position() = default;
};

using positionChain = std::stack<position>;


//class positionChain {
//    struct Node {
//        position curr;
//        Node *prev;
//        Node(position c, Node *p);
//    };
//    size_t length;
//    Node* currPos;
//public:
//    explicit positionChain();
//    ~positionChain();
//    void add(position pos);
//    position stepBack();
//    position last();
//    size_t getLength();
//};

#endif //MAZE_POSITION_H
