#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>

class GameState;

class Game
{
public:
	Game();
	~Game();

	//Fonction pour changer l'état du jeu
	void pushState(GameState* state);
	void popState();

	void previousState();

	//Méthode qui permet de récupérer notre état actuel (pointeur obligatoire)
	GameState* currentState();

	//La boucle de jeu
	void gameLoop();

	sf::RenderWindow window;

private:
	std::vector<GameState*> states;
};

