#pragma once
#include "State.hpp"
#include "MenuState.h"
#include "RessourceHolder.h"
#include <vector>

/**
* \file			OptionState.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		classe permettant de gérer l'état option
*
* \details		classe permettant de gérer l'état option
*
*/


/*! \class		OptionState
* \brief		classe permettant de gérer l'état option
*
* \details		classe permettant de gérer l'état option
*
*/

class OptionState : public State
{
public:
	/**
	* \brief	Constructeur
	*
	*Constructeur de l'état option
	*
	* \param data : stock les données communes associées à chaque état (fenêtre, état actuel)
	*/
	OptionState(GameDataRef data);

	/**
	* \brief	Initialise l'état option
	*
	*Initialise l'état option, avec toutes les ressources nécéssaires
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
	* \brief	mise a jour de la logique de l'état option
	*
	*mise a jour de la logique de l'état option
	*
	* \param dt : temps que met une itération
	*/
	void update(float dt);

	/**
	* \brief	affiche l'état option
	*
	*affiche l'état option
	*
	* \param dt : temps que met une itération
	*/
	void draw(float dt);

private:
	

	/**
	* \brief	Permet de passer de l'état option à l'état menu
	*
	*Permet de passer de l'état option à l'état menu
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
	void changeTextDesign(sf::Text& buttons);

private:
	GameDataRef _data;/*!< données communes aux états (fenêtre, état actuel)*/

	RessourceHolder ressources;/*!<  Objet RessourceHolder, stock les textures et les fonts*/
	sf::Sprite optionBackground;/*!< Sprite du fond d'écran*/

	sf::Text mButton;/*!< Bouttons affichés lors de l'état option*/
	sf::Text mYesNo;/*!< Texte affichant oui ou non*/
	sf::Text mTitle;/*!< Titre de l'état*/
};


