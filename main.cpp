#include <cstdlib>
#include <ctime>
#include "src/maze.h"
#include "src/game.h"


int main() {
    setConsoleSize(1700, 900);
    srand(time(0));
    displayInfo(30);
    maze myMaze(20, 30);
    myMaze.printMaze();
    game g(myMaze);
    printf("\n");
    system("pause");
}