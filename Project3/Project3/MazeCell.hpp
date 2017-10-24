#ifndef MazeCell_hpp
#define MazeCell_hpp

#include <stdio.h>
#include <limits.h>
#include <SFML\Graphics.hpp>
#include "Walls.h"

class MazeCell
{
public:
	MazeCell(unsigned __int16 column, unsigned __int16 row, int size, sf::RenderWindow* window);
	~MazeCell();

	unsigned int aStarValue = ULONG_MAX;

	bool isVisited = false, inStack = false, inStart = false, inEnd = false, playerVisited = false, onPath = false, onGrid = false, aiVisited = false, aiTrail = false, aStarVisited = false, aStarTrail = false;
	bool leftWall = true, rightWall = true, topWall = true, bottomWall = true;

	void Draw();

	int GetCollumn() { return collumn; }
	int GetRow() { return row; }

private:
	unsigned __int16 collumn, row;
	int size;
	unsigned __int8 wallWidth = 1;

	sf::RenderWindow* window;
	Walls walls;
};

#endif