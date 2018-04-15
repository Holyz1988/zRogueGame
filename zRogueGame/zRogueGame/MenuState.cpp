#include "MenuState.h"
#include "PlayState.h"
#include "OptionState.h"
#include "NewGameState.h"
#include <iostream>

MenuState::MenuState(GameDataRef data) : _data(data)
{

}

void MenuState::init()
{
	//On charge l'image de fond
	ressources.loadTexture("menuButton", "ressources/menu_background.png");
	menuSprite.setTexture(ressources.getTexture("menuButton"));

	//On charge la police du menu
	sf::Text text;
	ressources.loadFont("menuFont", "ressources/gomarice_game_continue_02.ttf");
	text.setFont(ressources.getFont("menuFont"));
	text.setCharacterSize(40);
	text.setStyle(sf::Text::Bold);

	//On met en place le titre
	mTitle.setFont(ressources.getFont("menuFont"));
	mTitle.setCharacterSize(70);
	mTitle.setStyle(sf::Text::Underlined);
	mTitle.setStyle(sf::Text::Bold);
	mTitle.setFillColor(sf::Color::Red);
	mTitle.setString("Z Painfull Game");

	//On place le titre
	sf::FloatRect titleRect = mTitle.getLocalBounds();
	mTitle.setOrigin(titleRect.left + titleRect.width / 2.0f,
					 titleRect.top + titleRect.height / 2.0f);
	mTitle.setPosition(sf::Vector2f(this->_data->window.getSize().x / 2.0f, 100));

	//on remplit notre vecteur de bouttons
	mButtons.push_back(text);
	mButtons.push_back(text);
	mButtons.push_back(text);
	mButtons.push_back(text);

	//On donne un texte à chaque boutton
	mButtons[0].setString("Nouvelle partie");
	mButtons[1].setString("Charger une partie");
	mButtons[2].setString("Options");
	mButtons[3].setString("Quitter");

	//On place les bouttons
	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		sf::FloatRect buttonRect = mButtons[i].getLocalBounds();
		mButtons[i].setOrigin(buttonRect.left + buttonRect.width / 2.0f,
							  titleRect.top + titleRect.height / 2.0f);
		mButtons[i].setPosition(sf::Vector2f(this->_data->window.getSize().x / 2.0f, 300.f + (i * 65.f)));
	}
}



void MenuState::handleInput()
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->_data->window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->_data->window.close();
			else if (event.key.code == sf::Keyboard::Return)
				loadGame();
			break;
			//Si on passe la souris sur l'un des textes du menu, changement de style.
		case sf::Event::MouseMoved:
			changeTextDesign(mButtons);
			break;
			//Gestion de la navigation du menu
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (isTextClicked(mButtons[0]))
				{
					loadGame();
				}
				else if (isTextClicked(mButtons[1]))
				{
					loadSaves();
				}
				else if (isTextClicked(mButtons[2]))
				{
					loadOptions();
				}
				else if (isTextClicked(mButtons[3]))
				{
					this->_data->window.close();
				}
			}
		}
	}
}

void MenuState::update(float dt)
{
	//changeTextColor(buttons);
}

void MenuState::draw(float dt)
{
	this->_data->window.draw(menuSprite);
	this->_data->window.draw(mTitle);

	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		this->_data->window.draw(mButtons[i]);
	}
}

void MenuState::loadGame()
{
	//Chargement de l'état menu
	this->_data->machine.addState(StateRef(new PlayState(this->_data)), true);
}

void MenuState::loadOptions()
{
	this->_data->machine.addState(StateRef(new OptionState(this->_data)), false);
}

void MenuState::loadSaves()
{
	this->_data->machine.addState(StateRef(new NewGameState(this->_data)), false);
}

bool MenuState::isTextClicked(sf::Text& text)
{
	sf::FloatRect rect = text.getGlobalBounds();

	//Si la souris se trouve sur le rectangle
	if (rect.contains((float)sf::Mouse::getPosition(this->_data->window).x, (float)sf::Mouse::getPosition(this->_data->window).y))
		return true;
	else
		return false;
}


//Change la couleur du text qui est survolé par la souris
void MenuState::changeTextDesign(std::vector<sf::Text>& buttons)
{
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		if (isTextClicked(buttons[i]))
		{
			buttons[i].setFillColor(sf::Color::Red);
			buttons[i].setOutlineThickness(6.f);
		}
		else
		{
			buttons[i].setFillColor(sf::Color::White);
			buttons[i].setOutlineThickness(0.f);
		}
	}
}
//TODO CONTINUER LE MENU

