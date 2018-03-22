#include "PlayState.h"
#include "MenuState.h"
#include <iostream>

#include "GameState.h"

PlayState::PlayState(Game * game)
{
	ressources.loadTexture("Player", "mainPlayer.png");
	player.sprite.setTexture(ressources.getTexture("Player"));
	player.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
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
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
				pauseGame();
			break;
		}
	}
}

void PlayState::update(float dt)
{
	player.update(dt);
}

void PlayState::draw(float dt)
{
	game->window.draw(this->player.sprite);
}

void PlayState::pauseGame()
{
}
