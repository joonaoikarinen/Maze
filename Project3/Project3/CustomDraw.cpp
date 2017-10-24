#include <iostream>
#include "CustomDraw.h"
#include "Inputs.h"
#include "Maze.hpp"
#include "AI.h"
#include "Astar.h"

CustomDraw::CustomDraw(int gridSize, int xPos, int yPos, sf::RenderWindow* window, int resolution, int goalX, int goalY)
{
	// Modifies private const integers
	int* ptr = const_cast<int*>(&_startX);
	*ptr = xPos;
	ptr = const_cast<int*>(&_startY);
	*ptr = yPos;
	ptr = const_cast<int*>(&_endX);
	*ptr = goalX;
	ptr = const_cast<int*>(&_endY);
	*ptr = goalY;

	// Prints start x & y
	//std::cout << "Start position x: " << _startX << std::endl;
	//std::cout << "Start position y: " << _startY << std::endl;
	//std::cout << "End position x: " << _endX << std::endl;
	//std::cout << "End position y: " << _endY << std::endl << std::endl << std::endl;
	_gridSize = gridSize;
	std::cout << "Gridsize: " << _gridSize << std::endl;

	// Declares parameters
	_x = xPos;
	_y = yPos;

	int startIndex = yPos + (xPos * _gridSize);

	_inputDirection = 0;
	_initFlag = false;
	_aiFlag = false;
	_playerTime = false;

	_resolution = resolution;
	_window = window;
	_maze = new Maze(_resolution, _resolution, _gridSize, _gridSize, _window, _x, _y, goalX, goalY);
	_maze->OwnRemoveWalls();

	_playerIndex = _maze->GetMazeCellIndexByPosition(xPos, yPos);

	//_ai = new AI(_gridSize, _maze, _window, startIndex);
	//_ai->start();
}

CustomDraw::~CustomDraw()
{
	_maze->~Maze();
	//std::cout << "CustomDraw class destroyed successfully" << std::endl;
}

