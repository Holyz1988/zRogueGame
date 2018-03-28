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

	//enemies
	Enemy mDragon;

	Enemy mFireBall;
	std::vector<Enemy> mFireBalls;

	Enemy mOrc;
	std::vector<Enemy> mOrcs;

	Wall mWall;
	std::vector<Wall> mWalls;

};

