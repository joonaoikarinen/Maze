#include <stdio.h>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Maze.hpp"
#include "Inputs.h"
#include "CustomDraw.h"
#include <Windows.h>
#include <string>

// Generates random goal position(s) 1 at a time
int returnRandomGoal(int xy);

int main(int argc, char** argv)
{
	std::cout << "Size of MazeCell: " << sizeof(MazeCell) << std::endl;
	std::string testi;
	std::cout << "Anna mazen sivun koko: ";
	int gridSize;
	std::cin >> gridSize;
	// Declares grid size (ex. gridSize = 20 -> xMax = 20, yMax = 20 -> grids = 400)

	// Declares resolution (x y scale is 1:1)
	int resolution = 1080;

	// Players start x position
	int x = 0;
	// Player start y position
	int y = 0;

	// Resets random
	srand(time(NULL));
	// Random maze goal coordinates
	int goalX = returnRandomGoal(gridSize);
	int goalY = returnRandomGoal(gridSize);

	// Init window
	sf::RenderWindow window(sf::VideoMode(resolution, resolution), "Maze", sf::Style::None);


	window.setKeyRepeatEnabled(false);

	// Init custom draw
	CustomDraw* customdraw;
	customdraw = new CustomDraw(gridSize, x, y, &window, resolution, goalX, goalY);

	Inputs input;
	int intInput = 0;

	//int otokset = 1;

	std::fstream fileHandler;


	// While window is open
	while (window.isOpen())
	{
		//Sleep(1);
		sf::Event evnt;

		// Updates game (inputs drawing etc.)
		customdraw->Update();
		intInput = input.returnDirection();
		// 8 == T
		if (intInput == 8)
		{
			delete customdraw;
			gridSize++;

			srand(time(NULL));
			goalX = returnRandomGoal(gridSize);
			goalY = returnRandomGoal(gridSize);
			customdraw = new CustomDraw(gridSize, x, y, &window, resolution, goalX, goalY);
			std::cout << "Size of whole maze == " << gridSize * gridSize * sizeof(MazeCell) << std::endl;
			//for (int x = 0; x < 10; x++)
				//customdraw->DrawMaze();

		}

		//std::cout << "En ole jaatynyt" << std::endl;

		// Jos painat yyyy(Y):tä
		if (intInput == 9)
		{
			std::cout << "Running some CSV" << std::endl;
			fileHandler.open("file.csv", std::ofstream::out | std::ofstream::app);

			fileHandler << "Gridsize,RHR,Astar,Pathlength,Otos\n";
			std::string textString = "";

			for (int otokset = 1; otokset < 11; otokset++)
			{
				for (int gridi = 2; gridi < 654; gridi = gridi * 2)
				{

					delete customdraw;
					srand(time(NULL));
					goalX = returnRandomGoal(gridi);
					goalY = returnRandomGoal(gridi);
					customdraw = new CustomDraw(gridi, x, y, &window, resolution, goalX, goalY);

					float AI1time = customdraw->RunAI1();
					float AI2time = customdraw->RunAI2();
					//std::cout << AI1time << std::endl;
					textString += std::to_string(gridi);
					textString += ",";
					textString += std::to_string(AI1time);
					textString += ",";
					textString += std::to_string(AI2time);
					textString += ",";
					textString += std::to_string(customdraw->CellsToGoal());
					textString += ",";
					textString += std::to_string(otokset);
					textString += "\n";
					//fileHandler << gridi << "," << customdraw->RunAI1() << "," << customdraw->RunAI2() << "," << otokset << "\n";
				}
				std::cout << "otos: " << otokset << std::endl;
			}
			fileHandler << textString;
			std::cout << "Mita maksaa string: " << sizeof(textString) << std::endl;
			fileHandler.close();
			std::cout << "done, otos" << std::endl;
		}

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				customdraw->~CustomDraw();
				window.close();
				break;
			}
		}
	}
	std::cout << "Program return 0 on next line!" << std::endl;
	return 0;
}

int returnRandomGoal(int gridSize)
{
	// Randoming xy coordinate of goal
	int randomInt = rand() % gridSize;
	int laps = 1;
	while (randomInt < gridSize / 2)
	{
		randomInt = rand() % gridSize;
		laps++;
	}
	//std::cout << "End position randomized " << laps << " times." << std::endl;
	return randomInt;
}