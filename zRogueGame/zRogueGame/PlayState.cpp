#include "PlayState.h"
#include "MenuState.h"
#include <iostream>

#include "GameState.h"

PlayState::PlayState(Game * game)
{
	this->rect.setSize(sf::Vector2f(32, 32));
	this->rect.setPosition(sf::Vector2f(200, 200));
	this->rect.setFillColor(sf::Color::Red);
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
	game->window.draw(this->rect);
}

void PlayState::pauseGame()
{
}
