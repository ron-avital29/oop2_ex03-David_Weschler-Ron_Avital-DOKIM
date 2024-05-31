#include <SFML/System.hpp>
#include "PackOfSticks.h"
#include "StickDetails.h"

PackOfSticks::PackOfSticks(sf::Vector2u limits)
{
	srand(std::time(NULL));

	StickDetails stickParam;
	m_packSize = stickParam._myPackSize= rand() % 11 + 40;
	int stickRange = limits.x / 2.55;
	int delta = stickRange / 4.5;
	float positionRange = limits.x * 2.3 / 11 + 15;
	std::string dummy;

	for (int i = 0; i < m_packSize;)
	{
		randomizeDetails(stickParam, i, stickRange, delta, positionRange, limits);
		if (DetailsAreValid(stickParam, limits, positionRange, dummy))
		{
			m_sticks.push_back(Stick(stickParam));
			i++;
		}
	}
	setBlocking();
	updatePickables();
}

PackOfSticks::PackOfSticks(sf::Vector2u limits, std::fstream& theFile, FileInfo& loadedInfo)
{
	StickDetails stickParam;
	readGameData(theFile, loadedInfo, stickParam);
	m_packSize = stickParam._myPackSize;
	readSticks(theFile, stickParam, loadedInfo._remainingSticks, limits);
	setBlocking();
	updatePickables();
}

void PackOfSticks::randomizeDetails(StickDetails& stickParam, int scoreId, int stickRange, int delta, float positionRange, sf::Vector2u limits)
{
	stickParam._len = rand() % stickRange + delta;
	stickParam._positionStart = sf::Vector2f((rand() % limits.x - (positionRange)) + positionRange, rand() % limits.y * 0.85 +30);
	stickParam._degree = rand() % 179 + 89;
	stickParam._index = scoreId;

	if (scoreId < 3) { stickParam._len = limits.y / 1.3; stickParam._score = 20; }
	else if (scoreId < 13) { stickParam._score = 10; }
	else if (scoreId < 27) { stickParam._score = 5; }
	else if (scoreId % 2 == 0) { stickParam._score = 3; }
	else { stickParam._score = 2; }

	Stick temp(stickParam);
	stickParam._positionEnd = temp.getEndLocation();
}

bool PackOfSticks::DetailsAreValid(const StickDetails& stick, const sf::Vector2u limits, float positionRange, std::string& whosFault)
{
	sf::Vector2f endPoint = stick._positionEnd;
	whosFault = "";
	bool allClear = true;

	if ((endPoint.x < positionRange || endPoint.x > limits.x))	{ whosFault += "endPoint.x ";	allClear =  false;}
	if ((endPoint.y < 30 || endPoint.y > limits.y)) { whosFault += "endPoint.y "; allClear = false;}
	if ((stick._positionStart.x < positionRange || stick._positionStart.x > limits.x)) { whosFault += "stick._positionStart.x "; allClear = false; }
	if (stick._index < 0 || stick._index > stick._myPackSize) { whosFault += "stick._index "; allClear = false; }
	if (stick._len < 0 || stick._len > std::max(limits.y / 1.3, limits.x / 2.55 + (limits.x / 2.55) / 4.5)) { whosFault += "stick._len "; allClear = false; }
	if (stick._score < 2 || stick._score > 20) { whosFault += "stick._score	"; allClear = false; }

	return allClear;
}

void PackOfSticks::readGameData(std::fstream& theFile, FileInfo& loadedInfo, StickDetails& stickParam)
{
	auto Throw = [](const std::string& message) { throw std::invalid_argument("Failed to read '" + message + "' from the file");};
	auto ThrowRange = [](const std::string& message) { throw std::runtime_error("'" + message + "' is out of range"); };

	if (!(theFile >> stickParam._myPackSize))		{Throw("stickParam._myPackSize");}
	if (!(theFile >> loadedInfo._remainingSticks))  {Throw("loadedInfo._remainingSticks");}
	if (!(theFile >> loadedInfo._remainigTime))		{Throw("loadedInfo._remainigTime");}
	if (!(theFile >> loadedInfo._playerScore))		{Throw("loadedInfo._playerScore");}
	if (!(theFile >> loadedInfo._pickedUp))			{Throw("loadedInfo._pickedUp");}

	if (stickParam._myPackSize < 1 || stickParam._myPackSize > 50)	{ThrowRange("stickParam._myPackSize");};
	if (loadedInfo._remainingSticks < 0 || loadedInfo._remainingSticks > stickParam._myPackSize) { ThrowRange("stickParam._remainingSticks");};
	if (loadedInfo._remainigTime < 0) {ThrowRange("loadedInfo._remainigTime");};
	if (loadedInfo._playerScore < 0)  {ThrowRange("loadedInfo._playerScore");};
	if (loadedInfo._pickedUp < 0)	  {ThrowRange("loadedInfo._pickedUp");};
}

