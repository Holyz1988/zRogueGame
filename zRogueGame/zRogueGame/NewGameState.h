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
* \brief		classe permettant de gérer l'état chargement des parties
*
* \details		classe permettant de gérer l'état chargement des parties
*
*/


/*! \class		NewGameState
* \brief		classe permettant de gérer l'état chargement des parties
*
* \details		classe permettant de gérer l'état chargement des parties
*
*/

class NewGameState : public State
{
public:
	/**
	* \brief	Constructeur
	*
	*Constructeur de l'état chargement des parties
	*
	* \param data : stock les données communes associées à chaque état (fenêtre, état actuel)
	*/
	NewGameState(GameDataRef data);

	/**
	* \brief	Initialise l'état chargement partie
	*
	*Initialise l'état chargement partie, avec toutes les ressources nécéssaires
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
	* \brief	mise a jour de la logique de l'état chargement partie
	*
	*mise a jour de la logique de l'état chargement partie
	*
	* \param dt : temps que met une itération
	*/
	void update(float dt);

	/**
	* \brief	affiche l'état chargement partie
	*
	*affiche l'état chargement partie
	*
	* \param dt : temps que met une itération
	*/
	void draw(float dt);

private:
	

	/**
	* \brief	Permet de passer de l'état chargement partie à l'état menu
	*
	*Permet de passer du menu au jeu principal
	*
	*/
	void loadMenu();

	/**
	* \brief	Vérifie si un boutton est cliqué
	*
	*Vérifie si un boutton est cliqué
	*
	* \param text : button qui est cliqué
	*
	* \return booléen qui nous informe si le text est cliqué ou non
	*/
	bool isTextClicked(sf::Text text);

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
	std::vector<Player> players;/*!< vecteur d'objet Joueur*/
	Database* db;/*!< Pointeur vers un objet database, permet la communication avec la BDD*/

	RessourceHolder ressources;/*!<  Objet RessourceHolder, stock les textures et les fonts*/
	sf::Sprite newGameBackground;/*!< Sprite du fond d'écran*/

	sf::Text mTitle;/*!< Titre de l'état*/
	std::vector<sf::Text> mButtons;/*!< Bouttons affichés lors du chargement d'une partie*/
};

