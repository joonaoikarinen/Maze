#include "Astar.h"
#include "MazeCell.hpp"
#include <iostream>
#include "Maze.hpp"
#include "CustomDraw.h"


Astar::Astar(unsigned __int16 gridsize, Maze* maze, sf::RenderWindow* window, int startIndex)
{
	_gridSize = gridsize;
	_maze = maze;
	_window = window;
	_startIndex = startIndex;
	_maze->cells[startIndex]->aStarVisited = true;
	_maze->cells[startIndex]->aStarValue = 0;
	_currentAstarValue = 0;
}


Astar::~Astar()
{

}


void Astar::GoEveryAvailableNeighbour()
{
	bool onGoal = false;
	int x = 0;
	while(!onGoal)
	{
		for (int luku = _maze->cells.size(); luku--;)
		{
			if (_maze->cells[x]->aStarValue == _currentAstarValue)
			{
				if(_maze->cells[x]->inEnd == true)
				{
					//std::cout << "Maali indexi on " << x << std::endl;
					onGoal = true;
				}
				if (_maze->cells[x]->rightWall == false && _maze->cells[x + _gridSize]->aStarVisited == false)
				{
					_maze->cells[x + _gridSize]->aStarVisited = true;
					_maze->cells[x + _gridSize]->aStarValue = _currentAstarValue + 1;
				}
				if (_maze->cells[x]->bottomWall == false && _maze->cells[x + 1]->aStarVisited == false)
				{
					_maze->cells[x + 1]->aStarVisited = true;
					_maze->cells[x + 1]->aStarValue = _currentAstarValue + 1;
				}
				if (_maze->cells[x]->leftWall == false && _maze->cells[x - _gridSize]->aStarVisited == false)
				{
					_maze->cells[x - _gridSize]->aStarVisited = true;
					_maze->cells[x - _gridSize]->aStarValue = _currentAstarValue + 1;
				}
				if (_maze->cells[x]->topWall == false && _maze->cells[x - 1]->aStarVisited == false)
				{
					_maze->cells[x - 1]->aStarVisited = true;
					_maze->cells[x - 1]->aStarValue = _currentAstarValue + 1;
				}
			}
			x++;
		}
			x = 0;
		_currentAstarValue = _currentAstarValue + 1;
	}
}