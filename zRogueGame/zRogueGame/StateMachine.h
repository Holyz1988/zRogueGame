#pragma once

#include <memory>
#include <stack>
#include "State.hpp"

/**
* \file			RessourceHolder.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe gère le changement d'état
*
* \details		Classe gère le changement d'état
*/


/*! \class		RessourceHolder
* \brief		Classe gère le changement d'état
*
* \details		Classe gère le changement d'état
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
	* \brief		Ajoute un état au conteur d'état du jeu
	*
	*Ajoute un état au conteur d'état du jeu
	*
	* \param newState : nouvelle état à ajouter
	* \param isReplacing : remplace l'ancienne état ou non ?
	*/
	void addState(StateRef newState, bool isReplacing = true);

	/**
	* \brief		Détruit l'état actuel
	*
	*Détruit l'état actuel
	*
	*/
	void removeState();

	/**
	* \brief		S'occupe du changement d'état entre chaque itération
	*
	*S'occupe du changement d'état entre chaque itération
	*
	*/
	void processStateChanges();

	/**
	* \brief		S'occupe du changement d'état entre chaque itération
	*
	*S'occupe du changement d'état entre chaque itération
	*
	* \return référence vers un pointeur unique qui pointe sur l'état en question
	*/
	StateRef& getActiveState();

private:
	std::stack<StateRef> _states;/*!< conteur d'état, wrapper à l'aide d'un pointeur unique*/
	StateRef _newState;/*!< nouvelle état, wrapper à l'aide d'un pointeur unique*/

	bool _isRemoving;/*!< représente le faite que l'on enlève l'état actuelle ou non*/
	bool _isAdding;/*!< représente le faite que l'on ajoute un état à l'état actuelle ou non*/
	bool _isReplacing;/*!< le nouvelle état doit-il remplacer ou non l'ancienne état ?*/
};

