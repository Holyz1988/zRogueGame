#pragma once
#include "PlayState.h"
#include "MenuState.h"
#include "GameState.h"
#include "Player.h"
#include "Enemy.h"

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
	sf::View Camera;

	RessourceHolder ressources;
	sf::Sprite mSpritePlayer;
	sf::Vector2f posPlayer;
	Player mPlayer;

	//enemies
	Enemy mDragon;

	Enemy mFireBall;
	std::vector<Enemy> mFireBalls;

	Enemy mOrc;
	std::vector<Enemy> mOrcs;
};

