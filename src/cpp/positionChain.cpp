#include <cstdlib>
#include "../position.h"

//positionChain::positionChain() {
//    length = 0;
//    currPos = nullptr;
//}

//positionChain::~positionChain() {
//    Node *next;
//    do {
//        next = currPos->prev;
//        delete currPos;
//        currPos = next;
//    } while (next != nullptr);
//}

//void positionChain::add(position pos) {
//    ++length;
//    currPos = new Node(pos, currPos);
//}

//position positionChain::stepBack() {
//    Node *t = currPos;
//    currPos = currPos->prev;
//    --length;
//    delete t;
//}

//position positionChain::last() {
//    return currPos->curr;
//}

//positionChain::Node::Node(position c, Node *p) {
//    curr = c;
//    prev = p;
//}

position::position(size_t tx, size_t ty) {
    x = tx; y = ty;
}

//size_t positionChain::getLength() {
//    return length;
//}

position position::closerCell(direction d) {
    if (d == UP)
        return position(x, y-1);
    else if (d == RIGHT)
        return position(x+1, y);
    else if (d == DOWN)
        return position(x, y+1);
    else
        return position(x-1, y);
}

bool position::operator==(const position &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool position::operator!=(const position &rhs) const {
    return !(rhs == *this);
}
