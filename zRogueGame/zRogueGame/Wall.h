#pragma once
#include "Entity.h"

/**
* \file			Wall.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe représentant les tuiles du jeu
*
* \details		Classe représentant les tuiles du jeu
*/


/*! \class		Wall
* \brief		Classe représentant les tuiles du jeu
*
* \details		Classe représentant les tuiles du jeu
*
*/

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
	sf::Texture mWallTexture;/*!< */
	bool locked;/*!< */
};

