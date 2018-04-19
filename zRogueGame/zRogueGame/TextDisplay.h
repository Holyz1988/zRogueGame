#pragma once
#include "Entity.h"

/**
* \file			TextDisplay.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe les différents affichage de texte sur la fenêtre
*
* \details		Classe les différents affichage de texte sur la fenêtre
*/


/*! \class		TextDisplay
* \brief		Classe les différents affichage de texte sur la fenêtre
*
* \details		Classe les différents affichage de texte sur la fenêtre
*
*/

class TextDisplay : public Entity
{
public:
	TextDisplay();
	void update();

	std::string myString = "default";/*!< */
};

