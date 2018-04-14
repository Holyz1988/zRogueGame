#pragma once
#include "Entity.h"

class Character : public Entity
{
public:
	//Stats
	int currency;
	int attackDamage;
	int currentHp;
	int maxHP;
	int level;
	float mSpeed;
};

