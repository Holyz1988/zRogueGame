#pragma once
#include "Entity.h"

class Wall : public Entity
{
public:
	Wall();

	void initArena(std::vector<Wall>& walls, Wall& wall);
	void drawArena(std::vector<Wall>& walls, sf::RenderWindow& window);
};

