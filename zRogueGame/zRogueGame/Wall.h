#pragma once
#include "Entity.h"

class Wall : public Entity
{
public:
	Wall();

	void initArena(std::vector<Wall>& walls, Wall& wall);
	void drawArena(std::vector<Wall>& walls, sf::RenderWindow& window);

	void initGround(std::vector<Wall>& ground, Wall& tile);
	void drawGround(std::vector<Wall>& ground, sf::RenderWindow& window);

	void drawSpawner(Wall& tile,sf::RenderWindow& window);

public:
	sf::Texture mWallTexture;
};

