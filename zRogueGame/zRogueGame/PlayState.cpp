#include "PlayState.h"
#include <iostream>
#include <math.h>

using namespace std;

PlayState::PlayState(Game * game) : mOrc(sf::Vector2f(10.f, 10.f))
{
	//Loading player
	ressources.loadTexture("Player", "ressources/mainPlayer.png");
	mPlayer.sprite.setTexture(ressources.getTexture("Player"));
	mPlayer.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	//Loading dragon
	ressources.loadTexture("Dragon", "ressources/Enemy_dragon2.png");
	mDragon.sprite.setTexture(ressources.getTexture("Dragon"));
	mDragon.sprite.setTextureRect(sf::IntRect(0, 0, 128, 160));
	mDragon.rect.setPosition(sf::Vector2f(200, 200));

	//Loading orcs
	ressources.loadTexture("Orc", "ressources/orc.png");
	mOrc.sprite.setTexture(ressources.getTexture("Orc"));
	mOrc.sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mOrc.rect.setPosition(sf::Vector2f(100, 100));

	//Loading enemies
	ressources.loadTexture("Enemy1", "ressources/fireball.png");
	mEnemy.sprite.setTexture(ressources.getTexture("Enemy1"));
	mEnemy.sprite.setTextureRect(sf::IntRect(0, 4 * 64, 64, 64));
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
	mEnemy.spawnEnemies(mEnemies, mEnemy, mPlayer);//Spawn les enemies
	mEnemy.updateV(mPlayer);//MAJ des positions enemies
	mEnemy.updateMovement(mEnemies, game->window);//MAJ des mouvement enimies
	mEnemy.updatePos();

	//Mise à jour du dragon
	mDragon.updatePos();

	//Mise à jour de l'orc
	mOrc.moveEnemies(dt);
	mOrc.updatePos();

	//Mise à jour des positions et actions du joueur
	//cout << mPlayer.getCurrentHP() << endl;
	mPlayer.losingHp(mOrc);
	cout << mPlayer.getCurrentHP() << endl;
	mPlayer.bulletCollision(mEnemies);
	mPlayer.fireBullets(game->window);//MAJ des projectiles
	mPlayer.updateVectors(game->window);//MAJ des positions joueur
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
	game->window.draw(this->mDragon.sprite);
	game->window.draw(this->mOrc.sprite);
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

