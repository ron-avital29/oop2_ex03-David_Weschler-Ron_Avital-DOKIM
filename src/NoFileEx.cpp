#include "NoFileEx.h"

NoFileEx::NoFileEx(const std::string& message)
	: std::runtime_error(message)
{
	m_background.setTexture(&m_resources.getFileNotFound());
	m_background.setSize(sf::Vector2f(553.27, 300.73));
}

void NoFileEx::HandleException()
{
	m_window.create(sf::VideoMode(553.27, 300.73), "Oops! File Error");
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
			}
		}
	}
}

void NoFileEx::draw()
{
	m_window.draw(m_background);
}
