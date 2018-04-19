#pragma once
#include "Entity.h"

/**
* \file			Items.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Potion
*
* \details		Potion
*
*/

/*! \class		Items
* \brief		Classe qui représente un objet dans le jeu
*
* \details		Classe qui représente un objet dans le jeu
*
*/
class Items : public Entity
{
public:
	int quantity;/*!< Quantité de l'objet dans le jeu*/
};

