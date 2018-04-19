#pragma once

#include "State.hpp"
#include "MenuState.h"
#include "RessourceHolder.h"
#include <vector>

/**
* \file			NewGameState.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		classe permettant de g�rer l'�tat chargement des parties
*
* \details		classe permettant de g�rer l'�tat chargement des parties
*
*/


/*! \class		NewGameState
* \brief		classe permettant de g�rer l'�tat chargement des parties
*
* \details		classe permettant de g�rer l'�tat chargement des parties
*
*/

class NewGameState : public State
{
public:
	/**
	* \brief	Constructeur
	*
	*Constructeur de l'�tat chargement des parties
	*
	* \param data : stock les donn�es communes associ�es � chaque �tat (fen�tre, �tat actuel)
	*/
	NewGameState(GameDataRef data);

	/**
	* \brief	Initialise l'�tat chargement partie
	*
	*Initialise l'�tat chargement partie, avec toutes les ressources n�c�ssaires
	*
	*/
	void init();

	/**
	* \brief	gestion de la saisie utilisateur
	*
	*gestion de la saisie utilisateur
	*
	*/
	void handleInput();

	/**
	* \brief	mise a jour de la logique de l'�tat chargement partie
	*
	*mise a jour de la logique de l'�tat chargement partie
	*
	* \param dt : temps que met une it�ration
	*/
	void update(float dt);

	/**
	* \brief	affiche l'�tat chargement partie
	*
	*affiche l'�tat chargement partie
	*
	* \param dt : temps que met une it�ration
	*/
	void draw(float dt);

private:
	

	/**
	* \brief	Permet de passer de l'�tat chargement partie � l'�tat menu
	*
	*Permet de passer du menu au jeu principal
	*
	*/
	void loadMenu();

	/**
	* \brief	V�rifie si un boutton est cliqu�
	*
	*V�rifie si un boutton est cliqu�
	*
	* \param text : button qui est cliqu�
	*
	* \return bool�en qui nous informe si le text est cliqu� ou non
	*/
	bool isTextClicked(sf::Text text);

	/**
	* \brief	Change le style du boutton survol�
	*
	*Change le style du boutton survol�
	*
	* \param buttons : les bouttons (textes) survol�s
	*/
	void changeTextDesign(std::vector<sf::Text>& buttons);

private:
	GameDataRef _data;/*!< donn�es communes aux �tats (fen�tre, �tat actuel)*/
	std::vector<Player> players;/*!< vecteur d'objet Joueur*/
	Database* db;/*!< Pointeur vers un objet database, permet la communication avec la BDD*/

	RessourceHolder ressources;/*!<  Objet RessourceHolder, stock les textures et les fonts*/
	sf::Sprite newGameBackground;/*!< Sprite du fond d'�cran*/

	sf::Text mTitle;/*!< Titre de l'�tat*/
	std::vector<sf::Text> mButtons;/*!< Bouttons affich�s lors du chargement d'une partie*/
};

