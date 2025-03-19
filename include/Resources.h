#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <thread>
#include <vector>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>   
#include <list>
#include <stdexcept>
#include "FileError.h"
#include "SaveFileError.h"

using namespace std;
using Point = sf::Vector2f;

const int NUM_OF_TEXTURES = 15;
const int NUM_OF_SOUNDS = 5;
const int START_BUTTON = 0, QUIT_BUTTON = 2;
const int NUM_OF_MENU_BUTTONS = 3;
const sf::Vector2f BUTTON_MENU_SIZE = { 315.f, 90.f };
const int THICKNESS_FRAME = 3;
const int FPS = 60;
const double PI = 3.14159265358979323846;
const int START = 0, END = 1, FACTOR = 2;
const std::chrono::seconds OUTLINE_DURATION{ 1 };
const int TOOL_BAR_SIZE = 5;

const sf::Vector2f POINTS_TEXT_POS = { 80.f, 175.f }, REMAIN_TEXT_POS = { 80.f, 250.f },
				   TIME_TEXT_POS = { 80.f, 100.f }, PICKABLE_TEXT_POS = { 80.f , 325.f },
				   PICKED_TEXT_POS = { 80.f, 400.f };
const int SIZE_OF_TEXT = 40;

const std::string timePrefix = "Time: ";
const std::string pointsPrefix = "Points: ";
const std::string remainingPrefix = "Remaining: ";
const std::string pickablePrefix = "Pickable: ";
const std::string pickedUpPrefix = "Picked Up: ";

static const sf::Color PINK_COLOR(255, 105, 180);
const sf::Time OUTLINE_DELAY = sf::seconds(1.f);
const int MAX_STICK_LENGTH = 950, MIN_STICK_LENGTH = 50;
const int MAX_ANGLE = 360;
const int MAX_X_POS = 1300, MIN_X_POS = 500, MAX_Y_POS = 800, MIN_Y_POS = 100;
const float STICK_WITDH = 20.0f, SCREEN_WIDTH = 1920.0f, SCREEN_LENGTH = 1080.0f;
const int THICKNESS = 2;
const sf::Color NEON_YELLOW = { 255, 255, 0 }, ORANGE = {255, 165, 0};
const int MAX_STICKS = 40, MIN_STICKS = 10, MAX_POINTS = 300, MAX_STICK_POINTS = 5;
const sf::Vector2f MENU_POS = { 80, 900 }, HINT_POS = { 80, 600 }, SAVE_POS = { 80, 750 };


enum ObjectType
{
	New,
	Load,
	Quit,
	Back,
	Save,
	Hint,
	MenuBottom,
	MenuBackground,
	Background,
	WinBackground,
	LoseBackground

};

enum ToolbarType
{
	Time, 
	Points,
	Remaining, 
	Pickable, 
	PickedUp
};


enum Color { 
	Red, 
	Blue, 
	Green, 
	Orange, 
	Yellow, 
	Count 
};

class Resources {

public:

	//Singleton, provides a centralized access point to these resources.
	static Resources& instance() {
		static auto resources = Resources(); // static in function!
		return resources;
	}

	//delete copy c-tor and operator=
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;

	sf::Font& get();
	sf::Texture& get(const ObjectType type);

private:
	Resources();
	std::vector<sf::Texture> m_textures;	//to store all game textures
	sf::Font m_font;						//to store game font

};
