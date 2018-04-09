#include "PlayState.h"
#include <iostream>
#include <math.h>

using namespace std;

PlayState::PlayState(Game * game) : mOrc(sf::Vector2f(10.f, 10.f))
{
	//Chargement du sol

	mRessources.loadTexture("Tiles", "ressources/tiles.png");
	mTile.sprite.setTexture(mRessources.getTexture("Tiles"));
	mTile.sprite.setTextureRect(sf::IntRect(7 * 32, 32, 32, 32));
	mTile.initGround(mGround, mTile);

	//Chargement des murs
	mWall.sprite.setTexture(mRessources.getTexture("Tiles"));
	mWall.sprite.setTextureRect(sf::IntRect(3 * 32, 32, 32, 32));
	mWall.initArena(mWalls, mWall);

	//Chargement du spawner mob
	mSpawnTile.sprite.setTexture(mRessources.getTexture("Tiles"));
	mSpawnTile.sprite.setTextureRect(sf::IntRect(3 * 32, 5 * 32, 3 * 32, 3 * 32));

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
	mOrc.spawEnemies(mOrcs, mOrc);

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
	mFireBall.spawnFireBalls(mFireBalls, mFireBall, mPlayer);//Spawn les enemies
	mFireBall.updateV(mPlayer);//MAJ des positions enemies
	mFireBall.updateMovement(mFireBalls, game->window, dt);//MAJ des mouvement enimies
	mFireBall.updatePos();

	//Mise à jour du dragon
	mDragon.updatePos();

	//Mise à jour de l'orc
	for (int i = 0; i < mOrcs.size(); i++)
	{
		mOrcs[i].moveEnemies(dt);
		mOrcs[i].updatePos();
	}

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
	//On déssine le monde
	mWall.drawArena(mWalls, game->window);
	mTile.drawGround(mGround, game->window);
	//game->window.draw(this->mWall.rect);
	mSpawnTile.drawSpawner(mSpawnTile, game->window);

	//On déssine le joueur et les boules
	game->window.draw(this->mPlayer.sprite);
	mPlayer.drawBullets(game->window);

	//Boules de feux
	//mFireBall.drawEnemies(mFireBalls, game->window);

	//Dragon
	//game->window.draw(this->mDragon.sprite);

	//Orcs
	mPlayer.spawnOrcs(mSpawnTile);
	if (mPlayer.getSpawnerStatus())
		mOrc.drawEnemies(mOrcs, this->game->window);
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


