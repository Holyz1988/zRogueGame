#include "Game.h"
#include "MenuState.h"



Game::Game(int width, int height, std::string title)
{
	this->_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

	this->_data->machine.addState(StateRef(new MenuState(this->_data)));

	this->run();
}

void Game::run()
{
	sf::Clock clock;

	while (this->_data->window.isOpen())
	{
		this->_data->machine.processStateChanges();
		//Controle des FPS
		float dt = clock.restart().asSeconds();

		//Récupérer les saisies utilisateurs pendant l'état acutel de notre jeu (menu, maingame, pause, etc)
		this->_data->machine.getActiveState()->handleInput();
		this->_data->machine.getActiveState()->update(dt);

		this->_data->window.clear(sf::Color::Black);

		this->_data->machine.getActiveState()->draw(dt);

		this->_data->window.display();
	}
}
