#ifndef Astar_h
#define Astar_h

#include <vector>
#include <stdio.h>
#include "Maze.hpp"
#include "MazeCell.hpp"
#include <SFML\Graphics.hpp>

class Astar
{
public:
	Astar(unsigned __int16 gridsize, Maze* maze, sf::RenderWindow* window, int startIndex);
	~Astar();

	void GoEveryAvailableNeighbour();

private:

	enum walls
	{
		none,
		top,
		right,
		bottom,
		left
	};

	unsigned __int16 _gridSize;
	int _startIndex;
	int _currentIndex;
	int _currentAstarValue;
	sf::RenderWindow* _window;
	Maze* _maze;
};

#endif