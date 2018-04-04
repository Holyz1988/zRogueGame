#include "PlayState.h"
#include <iostream>
#include <math.h>

using namespace std;

PlayState::PlayState(Game * game) : mOrc(sf::Vector2f(10.f, 10.f))
{
	//Chargement du sol

	mRessources.loadTexture("Ground", "ressources/tiles.png");
	mTile.sprite.setTexture(mRessources.getTexture("Ground"));
	mTile.sprite.setTextureRect(sf::IntRect(7 * 32, 32, 32, 32));
	mTile.initGround(mGround, mTile);

	//Chargement des murs
	mRessources.loadTexture("Walls", "ressources/tiles.png");
	mWall.sprite.setTexture(mRessources.getTexture("Walls"));
	mWall.sprite.setTextureRect(sf::IntRect(3 * 32, 32, 32, 32));
	mWall.initArena(mWalls, mWall);

	//Chargement du joueur
	mRessources.loadTexture("Player", "ressources/mainPlayer.png");
	mPlayer.sprite.setTexture(mRessources.getTexture("Player"));
	mPlayer.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	//Chargement des dragons
	mRessources.loadTexture("Dragon", "ressources/Enemy_dragon2.png");
	mDragon.sprite.setTexture(mRessources.getTexture("Dragon"));
	mDragon.sprite.setTextureRect(sf::IntRect(0, 0, 128, 160));
	mDragon.rect.setPosition(sf::Vector2f(200, 200));

	//Chargement des orcs
	mRessources.loadTexture("Orc", "ressources/orc.png");
	mOrc.sprite.setTexture(mRessources.getTexture("Orc"));
	mOrc.sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mOrc.rect.setPosition(sf::Vector2f(100, 100));

	//Chargement des boules de feux
	mRessources.loadTexture("Enemy1", "ressources/fireball.png");
	mFireBall.sprite.setTexture(mRessources.getTexture("Enemy1"));
	mFireBall.sprite.setTextureRect(sf::IntRect(0, 4 * 64, 64, 64));
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
	//Mise à jour des positions et actions enemies
	mFireBall.spawnEnemies(mFireBalls, mFireBall, mPlayer);//Spawn les enemies
	mFireBall.updateV(mPlayer);//MAJ des positions enemies
	mFireBall.updateMovement(mFireBalls, game->window, dt);//MAJ des mouvement enimies
	mFireBall.updatePos();

	//Mise à jour du dragon
	mDragon.updatePos();

	//Mise à jour de l'orc
	mOrc.moveEnemies(dt);
	mOrc.updatePos();

	//Mise à jour des positions et actions du joueur
	mPlayer.losingHp(mOrc);
	mPlayer.bulletCollision(mFireBalls);
	mPlayer.fireBullets(game->window, mWalls);//MAJ des projectiles
	mPlayer.updateVectors(game->window);//MAJ des positions joueur
	mPlayer.update(dt);//Met à jour la position du joueur

	//On place la caméra
	centerCamera();
	game->window.setView(mCamera);
}

void PlayState::draw(float dt)
{	
	mWall.drawArena(mWalls, game->window);
	mTile.drawGround(mGround, game->window);
	game->window.draw(this->mWall.rect);
	game->window.draw(this->mPlayer.sprite);
	mPlayer.drawBullets(game->window);
	mFireBall.drawEnemies(mFireBalls, game->window);
	game->window.draw(this->mDragon.sprite);
	game->window.draw(this->mOrc.sprite);
}

void PlayState::pauseGame()
{
	//TODO
}

void PlayState::centerCamera()
{
	this->mCamera.setSize(sf::Vector2f((float)game->window.getSize().x, (float)game->window.getSize().y));
	this->mCamera.setCenter(mPlayer.rect.getPosition());
}


