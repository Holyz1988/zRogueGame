#pragma once
#include "GameState.h"

class PlayState : public GameState
{
public:
	PlayState(Game* game);

	virtual void handleInput();
	virtual void update(sf::Time dt);
	virtual void draw(sf::Time dt);

private:
	void pauseGame();
};

