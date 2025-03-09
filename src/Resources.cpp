#pragma once

#include <SFML/Graphics.hpp>
#include "Resources.h"
#include <iostream>




Resources::Resources() {

	m_textures.resize(NUM_OF_TEXTURES);
	//m_buffers.resize(NUM_OF_SOUNDS);

	// menu
	m_textures[MenuBackground].loadFromFile("menu.png");
	m_textures[New].loadFromFile("new.png");
	//m_textures[Help].loadFromFile("help.png");
	m_textures[Quit].loadFromFile("quit.png");
	m_textures[Save].loadFromFile("save.png");
	m_textures[Hint].loadFromFile("hint.png");
	m_textures[Load].loadFromFile("load.png");
	m_textures[MenuBottom].loadFromFile("backToMenu.png");
	m_textures[Background].loadFromFile("background.png");
	//m_textures[HelpBackground].loadFromFile("helpBackground.png");

	// back
	m_textures[MenuBackground].loadFromFile("menu.png");
	m_textures[WinBackground].loadFromFile("WinBackground.png");
	m_textures[LoseBackground].loadFromFile("LoseBackground.png");

	m_font.loadFromFile("arial.ttf");

	//m_buffers[ClickSound].loadFromFile("clickSound.wav");
	

	//m_menuMusic.openFromFile("menuSong.ogg");
	//m_gameMusic.openFromFile("gameSong.ogg");
	//m_menuMusic.setVolume(MENU_SONG_VOLUME);
	//m_gameMusic.setVolume(GAME_SONG_VOLUME);

}
//=========================================================
sf::Texture& Resources::get(const ObjectType type) {

	return m_textures[type];

}
//=========================================================
sf::Font& Resources::get() {

	return m_font;
}
//=========================================================
//void Resources::playSound(const SoundType type) {
//
//	m_sound.setBuffer(m_buffers[type]);
//	m_sound.play();
//}
//=========================================================
//void Resources::playMusic(const MusicType type) {
//
//	if (type == MenuMusic) {
//		m_gameMusic.stop();
//		m_menuMusic.play();
//		m_menuMusic.setLoop(true);
//	}
//	else {
//		m_menuMusic.stop();
//		m_gameMusic.play();
//		m_gameMusic.setLoop(true);
//	}
//}
