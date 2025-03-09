#pragma once
#include "Stick.h"
#include "iostream"

Stick::Stick() 
{
	//get random values
	m_length = float(rand() % (MAX_STICK_LENGTH - MIN_STICK_LENGTH) + MIN_STICK_LENGTH);
	m_points[START] = { float((rand() % (MAX_X_POS - MIN_X_POS)) + MIN_X_POS), float((rand() % (MAX_Y_POS - MIN_Y_POS)) + MIN_Y_POS) };
	m_color = static_cast<Color>(rand() % Color::Count);

	setStick();	 //update stick's sprite

	//update rotation and checks if rectangle is in the desired bounds
	do {
		m_angle = float(rand() % MAX_ANGLE);
		m_stick.setRotation(m_angle);
		m_points[END] = getTransformedFarPoint(m_stick);
	} while (!validEndPoint());
	
}

Stick::Stick(std::istringstream& iss) 
{
	//read stick input from file line
	auto color = 0;
	iss >> color;
	if (color < 0 || color > Color::Count -1)
		throw std::out_of_range("Out of range : Please enter color numbers in the range: 0-4.\n");
	
	m_color = Color(color);

	iss >> m_length;
	if (m_length < MIN_STICK_LENGTH || m_length > MAX_STICK_LENGTH)
		throw std::out_of_range("Out of range : Please enter length in the range: 50-950.\n");

	iss >> m_points[START].x >> m_points[START].y;
	if (m_points[START].x < MIN_X_POS || m_points[START].x > MAX_X_POS || m_points[START].y < MIN_Y_POS || m_points[START].y > MAX_Y_POS)
		throw std::out_of_range("Out of range : Please enter point values in the range: x: 500 - 1300 y: 100 - 800 .\n");

	setStick();

	iss >> m_angle;
	m_stick.setRotation(m_angle);
	m_points[END] = getTransformedFarPoint(m_stick);
	if (m_angle < 0 || m_angle > MAX_ANGLE || !validEndPoint())
		throw std::out_of_range("Out of range : Please enter angle in the range 0-360 and so that the other point will bw in the screen and the stick will not be vertical.\n");

	
}

void Stick::setStick()
{
	//update rectangle  size
	m_stick.setSize(sf::Vector2f(STICK_WITDH, m_length));
	
	//update rectangle  position
	m_stick.setPosition(m_points[START]);

	//update rectangle colors
	m_stick.setFillColor(getColor(m_color));
	m_stick.setOutlineColor(sf::Color::Black);
	m_stick.setOutlineThickness(float(THICKNESS));
	m_stickPoints = m_color + 1;

}

bool Stick::validEndPoint() const
{
	return ((MIN_X_POS < m_points[END].x && m_points[END].x < SCREEN_WIDTH
		&& 0 < m_points[END].y && m_points[END].y < SCREEN_LENGTH)
		&& (m_points[START].x != m_points[END].x));
}

sf::Color Stick::getColor(const Color color) const {
	
	switch (color) {
	case Red: return sf::Color::Red;
	case Blue: return sf::Color::Blue;
	case Green: return sf::Color::Green;
	case Orange: return ORANGE;  // Orange
	case Yellow: return sf::Color::Yellow;
	default: return sf::Color::White;  // Default to white if something goes wrong
	}
}

sf::RectangleShape Stick::getShape() 
{
	if (m_outlineStick)
	{
		// Check if the outline duration has elapsed
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_outlineTime);
		if (elapsedTime >= OUTLINE_DURATION) {
			m_outlineStick = false; 
			m_stick.setOutlineColor(sf::Color::Black);
		}
	}

	return m_stick;
}

void Stick::OutlineStick()
{
	m_outlineStick = true;
	m_outlineTime = std::chrono::steady_clock::now();
	m_stick.setOutlineColor(NEON_YELLOW);

}

// Function to get the transformed point at the far side of the rectangle
sf::Vector2f Stick::getTransformedFarPoint(const sf::RectangleShape& rectangle) {
	sf::Transform transform = rectangle.getTransform();

	// Assuming the far point is the bottom right corner of the rectangle in local coordinates
	sf::Vector2f farPointLocal(rectangle.getSize().x, rectangle.getSize().y);

	// Adjust for the origin of the rectangle
	farPointLocal -= rectangle.getOrigin();

	// Transform the local coordinates to global coordinates
	sf::Vector2f farPointGlobal = transform.transformPoint(farPointLocal);

	return farPointGlobal;
}

bool Stick::pointInStick(const sf::Vector2f mousePosition) const
{
	const auto transformedPoint = m_stick.getTransform().getInverse().transformPoint(mousePosition);
	return m_stick.getLocalBounds().contains(transformedPoint);
}

sf::Vector2f Stick::getPoint(const int i) const
{
	return m_points[i];
}

void Stick::addInterrupting(std::list<Stick>::iterator addIt)
{
	m_interruptingSticks.push_back(addIt);
}

void Stick::addInterrupted(std::list<Stick>::iterator addIt)
{
	m_interruptedSticks.push_back(addIt);
}

int Stick::getNumOfInterrupting() const
{
	return int(m_interruptingSticks.size());
}

void Stick::updateEachInterrupted(std::list<Stick>::iterator toErase)
{
	for (auto it = m_interruptedSticks.begin(); it != m_interruptedSticks.end(); ++it)
	{
		(*it)->eraseFromInnterrupting(toErase);
	}
}

void Stick::eraseFromInnterrupting(std::list<Stick>::iterator toErase)
{
	for (auto it = m_interruptingSticks.begin(); it != m_interruptingSticks.end(); ++it)
	{
		if (*it == toErase)
		{
			m_interruptingSticks.erase(it);
			break; // Assuming `toErase` is unique in the list
		}
	}
}

std::list<Stick>::iterator Stick::getInterruptingStick()
{
	return *m_interruptingSticks.begin();
}

void Stick::updatePickAbleLIst(std::list<Stick*>& m_PickableStickList, int& Pickable)
{
	for (auto it = m_interruptedSticks.begin(); it != m_interruptedSticks.end(); ++it)
	{
		if ((*it)->getNumOfInterrupting() == 0)
		{
			// Insert into the sorted position
			auto insertPos = std::upper_bound(m_PickableStickList.begin(), m_PickableStickList.end(), &(**it),
				[](const Stick* a, const Stick* b) { return a->getPoints() > b->getPoints(); });
			m_PickableStickList.insert(insertPos, &(**it));
			Pickable++;
		}
	}
}

void Stick::printDataToFile(std::ofstream& outFile) const
{
	outFile << m_color << " " << m_length << " " << m_points[START].x 
			<< " " << m_points[START].y << " " << m_angle << "\n";
}

bool Stick::operator==(const Stick* other) const
{
	return m_stick.getPosition() == other->m_stick.getPosition() &&
		m_length == other->m_length &&
		m_angle == other->m_angle &&
		m_color == other->m_color;
}