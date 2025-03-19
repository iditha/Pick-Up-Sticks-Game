#include "Board.h"

Board::Board()
{
	m_hintSprite = sf::Sprite(Resources::instance().get(Hint));
	m_saveSprite = sf::Sprite(Resources::instance().get(Save));
	m_menuSprite = sf::Sprite(Resources::instance().get(MenuBottom));
	m_hintSprite.setPosition(HINT_POS);
	m_saveSprite.setPosition(SAVE_POS);
	m_menuSprite.setPosition(MENU_POS);
}

void Board::setBoard(const bool load)
{
	initObjects();
	
	if (load)
	{
		loadBoard();
	}
	else
	{
		newBoard();
	}

	updateData();
	m_currentPickableStick = m_PickableStickList.end();
}

void Board::loadBoard()
{
	auto f = std::ifstream("Board.txt"); 
	if (!(f.is_open()))
		throw FileError();

	auto s = std::string();

	std::getline(f, s);
	auto iss = std::istringstream(s);
	iss.exceptions(std::ios::failbit | std::ios::badbit);

	iss >> m_ToolBarData[Time] >> m_ToolBarData[Points] >> m_ToolBarData[Remaining] >> m_ToolBarData[PickedUp];

	for (int i = 0; i < m_ToolBarData[Remaining] && std::getline(f, s); i++)
	{
		auto iss = std::istringstream(s);
		iss.exceptions(std::ios::failbit | std::ios::badbit);

		// if the read fails, it throws
		m_stickList.push_back(Stick(iss));

		if (!(iss.eof() || (iss >> std::ws).eof()))
		{
			// check if at EOF, if not - discard whitespaces and check again for EOF
			// if it still isn't at EOF, there is something left in iss, which means
			// the line was too long, so throw an error here
			throw std::exception("Too many arguments in line.\n");
		}
	}
	ToolBarValid();
}

void Board::ToolBarValid() const
{
	if(m_ToolBarData[Time] < 1 || m_ToolBarData[Time] > (MAX_STICKS + MIN_STICKS) * FACTOR)
		throw std::out_of_range("Out of range error : Please enter TIME in the range 1-150 .\n");
	
	if (m_ToolBarData[Remaining] < 1 || m_ToolBarData[Remaining] != m_stickList.size())
		throw std::out_of_range("Out of range error : Please enter number of Remaining STICKS as in the file, range: 1-50\n");

	if (m_ToolBarData[PickedUp] < 0 || m_ToolBarData[PickedUp] > MAX_STICKS + MIN_STICKS -1)
		throw std::out_of_range("Out of range error : Please enter number of Pickedup STICKS in the range: 0-49 .\n");

	if (m_ToolBarData[PickedUp] + m_ToolBarData[Remaining] > MAX_STICKS + MIN_STICKS)
		throw std::out_of_range("Out of range error : Number of Pickedup STICKS + Number of Remaining STICKS is more than the maximum(50) sticks allowed. \n");

	if (m_ToolBarData[PickedUp] > m_ToolBarData[Points] || (m_ToolBarData[PickedUp] * MAX_STICK_POINTS) < m_ToolBarData[Points])
		throw std::out_of_range("Out of range error : Please enter Number of POINTS in the range: Number of Pickedup STICKS*1 - Number of Pickedup STICKS*5 .\n");

}

void Board::newBoard() 
{
	srand((unsigned int)time(NULL));
	m_ToolBarData[Remaining] = (rand() % MAX_STICKS) + MIN_STICKS;	
	m_ToolBarData[Time] = m_ToolBarData[Remaining] * FACTOR;

	//build sticks list
	for (int i = 0; i < m_ToolBarData[Remaining]; i++)
	{
		m_stickList.push_back(Stick());
	}
}

void Board::updateData()
{
	//update each stick data
	for (auto it1 = m_stickList.begin(); it1 != m_stickList.end(); ++it1)
	{
		for (auto it2 = m_stickList.begin(); it2 != it1; ++it2)
		{
			if (doIntersect(it1->getPoint(START), it1->getPoint(END),
				it2->getPoint(START), it2->getPoint(END)))
			{
				it1->addInterrupted(it2);
				it2->addInterrupting(it1);

			}
		}
	}

	// build free stick list
	for (auto it = m_stickList.begin(); it != m_stickList.end(); ++it)
	{
		if (it->getNumOfInterrupting() == 0)
		{
			// Insert into the sorted position
			auto insertPos = std::upper_bound(m_PickableStickList.begin(), m_PickableStickList.end(), &(*it),
				[](const Stick* a, const Stick* b) { return a->getPoints() > b->getPoints(); });
			m_PickableStickList.insert(insertPos, &(*it));
			m_ToolBarData[Pickable]++;
		}
	}
}

void Board::initObjects() {
	
	m_stickList.clear();

	// Reinitialize any member variables that depend on m_stickList
	m_PickableStickList.clear();
	m_currentPickableStick = m_PickableStickList.end();
	
	m_ToolBarData[Pickable] = 0;
	m_ToolBarData[Points] = 0;
	m_ToolBarData[PickedUp] = 0;
	m_winGame = false;
	m_goToMenu = false;

}

