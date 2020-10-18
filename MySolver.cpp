#include "MySolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MySolver, "MySolver (Required)");

void MySolver::options(const Maze& maze, MazeSolution& mazeSolution, std::vector<Cell>& path)
{
    path.push_back({mazeSolution.getCurrentCell().first, mazeSolution.getCurrentCell().second, true, true, true, true, false});
    path.back().up = maze.wallExists(mazeSolution.getCurrentCell().first, mazeSolution.getCurrentCell().second, Direction::up);
    path.back().down = maze.wallExists(mazeSolution.getCurrentCell().first, mazeSolution.getCurrentCell().second, Direction::down);
    path.back().left = maze.wallExists(mazeSolution.getCurrentCell().first, mazeSolution.getCurrentCell().second, Direction::left);
    path.back().right = maze.wallExists(mazeSolution.getCurrentCell().first, mazeSolution.getCurrentCell().second, Direction::right);
    //if(mazeSolution.getMovements().size() > 1)
    // {
    //     if(mazeSolution.getMovements().back() == Direction::up)
    //     {
    //         path.back().up = true; 
    //     }
    //     else if(mazeSolution.getMovements().back() == Direction::down)
    //     {
    //         path.back().down = true; 
    //     }
    //     else if(mazeSolution.getMovements().back() == Direction::left)
    //     {
    //         path.back().left = true; 
    //     }
    //     else if(mazeSolution.getMovements().back() == Direction::right)
    //     {
    //         path.back().right = true; 
    //     }
    // }

    if(path.back().up==true && path.back().down==true && path.back().left==true && path.back().right==true)
    {
        path.back().end = true;
        //std::cout << "dead end" << std::endl; 
    }

    // std::cout <<" x:" << path.back().x << " y:" << path.back().y << " Up:"<< path.back().up << " down:" << path.back().down << " left:" 
    // << path.back().left << " right:" <<  path.back().right << " end:" 
    // << path.back().end << std::endl; 

}

void MySolver::move(const Maze& maze, MazeSolution& mazeSolution, std::vector<Cell>&)
{
    if(path.back().end == false)
    {
        if(path.back().down == false)
        {
            path.back().down = true; 
            if(path.back().up==true && path.back().down==true && path.back().left==true && path.back().right==true)
                {
                    path.back().end = true; 
                }
             mazeSolution.extend(Direction::down);
             options(maze, mazeSolution, path);
             path.back().up = true;   
            if(path.back().up==true && path.back().down==true && path.back().left==true && path.back().right==true)
                {
                    path.back().end = true; 
                }         
        }
        else if(path.back().right == false)
        {
            path.back().right = true; 
            if(path.back().up==true && path.back().down==true && path.back().left==true && path.back().right==true)
                {
                    path.back().end = true; 
                }
             mazeSolution.extend(Direction::right);
              //std::cout << mazeSolution.getCurrentCell().first << " " << mazeSolution.getCurrentCell().second << " " << path.size() <<std::endl;
             options(maze, mazeSolution, path);
             path.back().left = true;  
            if(path.back().up==true && path.back().down==true && path.back().left==true && path.back().right==true)
                {
                    path.back().end = true; 
                }            
        }
        else if(path.back().up == false)
        {
            path.back().up = true; 
            if(path.back().up==true && path.back().down==true && path.back().left==true && path.back().right==true)
                {
                    path.back().end = true; 
                }
             mazeSolution.extend(Direction::up);
            if(mazeSolution.getCurrentCell()==mazeSolution.getStartingCell()&&path.size()>10)
            {
                //std::cout << "back to the begining" << std::endl;
                noSolution = true;
            }
             // std::cout << mazeSolution.getCurrentCell().first << " " << mazeSolution.getCurrentCell().second << " " << path.size() <<std::endl;
             options(maze, mazeSolution, path);
             path.back().down = true;  
            if(path.back().up==true && path.back().down==true && path.back().left==true && path.back().right==true)
                {
                    path.back().end = true; 
                }            
        }
        else if(path.back().left == false)
        {
            path.back().left = true; 
            if(path.back().up==true && path.back().down==true && path.back().left==true && path.back().right==true)
                {
                    path.back().end = true; 
                }
             mazeSolution.extend(Direction::left);
            if(mazeSolution.getCurrentCell()==mazeSolution.getStartingCell()&&path.size()>10)
            {
                //std::cout << "back to the begining" << std::endl;
                noSolution = true;
            }
             // std::cout << mazeSolution.getCurrentCell().first << " " << mazeSolution.getCurrentCell().second << " " << path.size() <<std::endl;
             options(maze, mazeSolution, path);
             path.back().right = true; 
            if(path.back().up==true && path.back().down==true && path.back().left==true && path.back().right==true)
                {
                    path.back().end = true; 
                }             
        }
    // std::cout <<" x:" << path.back().x << " y:" << path.back().y << " Up:"<< path.back().up << " down:" << path.back().down << " left:" 
    // << path.back().left << " right:" <<  path.back().right << " end:" 
    // << path.back().end << std::endl; 
    }
    else
    {
        //std::cout << "dead end" << std::endl;
        if(path.size()>0)
        {
            mazeSolution.backUp();
            path.pop_back();
           
        }
    }
    
}

bool MySolver::solve(const Maze& maze, MazeSolution& mazeSolution, std::vector<Cell>& path)
{
    bool finished = false; 
    //std::cout << "did it end: " <<(mazeSolution.getCurrentCell() == mazeSolution.getEndingCell()) << std::endl;
    if(finished == false)
    {  
        if(mazeSolution.isComplete() == true ||mazeSolution.getCurrentCell() == mazeSolution.getEndingCell())
        {
            return true;
        }
        if(noSolution == true) 
        {
            return true;
        }
        move(maze, mazeSolution, path);
        finished = solve(maze, mazeSolution, path);
        if(finished == true)
        {
            return true;
        }       
    }
    return finished;
}

void MySolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    mazeSolution.restart();
    options(maze,mazeSolution, path);
    //std::cout << mazeSolution.getEndingCell().first << " " << mazeSolution.getEndingCell().second << std::endl; 
    solve(maze, mazeSolution, path); 
}