void CustomDraw::Update()
{
	_inputDirection = _input.returnDirection();

	// 7 == R
	if (_inputDirection == 7)
	{
		for (int x = 0; x < _maze->cells.size(); x++)
		{
			_maze->cells[x]->aiTrail = false;
		}

		DrawMaze();
	}

	// Pys‰ytt‰‰ normi mazen piirt‰misen
	// 6 == E
	if (_inputDirection == 6)
	{
		std::cout << "Wannabe a* calculation time: ";
		sf::Clock clock;
		clock.restart();

		_initFlag = true;
		_astar = new Astar(_gridSize, _maze, _window, 0);
		_astar->GoEveryAvailableNeighbour();

		sf::Time sftime = clock.restart();
		float time = sftime.asSeconds();
		std::cout << time << std::endl;

		bool whileFlag = false;
		bool ifFlag = false;
		int tempCounter = 0;

		_window->clear();

		while (!whileFlag)
		{
			for (int x = 0; x < _maze->cells.size(); x++)
			{
				if (_maze->cells[x]->aStarValue == tempCounter && ifFlag == false)
				{
					DrawMaze();
					if (_maze->cells[x]->inEnd == true)
					{
						whileFlag = true;
						ifFlag = true;
					}
					_maze->cells[x]->aStarTrail = true;
				}
				if (_maze->cells.size() - 1 == x)
					tempCounter++;
			}
		}
		DrawMaze();

		sftime = clock.restart();
		time = sftime.asSeconds();
		std::cout << "Drawing time: " << time << std::endl;
		delete _astar;
	}

	// Starttaa AI:n ja piirt‰‰ sen
	// 5 == Q
	if (_inputDirection == 5)
	{
		std::cout << "RHR AI's calculation time: ";
		sf::Clock clock;
		clock.restart();
		_ai = new AI(_gridSize, _maze, _window, (_startY + (_startX * _gridSize)));
		_ai->start();

		sf::Time sftime = clock.restart();
		float time = sftime.asSeconds();
		std::cout << time << std::endl;

		std::vector<int>tempMoves = _ai->_aimoves;
		for (int x = 0; x < tempMoves.size(); x++)
		{
			_maze->cells[tempMoves[x]]->aiVisited = true;
			//_maze->cells[tempMoves[x]]->Draw();
			DrawMaze();
			_maze->cells[tempMoves[x]]->aiVisited = false;
			_maze->cells[tempMoves[x]]->aiTrail = true;
		}
		
		DrawMaze();
		
		sftime = clock.restart();
		time = sftime.asSeconds();
		std::cout << "Drawing time: " << time << std::endl;
		delete _ai;
	}

	// 1,2,3,4 -> WASD
	if (_inputDirection > 0 && _inputDirection <= 4)
	{
		if (!_playerTime)
		{
			_playerClock.restart();
			_playerTime = true;
		}

		_initFlag = true;
		switch (_inputDirection)
		{
		case 1:
			// Move up
			// y > 0 checks that we are on "map"
			// maze.cells checks if there is a wall
			if (_y > 0 && _maze->cells[_playerIndex]->topWall == false)
			{
				_y--;
				_maze->cells[_playerIndex]->onGrid = true;
			}
			break;
		case 2:
			// Move left
			if (_x > 0 && _maze->cells[_playerIndex]->leftWall == false)
			{
				_x--;
				_maze->cells[_playerIndex]->onGrid = true;
			}
			break;
		case 3:
			// Move down
			if (_y < _gridSize - 1 && _maze->cells[_playerIndex]->bottomWall == false)
			{
				_y++;
				_maze->cells[_playerIndex]->onGrid = true;
			}
			break;
		case 4:
			// Move right
			if (_x < _gridSize - 1 && _maze->cells[_playerIndex]->rightWall == false)
			{
				_x++;
				_maze->cells[_playerIndex]->onGrid = true;
			}
			break;
		default:
			std::cout << "Switch doesn't work as intended at CustomDraw.cpp" << std::endl;
			break;
		}

		// Get player index with x and y coordinates
		_playerIndex = _maze->GetMazeCellIndexByPosition(_x, _y);
		//std::cout << "Current color r: " << (int)_maze->cells[_playerIndex]->GetColor().r << " g: " << (int)_maze->cells[_playerIndex]->GetColor().g << " b: " << (int)_maze->cells[_playerIndex]->GetColor().b << " alpha: " << (int)_maze->cells[_playerIndex]->GetColor().a << std::endl;

		// Marks cell as visited via player index
		_maze->cells[_playerIndex]->playerVisited = true;

		// If player is on goal grid
		WinCondition();

		_window->clear();
		DrawStartPosition();
		DrawEndPosition();

		// Scans throught cells and finds cells that player has visited and draws them
		for (int cell = 0; cell < _maze->cells.size(); cell++)
		{
			if (_playerIndex == cell)_maze->cells[cell]->onGrid = false;
			if (_maze->cells[cell]->playerVisited == true)
			{
				// Index to XY coordinates
				int tempX = cell / _gridSize;
				int tempY = cell % _gridSize;
				DrawFromGrid(tempX, tempY);
			}
			if (_maze->cells[cell]->onGrid == true && _maze->cells[_playerIndex]->isVisited != false)
			{
				int tempX2 = cell / _gridSize;
				int tempY2 = cell % _gridSize;
				DrawFromGrid(tempX2, tempY2);
			}
		}
		_window->display();
	}
	
	if (_initFlag == false)
	{
		DrawMaze();
	}
}

