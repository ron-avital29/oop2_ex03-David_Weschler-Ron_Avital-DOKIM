#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <fstream>

#include "Button.h"
#include "FileInfo.h"
#include "GameInfo.h"
#include "PackOfSticks.h"
#include "Stick.h"
#include "Singleton.h"

class Game
{
public:
	Game(sf::RenderWindow&);
	Game(sf::RenderWindow&, std::fstream&);

	void run();
	
private:
	void setUp(sf::Vector2u);
	void setButtons();
	void draw() const;

	void handleClock();
	void handleClick(const sf::Event::MouseButtonEvent&);

	void buttonPressed(const sf::Event::MouseButtonEvent&);
	void showHint();
	void showBlockers(int);
	void save();

	Singleton& m_resources = Singleton::instance();

	sf::RenderWindow *m_window;
	sf::Clock m_clock;
	sf::Clock m_flashClock;
	sf::Time m_flashTime;
	sf::Time m_gameTime;
	sf::RectangleShape m_background;

	FileInfo m_loadedInfo;
	PackOfSticks m_pack;

	std::fstream m_file;
	std::string m_winLose;

	std::unique_ptr<GameInfo> m_info;
	std::vector<Button> m_buttons;

	int m_score;
	int m_timeLeft;
	int m_numOfPickedSticks;

	bool m_menuCall;
	bool m_gameOver;
	bool m_stopUpdating;
};