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
* \brief		classe permettant de g�rer l'�tat option
*
* \details		classe permettant de g�rer l'�tat option
*
*/


/*! \class		OptionState
* \brief		classe permettant de g�rer l'�tat option
*
* \details		classe permettant de g�rer l'�tat option
*
*/

class OptionState : public State
{
public:
	/**
	* \brief	Constructeur
	*
	*Constructeur de l'�tat option
	*
	* \param data : stock les donn�es communes associ�es � chaque �tat (fen�tre, �tat actuel)
	*/
	OptionState(GameDataRef data);

	/**
	* \brief	Initialise l'�tat option
	*
	*Initialise l'�tat option, avec toutes les ressources n�c�ssaires
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
	* \brief	mise a jour de la logique de l'�tat option
	*
	*mise a jour de la logique de l'�tat option
	*
	* \param dt : temps que met une it�ration
	*/
	void update(float dt);

	/**
	* \brief	affiche l'�tat option
	*
	*affiche l'�tat option
	*
	* \param dt : temps que met une it�ration
	*/
	void draw(float dt);

private:
	

	/**
	* \brief	Permet de passer de l'�tat option � l'�tat menu
	*
	*Permet de passer de l'�tat option � l'�tat menu
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
	void changeTextDesign(sf::Text& buttons);

private:
	GameDataRef _data;/*!< donn�es communes aux �tats (fen�tre, �tat actuel)*/

	RessourceHolder ressources;/*!<  Objet RessourceHolder, stock les textures et les fonts*/
	sf::Sprite optionBackground;/*!< Sprite du fond d'�cran*/

	sf::Text mButton;/*!< Bouttons affich�s lors de l'�tat option*/
	sf::Text mYesNo;/*!< Texte affichant oui ou non*/
	sf::Text mTitle;/*!< Titre de l'�tat*/
};


