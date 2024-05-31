#include "GameInfo.h"

GameInfo::GameInfo()
	: m_timeLeft(60), 
	  m_score(0), 
	  m_remaining(20), 
	  m_picked(0), 
	  m_pickables(0), 
	  m_gameIsOver(false)
{
	m_text.setFont(Singleton::instance().getFont());
	m_win.setTexture(&Singleton::instance().getWinScreen());
	m_lose.setTexture(&Singleton::instance().getLoseScreen());

	m_text.setCharacterSize(40);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(sf::Vector2f(40, 50));

	m_final.setCharacterSize(60);
	m_final.setFillColor(sf::Color(204, 0, 102));
	m_final.setFont(Singleton::instance().getFont());
}

void GameInfo::draw(sf::RenderWindow& window)
{
	window.draw(m_bar);

	auto S = [](auto subject, auto value) { return subject + std::to_string(value) + "\n"; };

	std::string infoString = S("Time: ", (int)m_timeLeft) +
							 S("Score: ", m_score) +
							 S("Remaining: ", m_remaining) +
							 S("Picked Up: ", m_picked) +
							 S("Pickable: ", m_pickables);
	
	m_text.setString(infoString);	

	window.draw(m_text);

	if (m_gameIsOver)
	{		
		showGameOver(window);
	}
}

void GameInfo::resetInfo(sf::Vector2u size)
{
	m_bar.setSize(sf::Vector2f(3, size.y * 0.94));
	m_bar.setPosition(sf::Vector2f(size.x*2.3 / 11, size.y * 0.03));
	m_bar.setFillColor(sf::Color::Black);
}

void GameInfo::update(float timeLeft, int score, int remaining, int picked, int pickables)
{
	m_timeLeft = timeLeft;
	m_score = score;
	m_remaining = remaining;
	m_picked = picked;
	m_pickables = pickables;
}

void GameInfo::setGameOver(bool state, std::string winLose)
{
	m_winLose = winLose;
	m_gameIsOver = state;
}

void GameInfo::showGameOver(sf::RenderWindow& window)
{
	m_final.setString("Final Score: " + std::to_string(m_score));
	m_final.setPosition(sf::Vector2f(window.getSize().x * 7/18, window.getSize().y *2/5));
	if (m_winLose == "Win")
	{
		m_win.setSize(sf::Vector2f(window.getSize()));
		window.draw(m_win);
	}
	else if (m_winLose == "Lose")
	{
		m_lose.setSize(sf::Vector2f(window.getSize()));
		window.draw(m_lose);
	}
	window.draw(m_final);
}