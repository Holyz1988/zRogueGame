#pragma once
#include "Entity.h"

/**
* \file			TextDisplay.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe les diff�rents affichage de texte sur la fen�tre
*
* \details		Classe les diff�rents affichage de texte sur la fen�tre
*/


/*! \class		TextDisplay
* \brief		Classe les diff�rents affichage de texte sur la fen�tre
*
* \details		Classe les diff�rents affichage de texte sur la fen�tre
*
*/

class TextDisplay : public Entity
{
public:
	TextDisplay();
	void update();

	std::string myString = "default";/*!< */
};

