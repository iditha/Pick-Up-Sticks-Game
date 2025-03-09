#pragma once
#include "Controller.h"

Controller::Controller() : m_window(sf::VideoMode((unsigned int)SCREEN_WIDTH, (unsigned int)SCREEN_LENGTH), "Pick Up Sticks") {

	m_window.setFramerateLimit(FPS);
}
//=========================================================
void Controller::run() {

	srand((unsigned int)time(NULL));

	//main loop - when the game ends we will come back to the menu
	while (true) {

		try {
			m_menu.runMenu(m_window);
			m_board.setBoard(m_menu.getLoad());
			resetTimeLevel();
			runGame();
		}

		catch (const std::ifstream::failure& e) {
			std::cerr << "You have an error with the input: " << e.what() << std::endl;
		}
		catch (const std::exception& e) { 
			std::cerr << "An error occurred: " << e.what() << std::endl; 
		}

	}
}

void Controller::runGame() {

	while (!m_board.getWinGame()) {

		draw();
		handleGameTime();

		if (m_gameTime.asSeconds() < 0) {	// if level time ends
			//Resources::instance().playSound(SoundType::LoseSound);
			m_loseGame = true;
			break;
		}

		handleEvents();
		if (m_board.getGoToMenu())
			return;
	}
	if (m_board.getWinGame() || m_loseGame)
		printWinOrLose();

}
//=========================================================
void Controller::handleEvents() {

	sf::Vector2f location = sf::Vector2f({ -1, -1 });

	for (auto event = sf::Event{}; m_window.pollEvent(event);) {
		switch (event.type) {

		case sf::Event::Closed:
			m_window.close();
			exit(EXIT_SUCCESS);

		case sf::Event::MouseButtonReleased:
		{
			location = m_window.mapPixelToCoords(
				{ event.mouseButton.x, event.mouseButton.y });
			m_board.handleClick(location);
		}

		//default: break;
		}

	}
}
//=========================================================
void Controller::draw() {

	m_window.clear();

	m_window.draw(sf::Sprite(Resources::instance().get(Background)));
	m_board.drawObjects(m_window);
	
	//update time in m_toolbardata in board- int(m_gameTime.asSeconds())
	m_board.updateTime(int(m_gameTime.asSeconds()));
	m_toolbar.drawToolbarText(m_window, m_board.getToolBarData());
	m_window.display();
}

//=========================================================
void Controller::handleGameTime() {

	m_gameTime -= m_timeOfCurrLevel.getElapsedTime();
	m_timeOfCurrLevel.restart();
		
}

void Controller::resetTimeLevel() {

	m_timeOfCurrLevel.restart();
	m_gameTime = sf::seconds(float(m_board.getTime()));

}

void Controller::printWinOrLose() 
{
	m_window.clear();

	if (m_board.getWinGame()) {
		sf::Sprite winSprite(Resources::instance().get(ObjectType::WinBackground));
		m_window.draw(winSprite);
		//Resources::instance().playSound(SoundType::WinGameSound);

	}
	if (m_loseGame) {
		sf::Sprite loseSprite(Resources::instance().get(ObjectType::LoseBackground));
		m_window.draw(loseSprite);
		//Resources::instance().playSound(SoundType::LoseSound);

	}

	m_window.display();
	m_loseGame = false;

	while (true) //makes that the user need to press enter to continue
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			break;
}