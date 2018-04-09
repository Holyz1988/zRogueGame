#pragma once
#include "PlayState.h"
#include "MenuState.h"
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

class PlayState : public GameState
{
public:
	PlayState(Game* game);

	virtual void handleInput();
	virtual void update(float dt);
	virtual void draw(float dt);

private:
	void pauseGame();
	void centerCamera();

	//void updateVectors();
	//void fireBullets();
	//void drawBullets();

private:
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

