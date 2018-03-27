#include "OptionState.h"
#include "MenuState.h"



OptionState::OptionState(Game* game)
{
	optionScreen.loadTexture("optionBackground", "ressources/Space_Background.png");
	optionBackground.setTexture(optionScreen.getTexture("optionBackground"));
	this->game = game;
}


void OptionState::handleInput()
{
	sf::Event event;
	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			game->window.close();
			break;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			loadMenu();
	}
}

void OptionState::update(float dt)
{
}

void OptionState::draw(float dt)
{
	game->window.draw(optionBackground);
}

void OptionState::loadMenu()
{
	//TODO : Arrache la mémoire, trouver une meilleur solution
	game->previousState();
}

bool OptionState::isTextClicked(sf::Text text)
{
	return false;
}

void OptionState::changeTextDesign(std::vector<sf::Text>& buttons)
{
}
