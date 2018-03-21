#include "MenuState.h"
#include "PlayState.h"

#include <iostream>


MenuState::MenuState(Game* game)
{
	//On charge l'image de fond
	menuScreen.loadTexture("menuButton", "menu_background.png");
	menuSprite.setTexture(menuScreen.getTexture("menuButton"));

	//On charge la police du menu
	sf::Text text;
	menuScreen.loadFont("menuFont", "gomarice_game_continue_02.ttf");
	text.setFont(menuScreen.getFont("menuFont"));
	text.setCharacterSize(40);
	text.setStyle(sf::Text::Bold);

	//On place les bouttons
	for (unsigned i = 0; i < 3; i++)
	{
		buttons.push_back(text);
		buttons[i].setPosition(game->window.getSize().x / 2.f, text.getPosition().y + (i * 60.f) + 200.f);
	}

	buttons[0].setString("Play game");
	buttons[1].setString("Options");
	buttons[2].setString("Quit");

	this->game = game;
}

void MenuState::handleInput()
{
	sf::Event event;
	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			game->window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				game->window.close();
			else if (event.key.code == sf::Keyboard::Return)
				loadGame();
			break;
		case sf::Event::MouseMoved:
			changeTextDesign(buttons);
			break;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (isTextClicked(buttons[0]))
			loadGame();
		else if (isTextClicked(buttons[1]))
			std::cout << "Go to option Screen" << std::endl;
		else if (isTextClicked(buttons[2]))
			game->window.close();
	}

}

void MenuState::update(sf::Time dt)
{
	//changeTextColor(buttons);
}

void MenuState::draw(sf::Time dt)
{
	game->window.draw(menuSprite);

	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		game->window.draw(buttons[i]);
	}
}

void MenuState::loadGame()
{
	//Chargement de l'état menu
	game->pushState(new PlayState(game));
}

bool MenuState::isTextClicked(sf::Text text)
{
	sf::FloatRect rect(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height);

	//Si la souris se trouve sur le rectangle
	if (rect.contains(sf::Mouse::getPosition(game->window).x, sf::Mouse::getPosition(game->window).y))
		return true;
	else
		return false;
}


//Change la couleur du text qui est survolé par la souris
void MenuState::changeTextDesign(std::vector<sf::Text>& buttons)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (isTextClicked(buttons[i]))
		{
			buttons[i].setFillColor(sf::Color::Red);
			buttons[i].setCharacterSize(50);
			buttons[i].setOutlineThickness(6.f);
		}
		else
		{
			buttons[i].setFillColor(sf::Color::White);
			buttons[i].setCharacterSize(40);
			buttons[i].setOutlineThickness(0.f);
		}
	}
}
//TODO CONTINUER LE MENU

