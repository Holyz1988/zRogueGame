#pragma once

#include "game.h"

class GameState
{
public:
	virtual void handleInput() = 0;
	virtual void update(float dt) = 0;
	virtual void draw(float dt) = 0;

protected:
	Game* game;
};