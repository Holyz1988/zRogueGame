#pragma once

#include <memory>
#include <stack>
#include "State.hpp"

/**
* \file			RessourceHolder.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe g�re le changement d'�tat
*
* \details		Classe g�re le changement d'�tat
*/


/*! \class		RessourceHolder
* \brief		Classe g�re le changement d'�tat
*
* \details		Classe g�re le changement d'�tat
*
*/

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
	/**
	* \brief		Constructeur
	*
	*Constructeur
	*
	*/
	StateMachine() {}

	/**
	* \brief		Destructeur
	*
	*Destructeur
	*
	*/
	~StateMachine() {}

	/**
	* \brief		Ajoute un �tat au conteur d'�tat du jeu
	*
	*Ajoute un �tat au conteur d'�tat du jeu
	*
	* \param newState : nouvelle �tat � ajouter
	* \param isReplacing : remplace l'ancienne �tat ou non ?
	*/
	void addState(StateRef newState, bool isReplacing = true);

	/**
	* \brief		D�truit l'�tat actuel
	*
	*D�truit l'�tat actuel
	*
	*/
	void removeState();

	/**
	* \brief		S'occupe du changement d'�tat entre chaque it�ration
	*
	*S'occupe du changement d'�tat entre chaque it�ration
	*
	*/
	void processStateChanges();

	/**
	* \brief		S'occupe du changement d'�tat entre chaque it�ration
	*
	*S'occupe du changement d'�tat entre chaque it�ration
	*
	* \return r�f�rence vers un pointeur unique qui pointe sur l'�tat en question
	*/
	StateRef& getActiveState();

private:
	std::stack<StateRef> _states;/*!< conteur d'�tat, wrapper � l'aide d'un pointeur unique*/
	StateRef _newState;/*!< nouvelle �tat, wrapper � l'aide d'un pointeur unique*/

	bool _isRemoving;/*!< repr�sente le faite que l'on enl�ve l'�tat actuelle ou non*/
	bool _isAdding;/*!< repr�sente le faite que l'on ajoute un �tat � l'�tat actuelle ou non*/
	bool _isReplacing;/*!< le nouvelle �tat doit-il remplacer ou non l'ancienne �tat ?*/
};

