#include "Game.h"

Game::Game(sf::RenderWindow& window)
	: m_window(&window), 
	  m_info(std::make_unique<GameInfo>()), 
	  m_pack(window.getSize()), 
	  m_score(0), 
	  m_numOfPickedSticks(0)
{
	setUp(window.getSize());
	setButtons();

	m_timeLeft = 35 + m_pack.getSize();
}

Game::Game(sf::RenderWindow& window, std::fstream& theFile)
	: m_window(&window), 
	  m_info(std::make_unique<GameInfo>()), 
	  m_pack(window.getSize(), theFile, m_loadedInfo), 
	  m_numOfPickedSticks(m_loadedInfo._pickedUp)
{

	setUp(window.getSize());
	setButtons();

	m_score = m_loadedInfo._playerScore;
	m_timeLeft = m_loadedInfo._remainigTime;
}

void Game::run()
{
	m_clock.restart();

	while (m_window->isOpen() && !m_menuCall)
	{
		if (m_gameOver)
		{
			m_info->setGameOver(true, m_winLose);
			m_stopUpdating = true;
		}

		handleClock();
		m_window->clear();
		draw();
		m_window->display();

		sf::Event event;
		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window->close();
				break;
			case sf::Event::MouseButtonPressed:
				handleClick(event.mouseButton);
				break;
			}
		}
		if (!m_stopUpdating)
		{
			m_info->update(m_timeLeft, m_score, m_pack.getRemaining(), m_numOfPickedSticks, m_pack.getPickables().size());		
		}
	}
}

void Game::setUp(sf::Vector2u size)
{
	m_info->resetInfo(size);
	m_background.setTexture(&m_resources.getGameBackground());
	m_background.setSize(sf::Vector2f(size.x, size.y));

	m_gameTime = m_clock.restart();
	m_timeLeft = 35 + m_pack.getSize();
	m_winLose = "";
	m_stopUpdating = m_gameOver = m_menuCall = false;

}

void Game::setButtons()
{
	auto x = sf::VideoMode::getDesktopMode().width / 7;
	auto y = sf::VideoMode::getDesktopMode().height / 7;
	m_buttons.push_back(Button(sf::Vector2f(x * 49/96, y * 35/12 -50), sf::Vector2f(x*7 / 12, y*7 / 12), HINT, &m_resources.getButtonTextures(3)));
	m_buttons.push_back(Button(sf::Vector2f(x * 49/96, y * 7/2 -25), sf::Vector2f(x * 7 / 12, y * 7 / 12), SAVE, &m_resources.getButtonTextures(4)));
	m_buttons.push_back(Button(sf::Vector2f(x * 49/96, y * 49/12), sf::Vector2f(x * 7 / 12, y * 7 / 12), MENU, &m_resources.getButtonTextures(5)));
}

void Game::draw() const
{
	m_window->draw(m_background);
	m_pack.draw(*m_window);

	for (int i = 0; i < NUM_OF_GAME_BUTTONS-1; i++)
	{
		m_buttons[i].draw(*m_window);
	}
	m_info->draw(*m_window);
	
	m_buttons[NUM_OF_GAME_BUTTONS - 1].draw(*m_window);
	
}

void Game::handleClock()
{
	static float passedSeconds = 0.0f;
	m_gameTime = m_clock.restart();
	passedSeconds += m_gameTime.asSeconds();
	int secondsPassed = (int)passedSeconds;
	passedSeconds -= secondsPassed;
	m_timeLeft -= secondsPassed;

	if (m_timeLeft < 0 && !m_gameOver)
	{
		m_gameOver = true;
		m_winLose = "Lose";
	}
}

void Game::handleClick(const sf::Event::MouseButtonEvent& clickPos)
{
	bool pickedAStick = false;
	int blockedStick = -1;
	m_pack.handleClick(sf::Vector2f(clickPos.x, clickPos.y), pickedAStick, blockedStick, m_score);
	buttonPressed(clickPos);

	if (pickedAStick)
	{
		m_numOfPickedSticks++;
	}
	else if (blockedStick != -1)
	{
		showBlockers(blockedStick);
		m_score -= 2;		// a "Punishment" is triggered if the player attempts to pick up a blocked stick

		if (m_score < 0)
		{
			m_score = 0;
		}
	}

	if (m_pack.getRemaining() == 0 && !m_gameOver)
	{
		m_gameOver = true;
		m_winLose = "Win";
	}
}

void Game::buttonPressed(const sf::Event::MouseButtonEvent& event)
{
	for (int i = 0; i < NUM_OF_GAME_BUTTONS; i++)
	{
		if (m_buttons[i].getGlobalBound().contains(event.x, event.y))
		{
			if (m_buttons[i].getType() == HINT)
			{
				showHint();
			}
			else if (m_buttons[i].getType() == SAVE)
			{
				save();
			}
			else if (m_buttons[i].getType() == MENU)
			{
				m_menuCall = true;
			}
		}
	}
}

void Game::showHint()
{
	m_score -= 20;
	m_score = std::max(0, m_score);

	m_flashTime = m_flashClock.restart();
	auto& pickables = m_pack.getPickables();
    auto rit = pickables.rbegin();

    while (rit != pickables.rend())
	{
		if (m_flashClock.getElapsedTime().asSeconds() >= 0.7f)
		{
			(*rit)->setOutLineColor(sf::Color::Yellow);

			m_window->clear(sf::Color(190, 206, 130));
			draw();
			m_window->display();
			(*rit)->setOutLineColor(sf::Color(32, 32, 32));

			++rit; 
			m_flashClock.restart();
		}
		sf::sleep(sf::milliseconds(10));
	}
	while (m_flashClock.getElapsedTime().asSeconds() <  0.7f);
}

void Game::showBlockers(int stickBlockers)
{
	for (int i = 0; i < 2; i++)
	{
		m_flashTime = m_flashClock.restart();
		auto& blockers = m_pack.getStick(stickBlockers).getBlockers();
		auto it = blockers.begin();

		m_pack.colorBlockers(sf::Color(255,204,204), stickBlockers);

		m_window->clear();
		draw();
		m_window->display();
		while (m_flashClock.getElapsedTime().asSeconds() < 0.5f);
		m_pack.colorBlockers(sf::Color(32, 32, 32), stickBlockers);
		m_window->clear();
		draw();
		m_window->display();
		m_flashTime = m_flashClock.restart();
		while (m_flashClock.getElapsedTime().asSeconds() < 0.5f && i==0);
	}
}

void Game::save()
{
	m_file.open("Board.txt", std::ios_base::out | std::ios_base::in | std::ios::trunc);

	m_file.clear();

	m_file << m_pack.getSize() <<"\n";
	m_file << m_pack.getRemaining() << "\n";
	m_file << m_timeLeft << "\n";
	m_file << m_score << "\n";
	m_file << m_numOfPickedSticks << "\n";

	m_pack.saveSticks(m_file);
	m_file.seekp(0, std::ios::beg);
}