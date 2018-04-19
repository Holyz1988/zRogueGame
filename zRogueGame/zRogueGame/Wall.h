#pragma once
#include "Entity.h"

/**
* \file			Wall.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe repr�sentant les tuiles du jeu
*
* \details		Classe repr�sentant les tuiles du jeu
*/


/*! \class		Wall
* \brief		Classe repr�sentant les tuiles du jeu
*
* \details		Classe repr�sentant les tuiles du jeu
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
	* \brief		Permet d'initialiser les murs de l'ar�ne
	*
	*Permet d'initialiser les murs de l'ar�ne
	*
	* \param walls : r�f�rence vers un conteneur des murs de l'ar�ne
	* \param wall : r�f�rence vers un mur de l'ar�ne
	*/
	void initArena(std::vector<Wall>& walls, Wall& wall);

	/**
	* \brief		Permet de d�ssiner les murs de l'ar�ne
	*
	*Permet de d�ssiner les murs de l'ar�ne
	*
	* \param walls : r�f�rence vers un conteneur des murs de l'ar�ne
	* \param window : r�f�rence de la fen�tre sur laquelle on d�ssine
	*/
	void drawArena(std::vector<Wall>& walls, sf::RenderWindow& window);

	/**
	* \brief		Permet d'initialiser le sol de l'ar�ne
	*
	*Permet d'initialiser le sol de l'ar�ne
	*
	* \param ground : r�f�rence vers un conteneur du sol de l'ar�ne
	* \param tile : r�f�rence vers une tuile repr�sentant le sol de l'ar�ne
	*/
	void initGround(std::vector<Wall>& ground, Wall& tile);

	/**
	* \brief		Permet de d�ssiner le sol sur la fen�tre
	*
	*Permet de d�ssiner le sol sur la fen�tre
	*
	* \param ground : r�f�rence vers un conteneur du sol de l'ar�ne
	* \param window : r�f�rence de la fen�tre sur laquelle on d�ssine
	*/
	void drawGround(std::vector<Wall>& ground, sf::RenderWindow& window);

	/**
	* \brief		Permet de d�ssiner le spawner sur la fen�tre
	*
	*Permet de d�ssiner le spawner sur la fen�tre
	*
	* \param tile : r�f�rence vers le spawner de l'ar�ne
	* \param window : r�f�rence de la fen�tre sur laquelle on d�ssine
	*/
	void drawSpawner(Wall& tile,sf::RenderWindow& window);

public:
	sf::Texture mWallTexture;/*!< Spritesheet charg� qui contient tous les d�cors de l'ar�ne*/
	bool locked;/*!< la tuile du spawner est elle locker ou non, c'est � dire a-t-on fait apparaitre des monstre ou non ?*/
};

