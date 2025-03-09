#pragma once

#include "Resources.h"
#include "Stick.h"

class Board {

public:
	Board();
	void setBoard(const bool load);
	void drawObjects(sf::RenderWindow& window);
	void handleClick(const sf::Vector2f location);
	const int* getToolBarData() const { return m_ToolBarData; }
	int getTime() const { return m_ToolBarData[Time]; }
	void updateTime(const int);
	bool getWinGame() const { return m_winGame; };
	bool getGoToMenu() const { return m_goToMenu; };

private:
	std::list<Stick> m_stickList;
	std::list<Stick*> m_PickableStickList;
	sf::Sprite m_hintSprite;
	sf::Sprite m_saveSprite;
	sf::Sprite m_menuSprite;
	int m_ToolBarData[TOOL_BAR_SIZE] = { 0 };
	//int m_timeLevel = 0;
	bool m_winGame = false;
	bool m_goToMenu = false;
	
	// For outlining with delay - Hint
	sf::Clock m_outlineClock;
	std::list<Stick*>::iterator m_currentPickableStick;

	void initObjects();
	bool onSegment(Point p, Point q, Point r);
	int orientation(Point p, Point q, Point r);
	bool doIntersect(Point p1, Point q1, Point p2, Point q2);
	void outlinePickableSticksWithDelay();
	void updateData();
	void newBoard();
	void loadBoard();
	void saveBoardGame();
	void ToolBarValid() const;
	

};