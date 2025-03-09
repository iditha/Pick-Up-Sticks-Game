#pragma once
#include "Board.h"
#include "Menu.h"
#include "Resources.h"
#include "Toolbar.h"


class Controller {

public:

	Controller();
	void run();

private:

	Board m_board;									//main board
	Menu m_menu;									//for menu
	Toolbar m_toolbar;								//for level information data
	sf::RenderWindow m_window;						//game render window

	sf::Time m_gameTime;							//for the time of the game 
	sf::Clock m_deltaTime, m_timeOfCurrLevel;
	bool m_loseGame = false;

	void handleGameTime();
	void handleEvents();
	void runGame();
	void draw();
	void resetTimeLevel();
	void printWinOrLose();


};