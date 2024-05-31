#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(sf::Vector2f, sf::Vector2f, enum Buttons, sf::Texture*);

	void setScale(float, float);

	sf::FloatRect getGlobalBound() const;
	enum Buttons getType() const;

	void draw(sf::RenderWindow&) const;

private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_location;
	enum Buttons m_type;
};