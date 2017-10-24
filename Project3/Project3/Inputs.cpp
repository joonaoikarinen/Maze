#include "Inputs.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>



Inputs::Inputs()
{

}


Inputs::~Inputs()
{
	//std::cout << "Inputs class destroyed successfully" << std::endl;
}

bool Inputs::readInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// Move up
		_lastPressedKey = W;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// Move left
		_lastPressedKey = A;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// Move down
		_lastPressedKey = S;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// Move right
		_lastPressedKey = D;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		// Start AI
		_lastPressedKey = Q;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		// Boolean trigger
		_lastPressedKey = E;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		// Boolean trigger
		_lastPressedKey = R;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		// Boolean trigger
		_lastPressedKey = T;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		// Boolean trigger
		_lastPressedKey = Y;
		return true;
	}
	return false;
}

int Inputs::returnDirection()
{
	// Inputflag blocks multiple presses at once
	if (readInputs() && _inputFlag == false)
	{
		_inputFlag = true;
		//std::cout << _lastPressedKey << std::endl;
		return _lastPressedKey;
	}
	// Releases flag when all buttons released
	if (!readInputs() && _inputFlag == true)
	{
		_inputFlag = false;
	}
	return 0;
}