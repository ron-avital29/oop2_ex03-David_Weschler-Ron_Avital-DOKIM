#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Button.h"
#include "Singleton.h"

class GameInfo
{
public:
	GameInfo();
	void draw(sf::RenderWindow&);
	void resetInfo(sf::Vector2u);
	void update(float, int, int, int, int);
	void setGameOver(bool, std::string);

private:
	void showGameOver(sf::RenderWindow&);

	sf::RectangleShape m_bar;
	sf::RectangleShape m_win;
	sf::RectangleShape m_lose;
	sf::Text m_text;
	sf::Text m_final;

	std::string m_winLose;

	int m_score;
	int m_remaining;
	int m_picked;
	int m_pickables;

	float m_timeLeft;
	bool m_gameIsOver;
};