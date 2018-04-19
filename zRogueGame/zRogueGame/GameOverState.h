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
* \brief		donn�es du jeu
*
* \details		classe permettant de g�rer l'�tat de fin de partie
*
*/


/*! \class		GameOverState
* \brief		Classe qui repr�sente l'�tat fin de partie
*
* \details		Classe qui repr�sente l'�tat fin de partie
*
*/
class GameOverState : public State
{
public:

	/**
	* \brief	Constructeur
	*
	*Constructeur de l'�tat fin de partie
	*
	* \param data : stock les donn�es communes associ�es � chaque �tat (fen�tre, �tat actuel)
	*/
	GameOverState(GameDataRef data);

	/**
	* \brief	Intialise toutes les donn�es n�c�ssaire � l'�tat fin de partie
	*
	*Intialise toutes les donn�es n�c�ssaire � l'�tat fin de partie
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
	* \brief mise � jour de la logique
	*
	*mise � jour de la logique
	*
	* \param dt : temps que met chaque it�ration
	*/
	void update(float dt);

	/**
	* \brief d�ssine les objets sur la fen�tre 
	*
	*d�ssine les objets sur la fen�tre 
	*
	*\param dt : temps que met chaque it�ration
	*/
	void draw(float dt);

private:
	sf::View mCamera;/*!< Vue de l'�cran fin de partie*/

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
	* \param text : Le texte qui est cliqu�
	*/
	bool isTextClicked(sf::Text text);

	/**
	* \brief Permet de passer du menu au jeu principal
	*
	*Permet de passer du menu au jeu principal
	*
	* \param buttons : les bouttons de l'�tat fin de partie
	*/
	void changeTextDesign(std::vector<sf::Text>& buttons);

private:
	GameDataRef _data;/*!< donn�es communes aux �tats (fen�tre, �tat actuel)*/
	Database* db;/*!< Pointeur vers un objet database, permet la communication avec la BDD*/
	Player player;/*!< Objet Joueur*/

	RessourceHolder ressources;/*!< Objet RessourceHolder, stock les textures et les fonts*/
	sf::Sprite gameOverBackground;/*!< Sprite du fond d'�cran*/
	std::vector<sf::Text> mButtons;/*!< Bouttons affich�s lors de la fin de partie*/
};
