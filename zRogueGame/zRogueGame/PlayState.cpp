#include <iostream>
#include <math.h>

#include "PlayState.h"
#include "MenuState.h"
#include "GameState.h"

PlayState::PlayState(Game * game)
{
	ressources.loadTexture("Player", "mainPlayer.png");
	mPlayer.sprite.setTexture(ressources.getTexture("Player"));
	mPlayer.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->game = game;
}

void PlayState::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Ferme la fen�tre */
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
	mEnemy.spawnEnemies(mEnemies, mEnemy, game->window, mPlayer);//Spawn les enemies
	mEnemy.updateVectors(mPlayer);//MAJ des positions enemies
	mEnemy.updateMovement(mEnemies, game->window, mPlayer);//MAJ des mouvement enimies
	mEnemy.bulletCollision(mPlayer.getBullets());
	mPlayer.fireBullets(game->window);//MAJ des projectiles
	mPlayer.updateVectors(game->window);//MAJ des positions joueurs
	mPlayer.update(dt);//Met � jour la position du joueur
}

void PlayState::draw(float dt)
{
	game->window.draw(this->mPlayer.sprite);
	mPlayer.drawBullets(game->window);
	mEnemy.drawEnemies(mEnemies, game->window);
}

void PlayState::pauseGame()
{
}

