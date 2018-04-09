#include "OptionState.h"
#include "MenuState.h"



OptionState::OptionState(GameDataRef data) : _data(data)
{

}

void OptionState::init()
{
	optionScreen.loadTexture("optionBackground", "ressources/Space_Background.png");
	optionBackground.setTexture(optionScreen.getTexture("optionBackground"));
}

void OptionState::handleInput()
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

void OptionState::update(float dt)
{
}

void OptionState::draw(float dt)
{
	this->_data->window.draw(optionBackground);
}

void OptionState::loadMenu()
{
	//TODO : Arrache la mémoire, trouver une meilleur solution
	//this->_data->previousState();
}

bool OptionState::isTextClicked(sf::Text text)
{
	return false;
}

void OptionState::changeTextDesign(std::vector<sf::Text>& buttons)
{
}
