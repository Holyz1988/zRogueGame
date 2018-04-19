#include "Game.h"
#include "MenuState.h"
#include <iostream>



Game::Game(int width, int height, std::string title)
{
	this->_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

	this->_data->machine.addState(StateRef(new MenuState(this->_data)));

	this->run();
}

void Game::run()
{
	sf::Clock clock;

	float newTime, frameTime, interpolation;

	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen())
	{
		this->_data->machine.processStateChanges();
		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		//Controle des FPS
		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			//Récupérer les saisies utilisateurs pendant l'état acutel de notre jeu (menu, maingame, pause, etc)
			this->_data->machine.getActiveState()->handleInput();
			this->_data->machine.getActiveState()->update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;

		this->_data->window.clear(sf::Color::Black);

		this->_data->machine.getActiveState()->draw(interpolation);

		this->_data->window.display();
	}
}
