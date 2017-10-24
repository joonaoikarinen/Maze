#ifndef Maze_hpp
#define Maze_hpp

#include <stdio.h>
#include <vector>
#include <SFML\Graphics.hpp>
#include "MazeCell.hpp"


class Maze
{
public:
	Maze(int width, int height, int collumns, int rows, sf::RenderWindow* window, int startX, int startY, int goalX, int goalY);
	~Maze();

	void Init(sf::Vector2f startPos, sf::Vector2f endPos);

	void Draw();
	void OwnRemoveWalls();

	MazeCell* GetRandomNeighbor(MazeCell* cell);

	void RemoveWalls(MazeCell* cell1, MazeCell* cell2);

	int GetMazeCellIndexByPosition(int x, int y);
	int CellsToGoal();
	int GenerationStepSpeed = 1000001;

	std::vector<MazeCell*> cells;
	MazeCell* currentCell;


private:
	int width, height;
	int collumns, rows;
	int _startX, _startY;
	int _goalX, _goalY;
	int _cellsToGoal;

	bool completedGeneration = false;

	sf::RenderWindow* window;

	std::vector<MazeCell*> stack;

};

#endif