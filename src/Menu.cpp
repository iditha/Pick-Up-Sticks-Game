#pragma once
#include "Menu.h"

Menu::Menu() {

	// init menu bottuns
	m_buttons.resize(NUM_OF_MENU_BUTTONS);

	for (int i = 0, y = 555; i < NUM_OF_MENU_BUTTONS; i++, y += 100) {
		m_buttons[i].setTexture(&Resources::instance().get(ObjectType(i)));
		m_buttons[i].setSize({ BUTTON_MENU_SIZE });
		m_buttons[i].setPosition(120.f, float(y + 20 * i));
		m_buttons[i].setOutlineColor(sf::Color::White);
		m_buttons[i].setOutlineThickness(THICKNESS_FRAME);
	}
};
//=========================================================
void Menu::drawMenu(sf::RenderWindow& window) {

	window.clear();
	auto sprite = sf::Sprite(Resources::instance().get(ObjectType::MenuBackground));
	window.draw(sprite);

	for (int i = 0; i < NUM_OF_MENU_BUTTONS ; i++)
		window.draw(m_buttons[i]);

	window.display();
}

//=========================================================
void Menu::runMenu(sf::RenderWindow& window) {

	bool inMenu = true;
	m_load = false;

	//menu loop
	while (window.isOpen() && inMenu) {
		drawMenu(window);

		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				handleMouseMove(window);
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Button::Left)
					handleMenuClick(inMenu, window);
				break;
			}
		}
	}
}

//=========================================================
void Menu::handleMouseMove(const sf::RenderWindow& window) {

	for (int i = 0; i < NUM_OF_MENU_BUTTONS; i++) {
		if (m_buttons[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			m_buttons[i].setOutlineColor(sf::Color::Magenta);
		}
		else
			m_buttons[i].setOutlineColor(sf::Color::Black);
	}
}
//=========================================================
void Menu::handleMenuClick(bool& inMenu, sf::RenderWindow& window) {

	// start game -> user pressed start button
	if (m_buttons[New].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		inMenu = false;
	}

	else if (m_buttons[Load].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		m_load = true;
		inMenu = false;
	}
		
	// quit -> user pressed quit button
	else if (m_buttons[Quit].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		exit(EXIT_SUCCESS);

	
}
//=========================================================