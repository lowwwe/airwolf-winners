/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

enum class Direction
{
	None,
	Left,
	Right
};


class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void animateHelo();
	void move();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	sf::Texture m_heloTextture; // texture helo
	sf::Sprite m_heloSprite; // sprite for helo
	bool m_exitGame; // control exiting game

	int m_currentFrame = 0; // 0,1,2,3
	float m_framecounter = 0.0f; // counter for frames
	float m_increment = 0.2f; // frame increment


	sf::Vector2f m_loaction{ 400.0f,300.0f };// helo location
	sf::Vector2f m_velocity{ 0.0f,-0.0f };// velocity
	Direction m_facing = Direction::None;
	float m_speed = 7.0f;
	sf::Vector2f m_target;

};

#endif // !GAME_HPP