void CustomDraw::DrawFromGrid(int x, int y)
{
	// Draws left side of 3x3 vision

	int tempIndex = _maze->GetMazeCellIndexByPosition(x, y);

	int drawIndex = tempIndex - _gridSize - 1;
	if (drawIndex <= _gridSize * _gridSize - 1 && drawIndex > 0 && y != 0)
		_maze->cells[drawIndex]->Draw();

	drawIndex = tempIndex - _gridSize;
	if (drawIndex <= _gridSize * _gridSize - 1 && drawIndex > 0)
		_maze->cells[drawIndex]->Draw();

	drawIndex = tempIndex - _gridSize + 1;
	if (drawIndex <= _gridSize * _gridSize - 1 && drawIndex > 0 && y != _gridSize - 1)
		_maze->cells[drawIndex]->Draw();

	// Draws middle of 3x3 vision

	int drawIndex2 = tempIndex - 1;
	if (drawIndex2 <= _gridSize * _gridSize - 1 && drawIndex2 > 0 && y != 0)
		_maze->cells[drawIndex2]->Draw();

	drawIndex2 = tempIndex;
	if (drawIndex2 <= _gridSize * _gridSize - 1 && drawIndex2 > 0)
		_maze->cells[drawIndex2]->Draw(); // On comment because we want to see player as black grid

	drawIndex2 = tempIndex + 1;
	if (drawIndex2 <= _gridSize * _gridSize - 1 && drawIndex2 > 0 && y != _gridSize - 1)
		_maze->cells[drawIndex2]->Draw();

	// Draws right side of 3x3 vision

	int drawIndex3 = tempIndex + _gridSize - 1;
	if (drawIndex3 <= _gridSize * _gridSize - 1 && drawIndex3 > 0 && y != 0)
		_maze->cells[drawIndex3]->Draw();

	drawIndex3 = tempIndex + _gridSize;
	if (drawIndex3 <= _gridSize * _gridSize - 1 && drawIndex3 > 0)
		_maze->cells[drawIndex3]->Draw();

	drawIndex3 = tempIndex + _gridSize + 1;
	if (drawIndex3 <= _gridSize * _gridSize - 1 && drawIndex3 > 0 && y != _gridSize - 1)
		_maze->cells[drawIndex3]->Draw();

	//
}

void CustomDraw::DrawStartPosition()
{
	// Draws start position
	_maze->cells[_maze->GetMazeCellIndexByPosition(_startX, _startY)]->Draw();
}

void CustomDraw::DrawEndPosition()
{
	// Draws end position
	_maze->cells[_maze->GetMazeCellIndexByPosition(_endX, _endY)]->Draw();
}

void CustomDraw::WinCondition()
{
	// If player is on goal grid
	if (_maze->cells[_playerIndex]->playerVisited == true && _maze->cells[_playerIndex]->inEnd == true)
	{

		playerTime = _playerClock.getElapsedTime();
		float fplayerTime = playerTime.asSeconds();
		std::cout << "Player's time: " << fplayerTime << std::endl;

		DrawMaze();
		//for (;;) {}
	}
}

void CustomDraw::DrawMaze()
{
	_window->clear();
	for (int x = 0; x < _gridSize; x++)
	{
		for (int y = 0; y < _gridSize; y++)
		{
			int currentIndex = y + (x * _gridSize);
			_maze->cells[currentIndex]->Draw();
		}
	}
	_window->display();
}

float CustomDraw::RunAI1()
{
	sf::Clock clock;
	clock.restart();
	_ai = new AI(_gridSize, _maze, _window, 0);
	_ai->start();

	sf::Time sftime = clock.restart();
	float time = sftime.asSeconds();
	delete _ai;
	return time;
}

float CustomDraw::RunAI2()
{
	sf::Clock clock;
	clock.restart();

	_astar = new Astar(_gridSize, _maze, _window, 0);
	_astar->GoEveryAvailableNeighbour();

	sf::Time sftime = clock.restart();
	float time = sftime.asSeconds();
	delete _astar;
	return time;
}

int CustomDraw::CellsToGoal()
{
	return _maze->CellsToGoal();
}