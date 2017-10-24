#include "Walls.h"



Walls::Walls(sf::RenderWindow* window, int collumn, int row, int size)
{
	_collumn = collumn;
	_row = row;
	_size = size;
	_window = window;
}


Walls::~Walls()
{

}

void Walls::DrawCurrentCell(sf::Color cellColor)
{
	sf::Vector2f cellPosition = sf::Vector2f(_size * _collumn, _size * _row);
	static sf::RectangleShape cellShape = sf::RectangleShape(sf::Vector2f(_size, _size));
	cellShape.setPosition(cellPosition.x, cellPosition.y);
	cellShape.setFillColor(cellColor);

	_window->draw(cellShape);
}

void Walls::DrawWalls(bool left, bool top, bool right, bool bottom, int wallWidth)
{
	sf::Vector2f cellPosition = sf::Vector2f(_size * _collumn, _size * _row);

	if (left)
	{
		static sf::RectangleShape leftWallShape = sf::RectangleShape(sf::Vector2f(wallWidth, _size));
		leftWallShape.setPosition(cellPosition.x, cellPosition.y);
		leftWallShape.setFillColor(sf::Color(0, 0, 0, 255));
		_window->draw(leftWallShape);
	}

	if (right)
	{
		static sf::RectangleShape rightWallShape = sf::RectangleShape(sf::Vector2f(wallWidth, _size));
		rightWallShape.setPosition(cellPosition.x + _size - wallWidth, cellPosition.y);
		rightWallShape.setFillColor(sf::Color(0, 0, 0, 255));
		_window->draw(rightWallShape);
	}

	if (top)
	{
		static sf::RectangleShape topWallShape = sf::RectangleShape(sf::Vector2f(_size, wallWidth));
		topWallShape.setPosition(cellPosition.x, cellPosition.y);
		topWallShape.setFillColor(sf::Color(0, 0, 0, 255));

		_window->draw(topWallShape);
	}

	if (bottom)
	{
		static sf::RectangleShape bottomWallShape = sf::RectangleShape(sf::Vector2f(_size, wallWidth));
		bottomWallShape.setPosition(cellPosition.x, cellPosition.y + _size - wallWidth);
		bottomWallShape.setFillColor(sf::Color(0, 0, 0, 255));
		_window->draw(bottomWallShape);
	}
}