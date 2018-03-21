#pragma once

#include "game.h"

class GameState
{
public:



	virtual void handleInput() = 0;
	virtual void update(sf::Time dt) = 0;
	virtual void draw(sf::Time dt) = 0;

protected:
	Game* game;
};