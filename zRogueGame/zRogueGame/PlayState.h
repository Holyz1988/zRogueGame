#pragma once
#include "GameState.h"
#include "RessourceHolder.h"
#include "Player.h"

class PlayState : public GameState
{
public:
	PlayState(Game* game);

	virtual void handleInput();
	virtual void update(float dt);
	virtual void draw(float dt);

private:
	void pauseGame();

private:
	RessourceHolder ressources;
	sf::Sprite mPlayer;
	sf::Vector2f posPlayer;
	Player player;
};

