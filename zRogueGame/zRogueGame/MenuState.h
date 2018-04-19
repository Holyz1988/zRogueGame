#pragma once
#include "State.hpp"
#include "Game.h"
#include "RessourceHolder.h"
#include "Database.h"
#include "Player.h"
#include <vector>

/**
* \file			MenuState.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe qui repr�sente l'�tat Menu
*
* \details		Classe qui repr�sente et g�re l'�tat Menu
*
*/

/*! \class		MenuState
* \brief		Classe qui repr�sente et g�re l'�tat Menu, h�rite de State
*
* \details		Classe qui repr�sente et g�re l'�tat Menu, h�rite de State
*
*/
class MenuState : public State
{
public:
	/**
	* \brief	Constructeur
	*
	*Constructeur de l'�tat menu
	*
	* \param data : stock les donn�es communes associ�es � chaque �tat (fen�tre, �tat actuel)
	*/
	MenuState(GameDataRef data);

	/**
	* \brief	Initialise l'�tat menu
	*
	*Initialise l'�tat menu, avec toutes les ressources n�c�ssaires
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
	* \brief	mise a jour de la logique de l'�tat menu
	*
	*mise a jour de la logique de l'�tat menu
	*
	* \param dt : temps que met une it�ration
	*/
	void update(float dt);

	/**
	* \brief	affiche l'�tat menu
	*
	*affiche l'�tat menu
	*
	* \param dt : temps que met une it�ration
	*/
	void draw(float dt);

private:

	/**
	* \brief	Permet de passer du menu au jeu principal
	*
	*Permet de passer du menu au jeu principal
	*
	*/
	void loadGame();

	/**
	* \brief	Permet de passer du menu aux options
	*
	*Permet de passer du menu aux options
	*
	*/
	void loadOptions();

	/**
	* \brief	Permet de passer du menu aux sauvegardes
	*
	*Permet de passer du menu aux sauvegardes
	*
	*/
	void loadSaves();

	/**
	* \brief	Permet de passer du menu aux nouvelles parties
	*
	*Permet de passer du menu aux nouvelles parties
	*
	*/
	void loadPlayers();

	/**
	* \brief	V�rifie si un boutton est cliqu�
	*
	*V�rifie si un boutton est cliqu�
	*
	* \param text : r�f�rence sur un button (texte) qui est cliqu�
	*
	* \return bool�en qui nous informe si le text est cliqu� ou non
	*/
	bool isTextClicked(sf::Text& text);

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
	Database* db;/*!< Pointeur vers un objet database, permet la communication avec la BDD*/
	Player player;/*!< Objet Joueur*/

	RessourceHolder ressources;/*!< Objet RessourceHolder, stock les textures et les fonts*/
	sf::Sprite menuSprite;/*!< Sprite du fond d'�cran*/

	sf::Text mTitle;/*!< Titre de l'�tat*/
	std::vector<sf::Text> mButtons;/*!<  Bouttons affich�s lors d'une nouvelle partie*/
	sf::Music bgMusic;
};

