#include "Singleton.h"
#include <iostream>

Singleton::Singleton()
{
	LoadFromFile();
}

sf::Texture& Singleton::getMenuBackground()
{
	return m_menuBackground;
}

sf::Texture& Singleton::getGameBackground()
{
	return m_gameBackground;
}

sf::Texture& Singleton::getFileNotFound()
{
	return m_fileNotFound;
}

sf::Texture& Singleton::getWinScreen()
{
	return m_winScreen;
}

sf::Texture& Singleton::getLoseScreen()
{
	return m_loseScreen;
}

Singleton& Singleton::instance()
{
	static Singleton Singleton;
	return Singleton;
}

sf::Texture& Singleton::getButtonTextures(int num)
{
	return m_buttonTextures[num];
}

Buttons Singleton::getButtonName(int i) const
{
	return m_names[i];
}

void Singleton::LoadFromFile()
{
	for (int num = START; num <= MENU; num++)
	{
		m_buttonTextures.push_back(sf::Texture());
		if (!(m_buttonTextures[num].loadFromFile(m_buttonNames[num])))
		{
			std::cerr << "cannot load textures\n";
			exit(EXIT_FAILURE);
		}
	}

	if (!m_font.loadFromFile("Font.ttf"))
	{
		std::cerr << "cannot load font\n";
		exit(EXIT_FAILURE);
	}

	if (!m_menuBackground.loadFromFile(m_nameOfBackgrounds[0]) ||
		!m_gameBackground.loadFromFile(m_nameOfBackgrounds[1]) ||
		!m_fileNotFound.loadFromFile(m_nameOfExemption) ||
		!m_winScreen.loadFromFile(m_endScreens[0]) ||
		!m_loseScreen.loadFromFile(m_endScreens[1]))

	{
		std::cerr << "cannot load textures\n";
		exit(EXIT_FAILURE);
	}
}

const sf::Font& Singleton::getFont() const
{
	return m_font;
}