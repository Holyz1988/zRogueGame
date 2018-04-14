#pragma once
#include "State.hpp"
#include "Game.h"

class GameOverState
{
public:
	GameOverState(GameDataRef data);

private:
	GameDataRef _data;
};

