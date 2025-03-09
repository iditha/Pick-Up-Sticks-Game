#pragma once
#include "Resources.h"

class Toolbar
{
public:
	Toolbar();
	~Toolbar() = default;

	void drawToolbarText(sf::RenderWindow&, const int ToolBarData[]);

private:
	sf::Text m_remainingText;
	sf::Text m_timeText;
	sf::Text m_pointsText;
	sf::Text m_pickableText;
	sf::Text m_pickedUpText;

};