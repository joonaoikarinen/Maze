#ifndef Walls_h
#define Walls_h

#include <stdio.h>
#include <limits.h>
#include <SFML\Graphics.hpp>

class Walls
{
public:
	Walls(sf::RenderWindow* window, int collumn, int row, int size);
	~Walls();

	void DrawCurrentCell(sf::Color cellColor);
	void DrawWalls(bool left, bool top, bool right, bool bottom, int wallWidth);

private:

	sf::RenderWindow* _window;
	int _collumn, _row;
	int _size;
	int _wallWidth;
};

#endif