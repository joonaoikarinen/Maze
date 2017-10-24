#include "Maze.hpp"
#include <iostream>

Maze::Maze(int width, int height, int collumns, int rows, sf::RenderWindow* window, int startX, int startY, int goalX, int goalY) : width(width), height(height), collumns(collumns), rows(rows), window(window), _startX(startX), _startY(startY), _goalX(goalX), _goalY(goalY)
{
	srand(time(0));
	_cellsToGoal = 0;
	Init(sf::Vector2f(_startX, _startY), sf::Vector2f(_goalX, _goalY));
}

Maze::~Maze()
{
	//std::cout << "Maze class destroyed successfully" << std::endl;
}

void Maze::Init(sf::Vector2f startPos, sf::Vector2f endPos)
{
	completedGeneration = false;
	cells.clear();
	stack.clear();

	int size = (int)(width / collumns);

	for (int x = 0; x < collumns; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			cells.push_back(new MazeCell(x, y, size, window));

			if (sf::Vector2f(x, y) == startPos)
			{
				cells[cells.size() - 1]->inStart = true;
			}
			else if (sf::Vector2f(x, y) == endPos)
			{
				cells[cells.size() - 1]->inEnd = true;
			}
		}
	}

	currentCell = cells[0];
	stack.push_back(currentCell);
}
void Maze::Draw()
{
	if (!completedGeneration)
	{
		int it = 0;
		while (it < GenerationStepSpeed)
		{
			it++;
			currentCell->isVisited = true;
			currentCell->inStack = true;

			MazeCell* nextCell = GetRandomNeighbor(currentCell);
			if (nextCell != nullptr)
			{
				RemoveWalls(currentCell, nextCell);

				currentCell = nextCell;

				stack.push_back(currentCell);
			}
			else
			{
				if (stack.size() > 1)
				{
					stack[stack.size() - 1]->inStack = false;
					stack.pop_back();
					currentCell = stack[stack.size() - 1];
				}
				if (stack.size() == 1)
				{
					stack[stack.size() - 1]->inStack = false;
					stack.clear();
					completedGeneration = true;

					it = GenerationStepSpeed;
				}
			}
			static int allowOnce = 0;
			if (currentCell->inEnd == true)allowOnce++;
			if (currentCell->inEnd == true && allowOnce >= 1)
			{
				for (int xz = 0; stack.size() > xz; xz++)
				{
					stack.at(xz)->onPath = true;
				}
			}
		}
	}
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i]->Draw();
	}
}

void Maze::OwnRemoveWalls()
{
	if (!completedGeneration)
	{
		int it = 0;
		while (it < GenerationStepSpeed)
		{
			it++;
			currentCell->isVisited = true;
			currentCell->inStack = true;

			MazeCell* nextCell = GetRandomNeighbor(currentCell);
			if (nextCell != nullptr)
			{
				RemoveWalls(currentCell, nextCell);

				currentCell = nextCell;

				stack.push_back(currentCell);
			}
			else
			{
				if (stack.size() > 1)
				{
					stack[stack.size() - 1]->inStack = false;
					stack.pop_back();
					currentCell = stack[stack.size() - 1];
				}
				if (stack.size() == 1)
				{
					stack[stack.size() - 1]->inStack = false;
					stack.clear();
					completedGeneration = true;

					it = GenerationStepSpeed;
				}
			}
			static int allowOnce = 0;
			if (currentCell->inEnd == true)allowOnce++;
			if (currentCell->inEnd == true && allowOnce >= 1)
			{
				for (int xz = 0; stack.size() > xz; xz++)
				{
					stack.at(xz)->onPath = true;
				}
			}
		}
	}
}

void Maze::RemoveWalls(MazeCell* cell1, MazeCell* cell2)
{
	if (cell1->GetCollumn() == cell2->GetCollumn() + 1)
	{
		cell1->leftWall = false;
		cell2->rightWall = false;
	}
	else if (cell1->GetCollumn() == cell2->GetCollumn() - 1)
	{
		cell1->rightWall = false;
		cell2->leftWall = false;
	}
	else if (cell1->GetRow() == cell2->GetRow() + 1)
	{
		cell1->topWall = false;
		cell2->bottomWall = false;
	}
	else if (cell1->GetRow() == cell2->GetRow() - 1)
	{
		cell1->bottomWall = false;
		cell2->topWall = false;
	}
}
MazeCell* Maze::GetRandomNeighbor(MazeCell* cell)
{
	std::vector<MazeCell*> availableNeighbors;

	int cellsSize = cells.size();

	//Right
	int index = GetMazeCellIndexByPosition(cell->GetCollumn() + 1, cell->GetRow());
	if (index < cellsSize && index != -1)
	{
		if (!cells[index]->isVisited)
		{
			availableNeighbors.push_back(cells[index]);
		}
	}
	//Left
	index = GetMazeCellIndexByPosition(cell->GetCollumn() - 1, cell->GetRow());
	if (index < cellsSize && index != -1)
	{
		if (!cells[index]->isVisited)
		{
			availableNeighbors.push_back(cells[index]);
		}
	}
	//Bottom
	index = GetMazeCellIndexByPosition(cell->GetCollumn(), cell->GetRow() + 1);
	if (index < cellsSize && index != -1)
	{
		if (!cells[index]->isVisited)
		{
			availableNeighbors.push_back(cells[index]);
		}
	}
	//Top
	index = GetMazeCellIndexByPosition(cell->GetCollumn(), cell->GetRow() - 1);
	if (index < cellsSize && index != -1)
	{
		if (!cells[index]->isVisited)
		{
			availableNeighbors.push_back(cells[index]);
		}
	}
	if (availableNeighbors.size() > 0)
	{
		return availableNeighbors[(int)(rand() % availableNeighbors.size())];
	}
	else
	{
		return nullptr;
	}
}

int Maze::GetMazeCellIndexByPosition(int x, int y)
{
	if (x < 0 || y < 0 || x > collumns - 1 || y > rows - 1)
	{
		return -1;
	}
	return y + (x * collumns); // weasel..
}


int Maze::CellsToGoal()
{
	for (int xx = 0; xx < collumns; xx++)
	{
		for (int yy = 0; yy < rows; yy++)
		{
			int tempIndex = GetMazeCellIndexByPosition(xx, yy);
			if (cells[tempIndex]->onPath == true)
			{
				_cellsToGoal++;
			}
		}
	}

	return _cellsToGoal;
}
