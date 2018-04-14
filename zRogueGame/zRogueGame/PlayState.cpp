#include "PlayState.h"
#include <iostream>
#include <math.h>

using namespace std;

PlayState::PlayState(GameDataRef data) : _data(data)
{

}
//: mOrc(sf::Vector2f(10.f, 10.f))
void PlayState::init()
{
	srand(time(NULL));
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

	//Chargement des boules de feux
	mRessources.loadTexture("Enemy1", "ressources/fireball.png");
	mFireBall.sprite.setTexture(mRessources.getTexture("Enemy1"));
	mFireBall.sprite.setTextureRect(sf::IntRect(0, 4 * 64, 64, 64));
}

void PlayState::handleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Ferme la fen�tre */
		case sf::Event::Closed:
			this->_data->window.close();
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
	//Mise � jour des positions et actions enemies
	mFireBall.spawnFireBalls(mFireBalls, mFireBall, mPlayer);//Spawn les enemies
	mFireBall.updateV(mPlayer);//MAJ des positions enemies
	mFireBall.updateMovement(mFireBalls, this->_data->window, dt);//MAJ des mouvement enimies
	mFireBall.updatePos();

	//Mise � jour du dragon
	mDragon.updatePos();

	//Spawn oircs
	if (mPlayer.getSpawnerStatus() && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		mOrc.spawEnemies(mOrcs, mOrc);
	//Mise � jour de l'orc
	for (int i = 0; i < mOrcs.size(); i++)
	{
		mOrcs[i].moveEnemies(dt);
		mOrcs[i].updatePos();
	}

	//Mise � jour des positions et actions du joueur
	mPlayer.losingHp(mOrcs);
	mPlayer.fireBallBulletCollision(mFireBalls);
	mPlayer.fireBullets(this->_data->window, mWalls);//MAJ des projectiles
	mPlayer.updateVectors(this->_data->window);//MAJ des positions joueur
	mPlayer.update(dt, mWalls);//Met � jour la position du joueur

	//On place la cam�ra
	centerCamera();
	this->_data->window.setView(mCamera);
}

void PlayState::draw(float dt)
{
	//On d�ssine le monde
	mWall.drawArena(mWalls, this->_data->window);
	mTile.drawGround(mGround, this->_data->window);
	//game->window.draw(this->mWall.rect);
	mSpawnTile.drawSpawner(mSpawnTile, this->_data->window);

	//On d�ssine le joueur et les boules
	this->_data->window.draw(this->mPlayer.sprite);
	mPlayer.drawBullets(this->_data->window);

	//Boules de feux
	//mFireBall.drawEnemies(mFireBalls, game->window);

	//Dragon
	//game->window.draw(this->mDragon.sprite);

	//Orcs
	mPlayer.spawnOrcs(mSpawnTile);
	if (mPlayer.getSpawnerStatus())
		mOrc.drawEnemies(mOrcs, this->_data->window);
}

void PlayState::pauseGame()
{
	//TODO
	float posX = this->_data->window.getSize().x;
	float posY = this->_data->window.getSize().y;

	this->mCamera.setCenter(sf::Vector2f(posX / 2, posY / 2));
	cout << posX / 2 << ", " << posY / 2 << endl;
	this->_data->machine.removeState();
	this->_data->machine.addState(StateRef(new MenuState(this->_data)), true);
}

void PlayState::centerCamera()
{
	this->mCamera.setSize(sf::Vector2f((float)this->_data->window.getSize().x, (float)this->_data->window.getSize().y));
	this->mCamera.setCenter(mPlayer.rect.getPosition());
}


//TODO LES MOBS ENLEVE DES HP MEME QUAND ILS NE SONT PAS SPAWN, FAIRE EN SORTE DE LES DESACTIVER QUAND IL NE SONT PAS DESSINER
