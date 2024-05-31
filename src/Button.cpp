#include "Button.h"

Button::Button(sf::Vector2f location, sf::Vector2f shapeSize, enum Buttons type, sf::Texture* aTexture)
	: m_location(location), 
	  m_type(type)
{
	m_shape.setSize(shapeSize);
	m_shape.setOrigin(shapeSize.x/2, shapeSize.y / 2);
	m_shape.setPosition(m_location);
	m_shape.setTexture(aTexture);
}

void Button::setScale(float x, float y)
{
	m_shape.setScale(x, y);
}

sf::FloatRect Button::getGlobalBound() const
{
	return m_shape.getGlobalBounds();
}

enum Buttons Button::getType() const
{
	return m_type;
}

void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}
