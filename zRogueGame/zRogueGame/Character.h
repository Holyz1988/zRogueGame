#pragma once
#include "Entity.h"
/**
* \file			Character.h
* \author		Amine ZEGHAD	
* \version		1.0
* \date			19 april 2018
* \brief		Défini les statistiques des personnages
*
* \details		Défini les statistiques des personnages joueurs et non joueurs
*
*/

/*! \class Character
* \brief		Défini les statistiques des personnages
*
* \details		Défini les statistiques des personnages jouables et non jouables
*
*/
class Character : public Entity
{
public:
	//Stats
	int currency; /*!< Argent que possède le personnage*/
	int attackDamage; /*!< Dégats du personnage*/
	int currentHp; /*!< Points de vies acutel du personnage*/
	int maxHP; /*!< Points de vies maximum du personnage*/
	int level; /*!< Niveau du personnage*/
	float mSpeed; /*!< Vitesse du personnage*/
};

