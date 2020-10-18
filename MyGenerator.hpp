#ifndef MYGENERATOR_H
#define MYGENERATOR_H


#include "MazeGenerator.hpp"
#include "Direction.hpp"


class MyGenerator : public MazeGenerator
{

private:

struct cell
{
  int x = 0;
  int y = 0;  
};

int w;
int h;
int currentW = 0;
int currentH = 0;
std::vector<cell> route;

public: 

virtual void generateMaze(Maze& maze);

Direction getDirection();

int getCurrentW()
{
    return currentW;
}

int getCurrentH()
{
    return currentH;
}

void visitCell(int, int, std::vector<std::vector<bool>>&);

bool visited(int , int, std::vector<std::vector<bool>>&);

bool border(Maze&, Direction);

bool deadEnd(Maze&, std::vector<std::vector<bool>>&); 

void tunnel(Maze&, std::vector<std::vector<bool>>&);

int newX(Direction);
int newY(Direction);

};

#endif 
