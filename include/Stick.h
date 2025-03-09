#pragma once

#include "Resources.h"
#include <cmath>

class Stick
{
public:
	Stick();
	Stick(std::istringstream& iss);
	sf::Color getColor(const Color color) const;
	sf::RectangleShape getShape();
	
	bool pointInStick(const sf::Vector2f mousePosition) const;
	sf::Vector2f getPoint(const int i) const;
	void addInterrupting(std::list<Stick>::iterator addIt);
	void addInterrupted(std::list<Stick>::iterator addIt);
	int getNumOfInterrupting() const;
	void updateEachInterrupted(std::list<Stick>::iterator toErase);
	void OutlineStick();
	std::list<Stick>::iterator getInterruptingStick(); 
	void updatePickAbleLIst(std::list<Stick*> &m_PickableStickList, int& Pickable);
	int getPoints() const { return m_stickPoints;  }
	void printDataToFile(std::ofstream& outFile) const;
	bool operator==(const Stick* other) const; 


private:
	sf::RectangleShape m_stick;
	sf::Vector2f m_points[2];
	Color m_color = Red;
	float m_length = 0;
	float m_angle = 0;
	int m_stickPoints = 0;

	bool m_outlineStick = false;		//tells if we need to outline the stick
	std::chrono::steady_clock::time_point m_outlineTime;

	std::list <std::list<Stick>::iterator> m_interruptingSticks;	//sticks that blocking this stick
	std::list <std::list<Stick>::iterator> m_interruptedSticks;		//sticks that blocked by this stick

	//private func
	void setStick();
	sf::Vector2f getTransformedFarPoint(const sf::RectangleShape& rectangle);
	void eraseFromInnterrupting(std::list<Stick>::iterator toErase);
	bool validEndPoint() const;

};
