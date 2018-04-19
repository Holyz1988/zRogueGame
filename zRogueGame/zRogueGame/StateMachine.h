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
	StateMachine() {}
	~StateMachine() {}

	void addState(StateRef newState, bool isReplacing = true);
	void removeState();

	void processStateChanges();

	StateRef& getActiveState();

private:
	std::stack<StateRef> _states;/*!< */
	StateRef _newState;/*!< */

	bool _isRemoving;/*!< */
	bool _isAdding;/*!< */
	bool _isReplacing;/*!< */

};

