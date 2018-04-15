#include "OptionState.h"
#include "MenuState.h"
#include "NewGameState.h"



NewGameState::NewGameState(GameDataRef data) : _data(data)
{

}

void NewGameState::init()
{
	optionScreen.loadTexture("optionBackground", "ressources/Space_Background.png");
	optionBackground.setTexture(optionScreen.getTexture("optionBackground"));
}

void NewGameState::handleInput()
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->_data->window.close();
			break;
		}

		if (event.key.code == sf::Keyboard::Escape)
			this->_data->machine.removeState();
	}
}

void NewGameState::update(float dt)
{
}

void NewGameState::draw(float dt)
{
	this->_data->window.draw(optionBackground);
}

void NewGameState::loadMenu()
{
	//TODO : Arrache la mémoire, trouver une meilleur solution
	//this->_data->previousState();
}

bool NewGameState::isTextClicked(sf::Text text)
{
	return false;
}

void NewGameState::changeTextDesign(std::vector<sf::Text>& buttons)
{
}