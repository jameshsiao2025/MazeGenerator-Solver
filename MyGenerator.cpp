
#include <iostream>
#include <vector>
#include <random>

#include "MyGenerator.hpp"
#include "Maze.hpp"
#include <ics46/factory/DynamicFactory.hpp>

//track your steps like digging tunnels, never visit a node that you have already been
//two dimensional structure
// void foo(int a, int b)
// {
//     
//     int** a = new int*[a];
//     for(int i=0; i<b; ++i)
//     {
//         a[i] = new int[b];
//     }
//      a[2][3] = 9; 
// }
//
// vector<vector<int>> v(d1, vector<int>(b,0));
// v.at(2).at(3) = 9;

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MyGenerator, "MyGenerator (Required)");
std::random_device device;
std::default_random_engine engine{device()};
std::uniform_int_distribution<int> distribution{0,3};

//get random direction
Direction MyGenerator::getDirection()
{
    int rand = distribution(engine); 
    if(rand == 0)
        return Direction::up;
    else if(rand == 1)
        return Direction::down;
    else if(rand == 2)
        return Direction::left;
    else
        return Direction::right; 
}

//check if a cell is visited
bool MyGenerator::visited(int x, int y , std::vector<std::vector<bool>>& target)
{
    if(x<0||y<0||x>=w||y>=h)
        return true;
    else if(target.at(x).at(y) == true)
        return true;
    else
    {
        return false; 
    } 
}

//check to see if going in a direction will hit the border
bool MyGenerator::border(Maze& maze, Direction target)
{
    int edge = false; 
    if(target == Direction::up) 
    {
        if(currentH == 0)
        edge = true;
        return edge;
    }
    else if(target == Direction::down)
    {
        if(currentH == maze.getHeight())
        edge = true;
        return edge;
    }
    else if(target == Direction::left)
    {
        if(currentW == 0)
        edge = true;
        return edge;
    }
    else if(target == Direction::right)
    {
        if(currentW == maze.getWidth())
        edge = true;
        return edge;
    }
    return edge;
}

//mark a cell as visited
void MyGenerator::visitCell(int x, int y, std::vector<std::vector<bool>>& map)
{
    // map[x][y].x = 0;
    // map[x][y].y = 0;
    map.at(x).at(y) = true;
    //std::cout << x << ", " << y << std::endl; 
}

//see if current cell is a dead end
bool MyGenerator::deadEnd(Maze& maze, std::vector<std::vector<bool>>& map)
{
    bool end = true;

    if(border(maze, Direction::up) == false && visited(getCurrentW(), getCurrentH()-1, map)==false)
    {
        end = false;   
    }
    else if(border(maze, Direction::down) == false && visited(getCurrentW(), getCurrentH()+1, map)==false)
    {
        end = false;
       
    }
    else if(border(maze, Direction::left) == false&&visited(getCurrentW()-1, getCurrentH(), map)==false)
    {
        end = false;
        
    }    
    else if(border(maze, Direction::right) == false&& visited(getCurrentW()+1, getCurrentH(), map)==false)
    {
        end = false;
       
    }
    // if(end == true)
    // {
    //     //std::cout << "dead end" << std::endl;
    // }
    // else{std::cout << "not a dead end" << std::endl;}
    return end;
}

int MyGenerator::newX(Direction d)
{
    if(d==Direction::up||d==Direction::down)
    {
        return getCurrentW();
    }
    else if(d==Direction::left)
    {
        return getCurrentW()-1;
    }
    else
    {
        return getCurrentW()+1;
    }
    
}
int MyGenerator::newY(Direction d)
{
    if(d==Direction::left||d==Direction::right)
    {
        return getCurrentH();
    }
    else if(d==Direction::up)
    {
        return getCurrentH()-1;
    }
    else
    {
        return getCurrentH()+1;
    }
}

void MyGenerator::tunnel(Maze& maze, std::vector<std::vector<bool>>& map)
{
    bool finished = false;
    if(deadEnd(maze, map) == false && finished == false)
    {
        bool path = false;
        Direction d; 
        while(path == false)
        {
            d = getDirection();
            if(border(maze, d)==false&&visited(newX(d), newY(d), map)==false)
                path = true;
        }
        maze.removeWall(currentW, currentH, d);
        //std::cout << currentW << ", " << currentH << ", WALL REMOVED" << std::endl;
        currentW = newX(d);
        currentH = newY(d);
        route.push_back({currentW, currentH});
        visitCell(currentW, currentH, map);
        tunnel(maze, map);
    }
    else
    {
        while(deadEnd(maze, map) == true && route.size()>1)
        {            
            route.pop_back();
            currentW = route.back().x;
            currentH = route.back().y;
            if(currentW == 0 && currentH == 0)
            {
                finished = true;
            }
            //std::cout << currentW << ", " << currentH << ", retraced" << std::endl; 
            tunnel(maze,map);
        }  

    }
}

void MyGenerator::generateMaze(Maze& maze)
{
    maze.addAllWalls();
    w = maze.getWidth();
    h = maze.getHeight();
    //initialize mapping vector
    std::vector<std::vector<bool>> map(w, std::vector<bool>(h, false)); 
    visitCell(0,0,map);
    tunnel(maze, map);
}