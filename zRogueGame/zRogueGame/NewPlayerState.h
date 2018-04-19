#pragma once

#include "State.hpp"
#include "MenuState.h"
#include "RessourceHolder.h"
#include <vector>

/**
* \file			NewPlayerState.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		classe permettant de gérer l'état nouvelle partie
*
* \details		classe permettant de gérer l'état nouvelle partie
*
*/


/*! \class		NewGameState
* \brief		classe permettant de gérer l'état nouvelle partie
*
* \details		classe permettant de gérer l'état nouvelle partie
*
*/

class NewPlayerState : public State
{
public:
	/**
	* \brief	Constructeur
	*
	*Constructeur de l'état nouvelle partie
	*
	* \param data : stock les données communes associées à chaque état (fenêtre, état actuel)
	*/
	NewPlayerState(GameDataRef data);

	/**
	* \brief	Initialise l'état nouvelle partie
	*
	*Initialise l'état nouvelle partie, avec toutes les ressources nécéssaires
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
	* \brief	mise a jour de la logique de l'état nouvelle partie
	*
	*mise a jour de la logique de l'état nouvelle partie
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
	* \brief	Permet de passer de l'état nouvelle partie à l'état menu
	*
	*Permet de passer de l'état nouvelle partie à l'état menu
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
	* \param buttons : référence vers les bouttons (textes) survolés
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
