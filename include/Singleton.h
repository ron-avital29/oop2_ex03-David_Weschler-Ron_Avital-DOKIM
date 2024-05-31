#pragma once

#include <SFML/Graphics.hpp>

#include <string.h>


//------------enum-------------
enum Buttons {START,
              LOAD,
              EXIT,
              HINT,
              SAVE,
              MENU};

//-------------const----------------
const int NUM_OF_BUTTONS = 6;
const int NUM_OF_MENU_BUTTONS = 3;
const int NUM_OF_GAME_BUTTONS = 3;
const int STICK_PARAMETERS = 6;

const sf::Color BLACK(64, 64, 65);
const sf::Color ORANGE(255, 145, 0);
const sf::Color GREEN(65, 186, 12);

class Singleton
{
public:
    ~Singleton() = default;
    static Singleton& instance();
    enum Buttons getButtonName(int) const;

    sf::Texture& getButtonTextures(int num);
    sf::Texture& getGameBackground();
    sf::Texture& getMenuBackground();
    sf::Texture& getFileNotFound();
    sf::Texture& getLoseScreen();
    sf::Texture& getWinScreen();
    const sf::Font& getFont() const;

    void LoadFromFile();

private:
    Singleton();
    Singleton(const Singleton&) = delete;

    Singleton operator=(const Singleton&) = delete;

    enum Buttons m_names[NUM_OF_BUTTONS] = {START, 
                                            LOAD, 
                                            EXIT, 
                                            HINT, 
                                            SAVE, 
                                            MENU};
    sf::Font m_font;
    sf::Texture m_gameBackground;
    sf::Texture m_menuBackground;
    sf::Texture m_fileNotFound;
    sf::Texture m_fileFault;
    sf::Texture m_winScreen;
    sf::Texture m_loseScreen;
    std::vector<sf::Texture> m_buttonTextures;

    std::vector<std::string> m_nameOfBackgrounds = {"MenuBack.png", 
                                                    "GameBack.png"};
    std::vector<std::string> m_endScreens = {"WinScreen.png",
                                             "LoseScreen.png"};
    std::string m_nameOfExemption = "FileNotFound.png";
    std::vector<std::string> m_buttonNames = {"Start.png",
                                              "Load.png",
                                              "Exit.png",
                                              "Hint.png",
                                              "Save.png",
                                              "Menu.png"};
};