#pragma once
#include <SFML/Graphics.hpp>

struct StickDetails
{
	sf::Vector2f _positionStart;
	sf::Vector2f _positionEnd;

	int _score;
	int _myPackSize;
	int _len;
	int _index;

	float _degree;
};