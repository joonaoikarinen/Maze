#ifndef AI_h
#define AI_h

#include <vector>
#include <stdio.h>
#include "Maze.hpp"
#include "MazeCell.hpp"
#include <SFML\Graphics.hpp>

class AI
{
public:
	AI(int gridsize, Maze* maze, sf::RenderWindow* window, int startIndex);
	~AI();

	void start();

	//std::vector<int> returnAiMoves() { return _aimoves; }
	std::vector<int> _aimoves;

private:

	bool doned;
	bool firstTime;

	enum walls
	{
		none,
		top,
		right,
		bottom,
		left
	};
	
	int _gridsize;
	int _aiPositionIndex;
	
	walls _lastState;
	walls SearchDirections();
	walls ChooseCorrectDirection();
	walls nextDirection;
	void Move(walls firstDir);

	sf::RenderWindow* _window;
	Maze* _maze;
};

#endif