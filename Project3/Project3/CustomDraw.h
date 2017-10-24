#ifndef CustomDraw_h
#define CustomDraw_h

#include "Maze.hpp"
#include "Inputs.h"
#include <SFML\Graphics.hpp>
#include "AI.h"
#include "Astar.h"

class CustomDraw
{
public:
	CustomDraw(int gridSize, int xPos, int yPos, sf::RenderWindow* window, int resolution, int goalX, int goalY);
	~CustomDraw();

	// Draws 3x3 area from input coordinates
	void DrawFromGrid(int x, int y);
	// Reads inputs and draws area
	void Update();
	// Draws whole maze
	void DrawMaze();
	int CellsToGoal();
	float RunAI1();
	float RunAI2();

private:
	// Draws start grid
	void DrawStartPosition();
	// Draws goal grid
	void DrawEndPosition();

	void WinCondition();

	// Start position, constructor modifies these later
	const int _startX = 0;
	const int _startY = 0;
	// Goal position, constructor modifies these later
	const int _endX = 0;
	const int _endY = 0;
	// Private parameters
	int _gridSize;
	int _x;
	int _y;
	int _playerIndex;
	int _resolution;
	int _inputDirection;
	bool _initFlag;
	bool _aiFlag;
	sf::RenderWindow* _window;
	Maze* _maze;
	AI* _ai;
	Astar* _astar;
	sf::Time playerTime;
	sf::Clock _playerClock;
	bool _playerTime;


	Inputs _input;
};

#endif


