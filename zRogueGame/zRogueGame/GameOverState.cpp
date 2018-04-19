#include "OptionState.h"
#include "MenuState.h"
#include "GameOverState.h"
#include "PlayState.h"

GameOverState::GameOverState(GameDataRef data) : _data(data)
{

}

void GameOverState::init()
{
	ressources.loadTexture("gameOverBackground", "ressources/game_over_screen.png");
	gameOverBackground.setTexture(ressources.getTexture("gameOverBackground"));

	sf::Text text;
	ressources.loadFont("menuFont", "ressources/gomarice_game_continue_02.ttf");
	text.setFont(ressources.getFont("menuFont"));
	text.setCharacterSize(40);
	text.setStyle(sf::Text::Bold);

	mButtons.push_back(text);
	mButtons.push_back(text);

	mButtons[0].setString("Retourner au menu");
	mButtons[1].setString("Quitter");

	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		sf::FloatRect buttonRect = mButtons[i].getLocalBounds();
		mButtons[i].setOrigin(buttonRect.left + buttonRect.width / 2.0f,
			buttonRect.top + buttonRect.height / 2.0f);
		mButtons[i].setPosition(sf::Vector2f(this->_data->window.getSize().x / 2.0f, 400 + (i * 65.f)));
	}

	mCamera.reset(sf::FloatRect(0,0,800, 600));
	this->_data->window.setView(mCamera);

	//Music et sons
	if (!bgMusic.openFromFile("nice_music.ogg"))
	{
		throw std::runtime_error("Failed to load nice_music.ogg");
	}
	bgMusic.setLoop(true);
	bgMusic.play();
	bgMusic.setVolume(20);
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
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->_data->window.close();
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
					bgMusic.stop();
					loadMenu();
				}
				else if (isTextClicked(mButtons[1]))
				{
					bgMusic.stop();
					this->_data->window.close();
				}
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
	this->_data->window.draw(gameOverBackground);
	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		this->_data->window.draw(mButtons[i]);
	}
}

void GameOverState::loadMenu()
{
	this->_data->machine.addState(StateRef(new MenuState(this->_data)), true);
}

bool GameOverState::isTextClicked(sf::Text text)
{
	sf::FloatRect rect = text.getGlobalBounds();

	//Si la souris se trouve sur le rectangle
	if (rect.contains((float)sf::Mouse::getPosition(this->_data->window).x, (float)sf::Mouse::getPosition(this->_data->window).y))
		return true;
	else
		return false;
}

void GameOverState::changeTextDesign(std::vector<sf::Text>& buttons)
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