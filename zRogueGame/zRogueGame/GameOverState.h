#pragma once
#include "State.hpp"
#include "MenuState.h"
#include "RessourceHolder.h"
#include <vector>

/**
* \file			GameOverState.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		données du jeu
*
* \details		classe permettant de gérer l'état de fin de partie
*
*/


/*! \class		GameOverState
* \brief		Classe qui représente l'état fin de partie
*
* \details		Classe qui représente l'état fin de partie
*
*/
class GameOverState : public State
{
public:

	/**
	* \brief	Constructeur
	*
	*Constructeur de l'état fin de partie
	*
	* \param data : stock les données communes associées à chaque état (fenêtre, état actuel)
	*/
	GameOverState(GameDataRef data);

	/**
	* \brief	Intialise toutes les données nécéssaire à l'état fin de partie
	*
	*Intialise toutes les données nécéssaire à l'état fin de partie
	*
	*/
	void init();

	/**
	* \brief gestion des saisies de l'utilisateur
	*
	*gestion des saisies de l'utilisateur
	*
	*/
	void handleInput();

	/**
	* \brief mise à jour de la logique
	*
	*mise à jour de la logique
	*
	* \param dt : temps que met chaque itération
	*/
	void update(float dt);

	/**
	* \brief déssine les objets sur la fenêtre 
	*
	*déssine les objets sur la fenêtre 
	*
	*\param dt : temps que met chaque itération
	*/
	void draw(float dt);

private:
	sf::View mCamera;/*!< Vue de l'écran fin de partie*/

	/**
	* \brief Permet de passer du menu au jeu principal
	*
	*Permet de passer du menu au jeu principal
	*
	*/
	void loadMenu();

	/**
	* \brief Permet de passer du menu au jeu principal
	*
	*Permet de passer du menu au jeu principal
	*
	* \param text : Le texte qui est cliqué
	*/
	bool isTextClicked(sf::Text text);

	/**
	* \brief Permet de passer du menu au jeu principal
	*
	*Permet de passer du menu au jeu principal
	*
	* \param buttons : les bouttons de l'état fin de partie
	*/
	void changeTextDesign(std::vector<sf::Text>& buttons);

private:
	GameDataRef _data;/*!< données communes aux états (fenêtre, état actuel)*/
	Database* db;/*!< Pointeur vers un objet database, permet la communication avec la BDD*/
	Player player;/*!< Objet Joueur*/

	RessourceHolder ressources;/*!< Objet RessourceHolder, stock les textures et les fonts*/
	sf::Sprite gameOverBackground;/*!< Sprite du fond d'écran*/
	std::vector<sf::Text> mButtons;/*!< Bouttons affichés lors de la fin de partie*/
};
