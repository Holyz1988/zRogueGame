#include "Wall.h"
#include <iostream>

#define HORIZONTAL_WALL 40
#define VERTICAL_WALL 15
#define BLOCK_SIZE 32

Wall::Wall()
{
	rect.setSize(sf::Vector2f(32.f, 32.f));
	rect.setPosition(sf::Vector2f(0.f, 0.f));
}

void Wall::initArena(std::vector<Wall>& walls, Wall& wall)
{
	//On dessine les murs horizontaux du haut
	for (size_t i = 0; i < HORIZONTAL_WALL; i++)
	{
		wall.rect.setPosition(sf::Vector2f(((float)i + 1.f) * BLOCK_SIZE, 0.f));
		walls.push_back(wall);
	}

	//On dessine les murs verticaux gauche
	for (size_t i = 0; i <= VERTICAL_WALL; i++)
	{
		wall.rect.setPosition(sf::Vector2f(0.f, (float)i * BLOCK_SIZE));
		walls.push_back(wall);
	}

	//On dessine les murs verticaux droite
	for (size_t i = 0; i <= VERTICAL_WALL; i++)
	{
		wall.rect.setPosition(sf::Vector2f(HORIZONTAL_WALL * BLOCK_SIZE, (float)i * BLOCK_SIZE));
		walls.push_back(wall);
	}

	//On dessine les murs horizontaux du bas
	for (size_t i = 0; i <= HORIZONTAL_WALL; i++)
	{
		wall.rect.setPosition(sf::Vector2f(((float)i + 1.f) * BLOCK_SIZE, VERTICAL_WALL * BLOCK_SIZE));
		walls.push_back(wall);
	}
}

void Wall::drawArena(std::vector<Wall>& walls, sf::RenderWindow & window)
{
	for (size_t i = 0; i < walls.size(); i++)
	{
		walls[i].sprite.setPosition(walls[i].rect.getPosition()); // On aligne le sprite dans le rectangle
		window.draw(walls[i].sprite);
	}
}

void Wall::initGround(std::vector<Wall>& ground, Wall& tile)
{
	for (size_t i = 1; i < HORIZONTAL_WALL; i++)
	{
		for (size_t j = 1; j < VERTICAL_WALL; j++)
		{
			tile.rect.setPosition(sf::Vector2f(BLOCK_SIZE * i, BLOCK_SIZE * j));
			ground.push_back(tile);
		}
	}
}

void Wall::drawGround(std::vector<Wall>& ground, sf::RenderWindow& window)
{
	for (size_t i = 0; i < ground.size(); i++)
	{
		ground[i].sprite.setPosition(ground[i].rect.getPosition());
		window.draw(ground[i].sprite);
	}
}

