#pragma once
#include "Toolbar.h"

Toolbar::Toolbar() {

	//set font
	m_remainingText.setFont(Resources::instance().get());
	m_timeText.setFont(Resources::instance().get());
	m_pointsText.setFont(Resources::instance().get());
	m_pickableText.setFont(Resources::instance().get());
	m_pickedUpText.setFont(Resources::instance().get());

	//set text size
	m_remainingText.setCharacterSize(SIZE_OF_TEXT);
	m_timeText.setCharacterSize(SIZE_OF_TEXT);
	m_pointsText.setCharacterSize(SIZE_OF_TEXT);
	m_pickableText.setCharacterSize(SIZE_OF_TEXT);
	m_pickedUpText.setCharacterSize(SIZE_OF_TEXT);

	//set text fill color to pink
	m_remainingText.setFillColor(PINK_COLOR); // Pink color
	m_timeText.setFillColor(PINK_COLOR); // Pink color
	m_pointsText.setFillColor(PINK_COLOR); // Pink color
	m_pickableText.setFillColor(PINK_COLOR); // Pink color
	m_pickedUpText.setFillColor(PINK_COLOR); // Pink color

	//set text outline color to black
	m_remainingText.setOutlineColor(sf::Color::Black);
	m_timeText.setOutlineColor(sf::Color::Black);
	m_pointsText.setOutlineColor(sf::Color::Black);
	m_pickableText.setOutlineColor(sf::Color::Black);
	m_pickedUpText.setOutlineColor(sf::Color::Black);

	//set outline thickness
	m_remainingText.setOutlineThickness(THICKNESS);
	m_timeText.setOutlineThickness(THICKNESS);
	m_pointsText.setOutlineThickness(THICKNESS);
	m_pickableText.setOutlineThickness(THICKNESS);
	m_pickedUpText.setOutlineThickness(THICKNESS);

	//set text position
	m_timeText.setPosition(TIME_TEXT_POS);
	m_remainingText.setPosition(REMAIN_TEXT_POS);
	m_pointsText.setPosition(POINTS_TEXT_POS);
	m_pickableText.setPosition(PICKABLE_TEXT_POS);
	m_pickedUpText.setPosition(PICKED_TEXT_POS);

}


//==========================================================
void Toolbar::drawToolbarText(sf::RenderWindow& window, const int ToolBarData[]) {

	// להוסיף את הסטרינג הקודם
	
	//draw time
	m_timeText.setString(timePrefix + std::to_string(ToolBarData[Time]));
	window.draw(m_timeText);

	//draw points
	m_pointsText.setString(pointsPrefix + std::to_string(ToolBarData[Points]));
	window.draw(m_pointsText);

	//draw 
	m_remainingText.setString(remainingPrefix + std::to_string(ToolBarData[Remaining]));
	window.draw(m_remainingText);

	//draw
	m_pickableText.setString(pickablePrefix + std::to_string(ToolBarData[Pickable]));
	window.draw(m_pickableText);
	
	//draw 
	m_pickedUpText.setString(pickedUpPrefix + std::to_string(ToolBarData[PickedUp]));
	window.draw(m_pickedUpText);
}
