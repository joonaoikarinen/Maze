#include "AI.h"
#include "MazeCell.hpp"
#include <iostream>
#include "Maze.hpp"
#include "CustomDraw.h"

AI::AI(int gridsize, Maze* maze, sf::RenderWindow* window, int startIndex)
{
	_gridsize = gridsize;
	_maze = maze;
	_aiPositionIndex = startIndex;
	_window = window;
	_lastState = none;
	nextDirection = none;
	doned = false;
	firstTime = true;
}

AI::~AI()
{
	//std::cout << "RHR destroyed" << std::endl;
}

void AI::start()
{
	// First direction to go before loop
	walls direction = SearchDirections();
	// While we are not in goal
	while (!doned)
	{
		// Mooove
		Move(direction);
		// Storage moves in vector for later use (drawing etc)
		_aimoves.push_back(_aiPositionIndex);
	}

	/*
	std::cout << "AI MOVES" << std::endl;
	for(int x = 0; x < _aimoves.size(); x++)
	{
		std::cout << x << " " << _aimoves[x] << std::endl;
	}
	*/
}

void AI::Move(walls firstmove)
{
	// Ask next pos
	nextDirection = ChooseCorrectDirection();
	// If first time in loop
	if (firstTime)
	{
		nextDirection = firstmove;
		firstTime = false;
	}

	// Take 'right' direction
	switch (nextDirection)
	{
	case walls::right:
		//std::cout << "Right" << std::endl;
		_aiPositionIndex = _aiPositionIndex + _gridsize;
		//_maze->cells[_aiPositionIndex]->aiVisited = true;
		_lastState = right;
		break;
	case walls::bottom:
		//std::cout << "Bottom" << std::endl;
		_aiPositionIndex++;
		//_maze->cells[_aiPositionIndex]->aiVisited = true;
		_lastState = bottom;
		break;
	case walls::left:
		//std::cout << "Left" << std::endl;
		_aiPositionIndex = _aiPositionIndex - _gridsize;
		//_maze->cells[_aiPositionIndex]->aiVisited = true;
		_lastState = left;
		break;
	case walls::top:
		//std::cout << "Up" << std::endl;
		_aiPositionIndex--;
		//_maze->cells[_aiPositionIndex]->aiVisited = true;
		_lastState = top;
		break;
	case walls::none:
		//std::cout << "None" << std::endl;
		break;
	// Error handling
	default:
		std::cout << "Problem at switch on AI.cpp file" << std::endl;
		break;
	}

	if (_maze->cells[_aiPositionIndex]->inEnd == true)
	{
		//std::cout << "I did it!" << std::endl;
		doned = true;
	}
}

AI::walls AI::SearchDirections()
{	
	if (_maze->cells[_aiPositionIndex]->rightWall != true) return walls::right;
	else if (_maze->cells[_aiPositionIndex]->bottomWall != true) return walls::bottom;
	else if (_maze->cells[_aiPositionIndex]->leftWall != true) return walls::left;
	else if (_maze->cells[_aiPositionIndex]->topWall != true) return walls::top;
	else return none;
}

AI::walls AI::ChooseCorrectDirection()
{
	if(_lastState == right)
	{
		if (_maze->cells[_aiPositionIndex]->bottomWall != true) return walls::bottom;
		else if (_maze->cells[_aiPositionIndex]->rightWall != true) return walls::right;
		else if (_maze->cells[_aiPositionIndex]->topWall != true) return walls::top;
		else if (_maze->cells[_aiPositionIndex]->leftWall != true) return walls::left;
		else return none;
	}
	if (_lastState == bottom)
	{
		if (_maze->cells[_aiPositionIndex]->leftWall != true) return walls::left;
		else if (_maze->cells[_aiPositionIndex]->bottomWall != true) return walls::bottom;
		else if (_maze->cells[_aiPositionIndex]->rightWall != true) return walls::right;
		else if (_maze->cells[_aiPositionIndex]->topWall != true) return walls::top;
		else return none;
	}
	if (_lastState == left)
	{
		if (_maze->cells[_aiPositionIndex]->topWall != true) return walls::top;
		else if (_maze->cells[_aiPositionIndex]->leftWall != true) return walls::left;
		else if (_maze->cells[_aiPositionIndex]->bottomWall != true) return walls::bottom;
		else if (_maze->cells[_aiPositionIndex]->rightWall != true) return walls::right;
		else return none;
	}
	if (_lastState == top)
	{
		if (_maze->cells[_aiPositionIndex]->rightWall != true) return walls::right;
		else if (_maze->cells[_aiPositionIndex]->topWall != true) return walls::top;
		else if (_maze->cells[_aiPositionIndex]->leftWall != true) return walls::left;
		else if (_maze->cells[_aiPositionIndex]->bottomWall != true) return walls::bottom;
		else return none;
	}
	if(_lastState == none)
	{
		return none;
	}
}