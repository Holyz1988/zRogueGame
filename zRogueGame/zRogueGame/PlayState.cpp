#include "PlayState.h"
#include "MenuState.h"
#include <iostream>

#include "GameState.h"

PlayState::PlayState(Game * game)
{
	this->game = game;
}

void PlayState::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Ferme la fenêtre */
		case sf::Event::Closed:
			this->game->window.close();
			break;

			//pause game
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				pauseGame();
			break;
		}
	}
}

void PlayState::update(sf::Time dt)
{
}

void PlayState::draw(sf::Time dt)
{
	sf::RectangleShape rect;
	rect.setPosition(sf::Vector2f(100, 100));
	rect.setFillColor(sf::Color::Green);
	rect.setSize(sf::Vector2f(64, 64));

	game->window.draw(rect);
}

void PlayState::pauseGame()
{
}
