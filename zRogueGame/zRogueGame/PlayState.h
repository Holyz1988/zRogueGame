#pragma once

#include "MenuState.h"
#include "State.hpp"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Database.h"

class PlayState : public State
{
public:
	PlayState(GameDataRef data, Player& player);
	PlayState(GameDataRef data);
	~PlayState();
	void init();

	void handleInput();
	void update(float dt);
	void draw(float dt);
	Database* db;

private:
	void pauseGame();
	void centerCamera();


	//void updateVectors();
	//void fireBullets();
	//void drawBullets();

private:
	GameDataRef _data;


	sf::View mCamera;

	RessourceHolder mRessources;
	sf::Sprite mSpritePlayer;
	sf::Vector2f mPosPlayer;
	Player mPlayer;

	//Dragon
	Enemy mDragon;

	//Boules de feu
	Enemy mFireBall;
	std::vector<Enemy> mFireBalls;

	//Orcs
	Enemy mOrc;
	std::vector<Enemy> mOrcs;

	//Murs
	Wall mWall;
	std::vector<Wall> mWalls;

	//Sols
	Wall mTile;
	std::vector<Wall> mGround;

	//Zone de spawn
	Wall mSpawnTile;

	
};

