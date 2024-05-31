#define _USE_MATH_DEFINES
#include <cmath>
#include "Stick.h"
#include "Singleton.h"

Stick::Stick(StickDetails& details)
	: m_score(details._score), 
	  m_locationStart(details._positionStart), 
	  m_length(details._len),
	  m_degree(details._degree), 
	  m_index(details._index) , 
	  m_blockingMe(details._myPackSize, false)
{
	setColor(details._score);

	m_shape.setFillColor(m_color);
	m_shape.setSize(sf::Vector2f(m_length, 12));
	m_shape.setPosition(m_locationStart);
	m_shape.rotate(m_degree);
	m_locationEnd = calculateEndPoint();
	m_shape.setOutlineThickness(1.5);
	m_shape.setOutlineColor(sf::Color(32,32,32));

	m_numOfBlocking = 0;
}

sf::Vector2f Stick::calculateEndPoint() const
{
	float radians = m_degree * (M_PI / 180.0f);
	float x_end = m_locationStart.x + m_length * std::cos(radians);
	float y_end = m_locationStart.y + m_length * std::sin(radians);

	return sf::Vector2f(x_end, y_end);
}

void Stick::setOutLineColor(sf::Color color)
{
	m_shape.setOutlineColor(color);
}

void Stick::setColor(int score)
{
	switch (score)
	{
	case 20:
		m_color = sf::Color::Blue;
		break;
	case 10:
		m_color = BLACK;
		break;
	case 5:
		m_color = ORANGE;
		break;
	case 3:
		m_color = GREEN;
		break;
	case 2:
		m_color = sf::Color::Red;
		break;
	default:
		break;
	}
}

void Stick::setBlocking(int i, bool state)
{
	m_numOfBlocking += state ? 1 : -1;
	m_blockingMe[i] = state;
}

int Stick::getScore() const
{
	return m_score;
}

const std::vector<bool>& Stick::getBlockers() const
{
	return m_blockingMe;
}

sf::Vector2f Stick::getStartLocation() const
{
	return m_locationStart;
}

sf::Vector2f Stick::getEndLocation() const
{
	return m_locationEnd;
}

int Stick::getIndex() const
{
	return m_index;
}

int Stick::getLen() const
{
	return m_length;
}

float Stick::getDegree() const
{
	return m_degree;
}

sf::Color Stick::getColor() const
{
	return m_color;
}

bool Stick::isPressed(sf::Vector2f clickPos) const
{
	sf::Vector2f correctPos = m_shape.getTransform().getInverse().transformPoint(clickPos);
	return m_shape.getLocalBounds().contains(correctPos);
}

bool Stick::freeToPick() const
{
	return m_numOfBlocking == 0;
}

bool Stick::isBlockingMe(int i) const
{
	return m_blockingMe[i];
}

void Stick::draw(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}