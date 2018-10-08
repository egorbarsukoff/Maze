cmake_minimum_required(VERSION 3.8)
project(maze)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(SOURCE_FILES main.cpp src/game.h src/cpp/game.cpp src/cpp/solver.cpp src/maze.h src/position.h src/cpp/positionChain.cpp src/cpp/maze.cpp src/cpp/display.cpp src/display.h src/solver.h src/cpp/DFSfield.cpp src/DFSfield.h)
add_executable(maze ${SOURCE_FILES})