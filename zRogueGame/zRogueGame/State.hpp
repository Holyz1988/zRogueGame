#pragma once

/**
* \file			State.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe abstraite
*
* \details		Classe abstraite qui permet de réaliser du polymorphisme et d'appeler les fonction d'affichage de l'état dans lequel on se trouve
*
*/


/*! \class		State
* \brief		Classe abstraite
*
* \details		Classe qui permet de gérer le chargement des textures et des polices de caractères
*
*/

class State
{
public:
	virtual void init() = 0;

	virtual void handleInput() = 0;
	virtual void update(float dt) = 0;
	virtual void draw(float dt) = 0;

	virtual void pause() {}
	virtual void resume() {}
};
