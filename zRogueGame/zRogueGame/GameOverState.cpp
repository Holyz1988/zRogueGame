#include "OptionState.h"
#include "MenuState.h"
#include "GameOverState.h"
#include "PlayState.h"

GameOverState::GameOverState(GameDataRef data) : _data(data)
{

}

void GameOverState::init()
{
	optionScreen.loadTexture("gameOverBackground", "ressources/game_over_screen.png");
	optionBackground.setTexture(optionScreen.getTexture("gameOverBackground"));

	mCamera.reset(sf::FloatRect(0,0,800, 600));
	this->_data->window.setView(mCamera);
}

void GameOverState::handleInput()
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->_data->window.close();
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
			{
				this->_data->machine.addState(StateRef(new PlayState(this->_data)), true);
			}
			break;
		}
	}
}

void GameOverState::update(float dt)
{
}

void GameOverState::draw(float dt)
{
	this->_data->window.draw(optionBackground);
}

void GameOverState::loadMenu()
{
	//TODO : Arrache la mémoire, trouver une meilleur solution
	//this->_data->previousState();
}

bool GameOverState::isTextClicked(sf::Text text)
{
	return false;
}

void GameOverState::changeTextDesign(std::vector<sf::Text>& buttons)
{
}