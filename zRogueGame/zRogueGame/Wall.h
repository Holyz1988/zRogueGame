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
	/**
	* \brief		Constructeur
	*
	*Constructeur de la classe Wall
	*
	*/
	Wall();


	/**
	* \brief		Permet d'initialiser les murs de l'arène
	*
	*Permet d'initialiser les murs de l'arène
	*
	* \param walls : référence vers un conteneur des murs de l'arène
	* \param wall : référence vers un mur de l'arène
	*/
	void initArena(std::vector<Wall>& walls, Wall& wall);

	/**
	* \brief		Permet de déssiner les murs de l'arène
	*
	*Permet de déssiner les murs de l'arène
	*
	* \param walls : référence vers un conteneur des murs de l'arène
	* \param window : référence de la fenêtre sur laquelle on déssine
	*/
	void drawArena(std::vector<Wall>& walls, sf::RenderWindow& window);

	/**
	* \brief		Permet d'initialiser le sol de l'arène
	*
	*Permet d'initialiser le sol de l'arène
	*
	* \param ground : référence vers un conteneur du sol de l'arène
	* \param tile : référence vers une tuile représentant le sol de l'arène
	*/
	void initGround(std::vector<Wall>& ground, Wall& tile);

	/**
	* \brief		Permet de déssiner le sol sur la fenêtre
	*
	*Permet de déssiner le sol sur la fenêtre
	*
	* \param ground : référence vers un conteneur du sol de l'arène
	* \param window : référence de la fenêtre sur laquelle on déssine
	*/
	void drawGround(std::vector<Wall>& ground, sf::RenderWindow& window);

	/**
	* \brief		Permet de déssiner le spawner sur la fenêtre
	*
	*Permet de déssiner le spawner sur la fenêtre
	*
	* \param tile : référence vers le spawner de l'arène
	* \param window : référence de la fenêtre sur laquelle on déssine
	*/
	void drawSpawner(Wall& tile,sf::RenderWindow& window);

public:
	sf::Texture mWallTexture;/*!< Spritesheet chargé qui contient tous les décors de l'arène*/
	bool locked;/*!< la tuile du spawner est elle locker ou non, c'est à dire a-t-on fait apparaitre des monstre ou non ?*/
};

