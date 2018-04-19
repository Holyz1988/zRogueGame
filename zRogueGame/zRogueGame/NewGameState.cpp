#include "OptionState.h"
#include "MenuState.h"
#include "NewGameState.h"
#include "PlayState.h"
#include <string.h>
#include <iostream>

using namespace std;

NewGameState::NewGameState(GameDataRef data) : _data(data)
{

}

void NewGameState::init()
{
	ressources.loadTexture("newGameBackground", "ressources/menu_background.png");
	newGameBackground.setTexture(ressources.getTexture("newGameBackground"));

	db = new Database();
	db->openDatabase();

	players = db->getAllPlayer();

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
	mTitle.setString("Parties sauvegardees");

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
	mButtons[0].setString("ID : " + std::to_string(players[0].idPlayer) + "   Level : " + std::to_string(players[0].level));
	mButtons[1].setString("ID : " + std::to_string(players[1].idPlayer) + "   Level : " + std::to_string(players[1].level));
	mButtons[2].setString("ID : " + std::to_string(players[2].idPlayer) + "   Level : " + std::to_string(players[2].level));

	//On place les bouttons
	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		sf::FloatRect buttonRect = mButtons[i].getLocalBounds();
		mButtons[i].setOrigin(buttonRect.left + buttonRect.width / 2.0f,
			titleRect.top + titleRect.height / 2.0f);
		mButtons[i].setPosition(sf::Vector2f(this->_data->window.getSize().x / 2.0f, 300.f + (i * 65.f)));
	}
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
		case sf::Event::MouseMoved:
			changeTextDesign(mButtons);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (isTextClicked(mButtons[0]))
				{
					players[0].currentHp = players[0].maxHP;
					this->_data->machine.addState(StateRef(new PlayState(this->_data, players[0])), true);
				}
				else if (isTextClicked(mButtons[1]))
				{
					players[1].currentHp = players[1].maxHP;
					this->_data->machine.addState(StateRef(new PlayState(this->_data, players[1])), true);
				}
				else if (isTextClicked(mButtons[2]))
				{
					players[1].currentHp = players[1].maxHP;
					this->_data->machine.addState(StateRef(new PlayState(this->_data, players[2])), true);
				}
			}
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
	this->_data->window.draw(newGameBackground);
	this->_data->window.draw(mTitle);
	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		this->_data->window.draw(mButtons[i]);
	}
}

void NewGameState::loadMenu()
{
	//TODO : Arrache la mémoire, trouver une meilleur solution
	//this->_data->previousState();
}

bool NewGameState::isTextClicked(sf::Text text)
{
	sf::FloatRect rect = text.getGlobalBounds();

	//Si la souris se trouve sur le rectangle
	if (rect.contains((float)sf::Mouse::getPosition(this->_data->window).x, (float)sf::Mouse::getPosition(this->_data->window).y))
		return true;
	else
		return false;
}

void NewGameState::changeTextDesign(std::vector<sf::Text>& buttons)
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