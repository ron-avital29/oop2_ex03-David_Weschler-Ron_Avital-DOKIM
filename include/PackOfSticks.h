#pragma once

#include <SFML/Graphics.hpp>
#include "list"
#include "Stick.h"
#include "cstdlib"
#include "ctime"
#include <set>
#include "FileInfo.h"
#include <fstream>

typedef std::reverse_iterator<std::list<Stick>::iterator> lIt;

class PackOfSticks
{
public:
	PackOfSticks(sf::Vector2u);
	PackOfSticks(sf::Vector2u, std::fstream&, FileInfo&);

	void randomizeDetails(StickDetails&, int, int, int , float, sf::Vector2u);
	bool DetailsAreValid(const StickDetails&, const sf::Vector2u, float, std::string&);

	void handleClick(sf::Vector2f, bool&, int&, int&);
	bool handlePickUp(lIt, int&);

	int getSize() const;
	int getRemaining() const;
	const Stick& getStick(int index) const;

	void saveSticks(std::fstream&);
	void colorBlockers(sf::Color, int);
	void draw(sf::RenderWindow&) const;

	class Comparator
	{
	public:
		bool operator()(const Stick*, const Stick*) const;
	};

	std::multiset<Stick*, Comparator>& getPickables();

private:
	void setBlocking();
	void readGameData(std::fstream&, FileInfo&, StickDetails&);
	void readSticks(std::fstream&, StickDetails&, int, sf::Vector2u);
	void updatePickables();

	bool doIntersect(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
	int orientation(sf::Vector2f, sf::Vector2f, sf::Vector2f);
	bool onSegment(sf::Vector2f, sf::Vector2f, sf::Vector2f);

	std::list<Stick> m_sticks;
	std::multiset<Stick*, Comparator> m_pickable;

	int m_packSize;
};

class Comparator
{
public:
	bool operator()(const Stick*, const Stick*) const;
};