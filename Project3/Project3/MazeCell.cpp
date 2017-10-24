#include "MazeCell.hpp"
#include <iostream>
#include "Walls.h"

MazeCell::MazeCell(unsigned __int16 collumn, unsigned __int16 row, int size, sf::RenderWindow* window) : collumn(collumn), row(row), size(size), window(window), walls(window, collumn, row, size)
{

}

MazeCell::~MazeCell()
{

}


void MazeCell::Draw()
{
	sf::Color onlyRightColor;
	if (onGrid)
	{
		onlyRightColor = sf::Color(206, 72, 153, 255);
	}
	else if (playerVisited && !inStart)
	{
		onlyRightColor = sf::Color(84, 255, 153, 255);
	}
	else if (inEnd)
	{
		onlyRightColor = sf::Color(0, 255, 0, 255);
	}
	else if(aStarTrail)
	{
		onlyRightColor = sf::Color(255, 100, 100, 255);
	}
	else if (aiVisited)
	{
		onlyRightColor = sf::Color(102, 0, 204, 255);
	}
	else if (aiTrail)
	{
		onlyRightColor = sf::Color(102, 0, 204, 255);
	}
	else if (inStart)
	{
		onlyRightColor = sf::Color(255, 0, 0, 255);
	}
	else if (onPath && !inStart)
	{
		//onlyRightColor = sf::Color(200, 200, 200, 255);
		onlyRightColor = sf::Color(255, 255, 255, 255);
	}
	else if (inStack)
	{
		onlyRightColor = sf::Color(255, 0, 0, 255);
	}
	else if (isVisited && !inStart)
	{
		onlyRightColor = sf::Color(255, 255, 255, 255);
	}

	walls.DrawCurrentCell(onlyRightColor);
	walls.DrawWalls(leftWall, topWall, rightWall, bottomWall, wallWidth);
}
