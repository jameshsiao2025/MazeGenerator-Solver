#ifndef MYSOLVER_H
#define MYSOLVER_H

#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Direction.hpp"
#include "Maze.hpp"

class MySolver : public MazeSolver
{
private:

bool noSolution = false; 

struct Cell
{
    int x;
    int y;
    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;
    bool end = false; 
};

std::vector<Cell> path; 

public:

void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
void options(const Maze& maze, MazeSolution& mazeSolution, std::vector<Cell>& path);
void move(const Maze& maze, MazeSolution& mazeSolution, std::vector<Cell>& path);
bool solve(const Maze& maze, MazeSolution& mazeSolution, std::vector<Cell>& path);

};

#endif