void PackOfSticks::readSticks(std::fstream& theFile, StickDetails& stickParam, int end, sf::Vector2u limits)
{
	auto Throw = [](const std::string& message) { throw std::invalid_argument("Failed to read '" + message + "' from the file"); };
	auto ThrowRange = [](const std::string& message) { throw std::runtime_error("'" + message + "' is out of range"); };
	
	float positionRange = limits.x * 2.3 / 11 + 15;
	std::string whosFault;

	for (auto i = 0; i < end; i++)
	{
		if (!(theFile >> stickParam._score))		   {Throw("stickParam._score");};
		if (!(theFile >> stickParam._positionStart.x)) {Throw("stickParam._positionStart.x");};
		if (!(theFile >> stickParam._positionStart.y)) {Throw("stickParam._positionStart.y");};
		if (!(theFile >> stickParam._len))			   {Throw("stickParam._len");};
		if (!(theFile >> stickParam._degree))		   {Throw("stickParam._degree");};
		if (!(theFile >> stickParam._index))		   {Throw("stickParam._index");}

		m_sticks.push_back(Stick(stickParam));

		stickParam._positionEnd = m_sticks.back().getEndLocation();

		if (!DetailsAreValid(stickParam, limits, positionRange, whosFault))
		{
			ThrowRange(whosFault);
		}
	}
}

void PackOfSticks::setBlocking()
{
	int me = 0;
	for (auto iter = m_sticks.begin(); iter != m_sticks.end(); iter++)
	{
		auto it = std::next(iter);

		int blockerIndex = me +1;
		for (; it != m_sticks.end(); ++it)
		{
			if (doIntersect(iter->getStartLocation(), iter->getEndLocation(), 
						    it->getStartLocation(), it->getEndLocation()))
			{	
				iter->setBlocking(it->getIndex(), true);
			}
			blockerIndex++;
		}
		me++;
	}
}

void PackOfSticks::handleClick(sf::Vector2f clickPos, bool& picked, int& showBlockers, int& score)
{
	int i = 0;
	for (auto rit = m_sticks.rbegin(); rit != m_sticks.rend(); ++rit) 
	{
		if (rit->isPressed(clickPos)) 
		{
			showBlockers = rit->getIndex();
			picked = handlePickUp(rit, score);
			break;
		}
		i++;
	}
}

bool PackOfSticks::handlePickUp(lIt stickPtr, int& score)
{
	if (stickPtr->freeToPick())
	{     
		score += stickPtr->getScore();
		int indexToErase = stickPtr->getIndex();
		m_sticks.erase(std::next(stickPtr).base());	

		for (auto it = m_sticks.begin(); it != m_sticks.end(); ++it)
		{
			if (it->isBlockingMe(indexToErase))
			{
				it->setBlocking(indexToErase, false);
			}
		}
		updatePickables();
		return true;
	}
	return false;
}

int PackOfSticks::getSize() const
{
	return m_packSize;
}

int PackOfSticks::getRemaining() const
{
	return m_sticks.size();
}

void PackOfSticks::saveSticks(std::fstream& file)
{
	for (const auto& stick : m_sticks)
	{
		file << stick.getScore() << " ";
		file << stick.getStartLocation().x << " ";
		file << stick.getStartLocation().y << " ";
		file << stick.getLen() << " ";
		file << stick.getDegree() << " ";
		file << stick.getIndex() << "\n";
	}
}

const Stick& PackOfSticks::getStick(int index) const
{
	for (const auto& it : m_sticks)
	{
		if (it.getIndex() == index)
		{
			return it;
		}
	}
}

std::multiset<Stick*, PackOfSticks::Comparator>& PackOfSticks::getPickables()
{
	return m_pickable;
}

bool PackOfSticks::doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
	{
		return true;
	}

	// Special Cases 
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1))
	{
		return true;
	}

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1))
	{
		return true;
	}

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2))
	{
		return true;
	}

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2))
	{
		return true;
	}

	return false; // Doesn't fall in any of the above cases 
}

int PackOfSticks::orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; 

	return (val > 0) ? 1 : 2; 
}

bool PackOfSticks::onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

void PackOfSticks::colorBlockers(sf::Color color, int stickIndex)
{
	auto& stick = getStick(stickIndex);

	for (auto it = m_sticks.begin(); it != m_sticks.end(); ++it)
	{
		if (stick.isBlockingMe(it->getIndex()))
		{
			it->setOutLineColor(color);
		}
	}
}

void PackOfSticks::draw(sf::RenderWindow& window) const
{
	for (const auto& stick : m_sticks)
	{
		stick.draw(window);
	}
}

void PackOfSticks::updatePickables()
{
	m_pickable.clear();
	for (auto& it : m_sticks)
	{
		if (it.freeToPick())
		{
			m_pickable.emplace(&it);
		}
	}
}

bool PackOfSticks::Comparator::operator()(const Stick* one, const Stick* two) const
{
	return one->getScore() < two->getScore();
}