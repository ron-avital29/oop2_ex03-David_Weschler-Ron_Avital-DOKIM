#pragma once

#include "SFML/Graphics.hpp"
#include <stdexcept>
#include <string>

#include "Singleton.h"

class NoFileEx : public std::runtime_error
{
public:
    NoFileEx(const std::string& message);
    virtual void HandleException();

private:
    void draw();

    Singleton& m_resources = Singleton::instance();

    sf::RectangleShape m_background;
    sf::RenderWindow m_window;
};