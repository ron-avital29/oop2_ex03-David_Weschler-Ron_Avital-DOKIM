#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include "StickDetails.h"

class Stick
{
public:
	Stick(StickDetails&);

	sf::Vector2f calculateEndPoint() const;

	void setOutLineColor(sf::Color);
	void setBlocking(int, bool);

	int getScore() const;
	const std::vector<bool>& getBlockers() const;
	sf::Vector2f getStartLocation() const;
	sf::Vector2f getEndLocation() const;
	int getIndex() const;
	int getLen() const;
	float getDegree() const;
	sf::Color getColor() const;

	bool isPressed(sf::Vector2f) const;
	bool freeToPick() const;
	bool isBlockingMe(int) const;
	void draw(sf::RenderWindow&) const;

private:
	void setColor(int);

	sf::RectangleShape m_shape;
	sf::Color m_color;
	sf::Vector2f m_locationStart;
	sf::Vector2f m_locationEnd;

	std::vector<bool> m_blockingMe;
	float m_degree;
	int m_length;
	int m_score;
	int m_index;
	int m_numOfBlocking;
};
