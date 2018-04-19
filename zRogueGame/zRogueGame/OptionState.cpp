#include "OptionState.h"
#include "MenuState.h"



OptionState::OptionState(GameDataRef data) : _data(data)
{

}

void OptionState::init()
{
	//On charge l'image de fond
	ressources.loadTexture("optionBackground", "ressources/Space_Background.png");
	optionBackground.setTexture(ressources.getTexture("optionBackground"));

	//On charge la police du menu
	ressources.loadFont("menuFont", "ressources/gomarice_game_continue_02.ttf");
	mButton.setFont(ressources.getFont("menuFont"));
	mButton.setCharacterSize(40);
	mButton.setStyle(sf::Text::Bold);

	//On charge la police du menu
	ressources.loadFont("menuFont", "ressources/gomarice_game_continue_02.ttf");
	mYesNo.setFont(ressources.getFont("menuFont"));
	mYesNo.setCharacterSize(40);
	mYesNo.setStyle(sf::Text::Bold);

	//On met en place le titre
	mTitle.setFont(ressources.getFont("menuFont"));
	mTitle.setCharacterSize(70);
	mTitle.setStyle(sf::Text::Underlined);
	mTitle.setStyle(sf::Text::Bold);
	mTitle.setFillColor(sf::Color::Red);
	mTitle.setString("Options");

	//On place le titre
	sf::FloatRect titleRect = mTitle.getLocalBounds();
	mTitle.setOrigin(titleRect.left + titleRect.width / 2.0f,
		titleRect.top + titleRect.height / 2.0f);
	mTitle.setPosition(sf::Vector2f(this->_data->window.getSize().x / 2.0f, 100));
	
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
	this->_data->window.draw(mTitle);
	this->_data->window.draw(mButton);
	this->_data->window.draw(mYesNo);
}

void OptionState::loadMenu()
{
	//TODO : Arrache la mémoire, trouver une meilleur solution
	//this->_data->previousState();
}

bool OptionState::isTextClicked(sf::Text text)
{
	sf::FloatRect rect = text.getGlobalBounds();

	//Si la souris se trouve sur le rectangle
	if (rect.contains((float)sf::Mouse::getPosition(this->_data->window).x, (float)sf::Mouse::getPosition(this->_data->window).y))
		return true;
	else
		return false;
}

void OptionState::changeTextDesign(sf::Text& button)
{
	if (isTextClicked(button))
	{
		button.setFillColor(sf::Color::Red);
		button.setOutlineThickness(6.f);
	}
	else
	{
		button.setFillColor(sf::Color::White);
		button.setOutlineThickness(0.f);
	}
}
