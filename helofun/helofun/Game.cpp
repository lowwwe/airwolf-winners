/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouse(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMouse(sf::Event t_event)
{
	float lenght = 0.0f;
	sf::Vector2f displacment;
	
	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		m_target = sf::Vector2f(t_event.mouseButton.x, t_event.mouseButton.y);
		displacment.x = static_cast<float>(t_event.mouseButton.x) - m_loaction.x;
		displacment.y = static_cast<float>(t_event.mouseButton.y) - m_loaction.y;
		lenght = std::sqrtf((displacment.x * displacment.x) + (displacment.y * displacment.y));
		displacment = displacment / lenght;
		m_velocity = displacment;
		m_velocity = m_velocity * m_speed;
		m_increment = 0.79;
		if (static_cast<float>(t_event.mouseButton.x) > m_loaction.x)
		{
			m_facing = Direction::Right;
			m_heloSprite.setScale(1.0f, 1.0f);
		}
		else
		{
			m_facing = Direction::Left;
			m_heloSprite.setScale(-1.0f, 1.0f);
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	animateHelo();
	move();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_heloSprite);
	m_window.display();
}

void Game::animateHelo()
{
	int newFrame = 0;
	m_framecounter +=m_increment;
	newFrame = static_cast<int>(m_framecounter);
	newFrame = newFrame % 4;
	if (newFrame != m_currentFrame)
	{
		m_currentFrame = newFrame;
		//m_heloSprite.setTextureRect(sf::IntRect(0, 0, 180, 64));  // 0
		//m_heloSprite.setTextureRect(sf::IntRect(0, 64, 180, 64)); // 1
		//m_heloSprite.setTextureRect(sf::IntRect(0, 128, 180, 64)); // 2
		//m_heloSprite.setTextureRect(sf::IntRect(0, 192, 180, 64)); // 3

		m_heloSprite.setTextureRect(sf::IntRect(0, 64 * m_currentFrame, 180, 64));
	}

}

void Game::move()
{
	if (m_facing != Direction::None)
	{
		m_loaction += m_velocity;
		m_heloSprite.setPosition(m_loaction);
		if (m_facing == Direction::Right && m_loaction.x > m_target.x)
		{
			m_facing = Direction::None;
			m_increment = 0.28;
		}
		if (m_facing == Direction::Left && m_loaction.x < m_target.x)
		{
			m_facing = Direction::None;
			m_increment = 0.28;
		}
		
	}
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_heloTextture.loadFromFile("ASSETS\\IMAGES\\helicopter.png"))
	{
		std::cout << "error with texture" << std::endl;
	}
	m_heloSprite.setTexture(m_heloTextture);
	m_heloSprite.setTextureRect(sf::IntRect(0, 0, 180, 64));
	m_heloSprite.setPosition(400.0f, 300.0f);
	m_heloSprite.setOrigin(90.0f, 32.0f);
}
