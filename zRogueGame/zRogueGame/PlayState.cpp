#include "PlayState.h"
#include <iostream>
#include <math.h>

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
	mEnemy.spawnEnemies(mEnemies, mEnemy, mPlayer);//Spawn les enemies
	mEnemy.updateV(mPlayer);//MAJ des positions enemies
	mEnemy.updateMovement(mEnemies, game->window);//MAJ des mouvement enimies
	mPlayer.bulletCollision(mEnemies);
	mPlayer.fireBullets(game->window);//MAJ des projectiles
	mPlayer.updateVectors(game->window);//MAJ des positions joueurs
	mPlayer.update(dt);//Met à jour la position du joueur
}

void PlayState::draw(float dt)
{
	/*
	TODO
	Faire la caméra
	centerCamera();
	game->window.setView(Camera);
	*/
	game->window.draw(this->mPlayer.sprite);
	mPlayer.drawBullets(game->window);
	mEnemy.drawEnemies(mEnemies, game->window);
}

void PlayState::pauseGame()
{
}
/*
void PlayState::centerCamera()
{
	this->Camera.setCenter(mPlayer.rect.getPosition());
}
*/

