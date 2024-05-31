#include "Menu.h"
#include "Game.h"
#include "NoFileEx.h"

Menu::Menu()
{
	m_X = sf::VideoMode::getDesktopMode().width/1.5;
	m_Y = sf::VideoMode::getDesktopMode().height/1.5;
	m_background.setTexture(&m_resources.getMenuBackground());
	m_background.setSize(sf::Vector2f(m_X, m_Y));

	setButtons();
}

void Menu::run()
{
	m_window.create(sf::VideoMode(m_X, m_Y), "Pick Up Sticks");

	while (m_window.isOpen())
	{
		m_window.clear();
		draw();
		m_window.display();

		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonPressed:
				handleChoice(event.mouseButton);
				break;
			}
		}

		for (int i = 0; i < NUM_OF_MENU_BUTTONS; i++)
		{
			(m_buttons[i].getGlobalBound().contains(sf::Mouse::getPosition(m_window).x,
				sf::Mouse::getPosition(m_window).y)) ?
				m_buttons[i].setScale(1.1f, 1.1f) :
				m_buttons[i].setScale(1.0f, 1.0f);
		}
	}
}

void Menu::setButtons()
{
	for (int i = 0; i < NUM_OF_MENU_BUTTONS; i++)
	{
		m_buttons.push_back(Button(sf::Vector2f(m_X / 2, ((i + 2) * m_Y * 3 / 14)), 
								   sf::Vector2f(m_X / 5.5, m_Y / 5.5), 
							       m_resources.getButtonName(i), 
								   &m_resources.getButtonTextures(i)));
	}
}

void Menu::handleChoice(const sf::Event::MouseButtonEvent& event)
{
	for (int i = 0; i < NUM_OF_MENU_BUTTONS; i++)
	{
		if (m_buttons[i].getGlobalBound().contains(event.x, event.y))
		{
			if (m_buttons[i].getType() == START)
			{
				Game game(m_window);
				game.run();
				m_file.close();
			}
			else if (m_buttons[i].getType() == LOAD)
			{
				try {
					openFile();
					Game game(m_window, m_file);
					game.run();
					m_file.close();
				}
				catch (NoFileEx& e) {
					e.HandleException();
				}
				catch (std::runtime_error& e)
				{
					std::cerr << e.what();
				}
				catch (std::invalid_argument& e)
				{
					std::cerr << e.what();
				}
			}
			else if (m_buttons[i].getType() == EXIT)
			{
				m_window.close();
			}
		}
	}
}

void Menu::openFile()
{
	m_file.open("Board.txt", std::ios_base::out | std::ios_base::in);

	if (!m_file.is_open())
	{
		throw NoFileEx("Error opening the file");
	}
}

void Menu::draw()
{
	m_window.draw(m_background);
	for (int i = 0; i < NUM_OF_MENU_BUTTONS; i++)
	{
		m_buttons[i].draw(m_window);
	}
}