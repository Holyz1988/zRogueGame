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
* \brief		Classe qui représente l'état Menu
*
* \details		Classe qui représente et gère l'état Menu
*
*/

/*! \class		MenuState
* \brief		Classe qui représente et gère l'état Menu, hérite de State
*
* \details		Classe qui représente et gère l'état Menu, hérite de State
*
*/
class MenuState : public State
{
public:
	/**
	* \brief	Constructeur
	*
	*Constructeur de l'état menu
	*
	* \param data : stock les données communes associées à chaque état (fenêtre, état actuel)
	*/
	MenuState(GameDataRef data);

	/**
	* \brief	Initialise l'état menu
	*
	*Initialise l'état menu, avec toutes les ressources nécéssaires
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
	* \brief	mise a jour de la logique de l'état menu
	*
	*mise a jour de la logique de l'état menu
	*
	* \param dt : temps que met une itération
	*/
	void update(float dt);

	/**
	* \brief	affiche l'état menu
	*
	*affiche l'état menu
	*
	* \param dt : temps que met une itération
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
	* \brief	Vérifie si un boutton est cliqué
	*
	*Vérifie si un boutton est cliqué
	*
	* \param text : référence sur un button (texte) qui est cliqué
	*
	* \return booléen qui nous informe si le text est cliqué ou non
	*/
	bool isTextClicked(sf::Text& text);

	/**
	* \brief	Change le style du boutton survolé
	*
	*Change le style du boutton survolé
	*
	* \param buttons : les bouttons (textes) survolés
	*/
	void changeTextDesign(std::vector<sf::Text>& buttons);

private:
	GameDataRef _data;/*!< données communes aux états (fenêtre, état actuel)*/
	Database* db;/*!< Pointeur vers un objet database, permet la communication avec la BDD*/
	Player player;/*!< Objet Joueur*/

	RessourceHolder ressources;/*!< Objet RessourceHolder, stock les textures et les fonts*/
	sf::Sprite menuSprite;/*!< Sprite du fond d'écran*/

	sf::Text mTitle;/*!< Titre de l'état*/
	std::vector<sf::Text> mButtons;/*!<  Bouttons affichés lors d'une nouvelle partie*/
	sf::Music bgMusic;
};

