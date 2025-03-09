#pragma once
#include "Resources.h"

class Menu {

public:
	Menu();

	void drawMenu(sf::RenderWindow& window);
	void runMenu(sf::RenderWindow& window);
	void handleMenuClick(bool& inMenu, sf::RenderWindow& window);
	void handleMouseMove(const sf::RenderWindow& window);
	bool getLoad() const { return m_load; }

private:
	std::vector<sf::RectangleShape> m_buttons;		//for menu buttons
	bool m_load = false; 

};