void Board::drawObjects(sf::RenderWindow& window) 
{
	window.draw(m_hintSprite);
	window.draw(m_saveSprite);
	window.draw(m_menuSprite);

	for (auto it = m_stickList.begin(); it != m_stickList.end(); ++it) {
		window.draw(it->getShape());
	}

	outlinePickableSticksWithDelay();
}

void Board::handleClick(const sf::Vector2f location)
{

	for (auto it = m_stickList.rbegin(); it != m_stickList.rend(); ++it)
	{
		if (it->pointInStick(location))
		{
			//pickable stick
			if ((it->getNumOfInterrupting() == 0))
			{
				auto regIt = std::next(it).base();				// make reverse iterator to regular iterator
				it->updateEachInterrupted(regIt);				// erase the iterator from list interrupting
				it->updatePickAbleLIst(m_PickableStickList, m_ToolBarData[Pickable]);	// add the new pickable sticks to the pickable list
				
				// Find the corresponding iterator in m_PickableStickList
				auto pickableIt = std::find(m_PickableStickList.begin(), m_PickableStickList.end(), *regIt);
				if (pickableIt != m_PickableStickList.end()) 
				{
					m_PickableStickList.erase(pickableIt);		// Erase the element from pickable sticks list
					m_ToolBarData[Pickable]--;
				}

				//update screen data
				m_ToolBarData[Remaining]--;
				m_ToolBarData[PickedUp]++;
				m_ToolBarData[Points] += it->getPoints();

				m_stickList.erase(regIt);						// Erase the element from sticks list
				//checks if player won
				if (m_stickList.size() == 0)
					m_winGame = true;
				
			}
			//unpickable stick - show which sticks interrupting
			else
			{
				it->getInterruptingStick()->OutlineStick();
			}
			break;
		}
	}

	if (m_hintSprite.getGlobalBounds().contains(location))
	{
		for (auto it = m_PickableStickList.begin(); it != m_PickableStickList.end(); ++it)
		{
			m_currentPickableStick = m_PickableStickList.begin(); // Reset the iterator
			m_outlineClock.restart(); // Reset the clock
		}
	}

	if (m_saveSprite.getGlobalBounds().contains(location))
	{
		saveBoardGame();
	}

	if (m_menuSprite.getGlobalBounds().contains(location))
	{
		m_goToMenu = true;
		return;
	}

}

void Board::saveBoardGame()
{
	std::ofstream outFile;

	outFile.open("Board.txt", std::ios::out | std::ios::trunc);

	if (!outFile.is_open())
	{
		throw FileError(); 
	}

	//Write data to the file
	try
	{
		outFile << m_ToolBarData[Time] << " "
			<< m_ToolBarData[Points] << " "
			<< m_ToolBarData[Remaining] << " "
			<< m_ToolBarData[PickedUp] << std::endl;

		if (outFile.fail())
		{
			throw std::ios_base::failure("Failed to write toolbar data to file");
		}

		for (auto it = m_stickList.begin(); it != m_stickList.end(); ++it)
		{
			it->printDataToFile(outFile);
			if (outFile.fail())
			{
				throw std::ios_base::failure("Failed to write stick data to file");
			}
		}
	}
	catch (const std::exception& e)
	{
		outFile.close();
		throw;
	}

	outFile.close();

	if (outFile.fail())
	{
		throw std::ios_base::failure("Failed to properly close the file");
	}
}

//void Board::saveBoardGame()
//{
//	std::ofstream outFile;
//
//	// Open a file (this will create the file if it does not exist)
//	outFile.open("Board.txt");
//
//	// Check if the file is open
//	if (!outFile.is_open()) 
//		throw SaveFileError();
//
//	
//	outFile << m_ToolBarData[Time] << " " << m_ToolBarData[Points] << " " << m_ToolBarData[Remaining]
//			<< " " << m_ToolBarData[PickedUp] << std::endl;
//
//
//	for (auto it = m_stickList.begin(); it != m_stickList.end(); ++it)
//	{
//		it->printDataToFile(outFile);
//	}
//
//	
//	outFile.close();
//}

void Board::outlinePickableSticksWithDelay() {
	if (m_currentPickableStick != m_PickableStickList.end()) {
		if (m_outlineClock.getElapsedTime() >= OUTLINE_DELAY) {
			(*m_currentPickableStick)->OutlineStick(); // Outline the current stick
			++m_currentPickableStick; // Move to the next stick
			m_outlineClock.restart(); // Reset the clock
		}
	}
}

void  Board::updateTime(const int time)
{
	m_ToolBarData[Time] = time;
}

// Given three collinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool Board::onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are collinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int Board::orientation(Point p, Point q, Point r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
	// for details of below formula. 
	int val = int((q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y));

	if (val == 0) return 0;  // collinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool Board::doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and 
	// special cases 
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}

