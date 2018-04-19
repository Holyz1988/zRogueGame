#pragma once
#include <memory>
#include <string>
#include "SFML\Graphics.hpp"
#include "StateMachine.h"

/**
* \file			Data.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		données du jeu
*
* \details		classe permettant de lancer le jeu, et de naviguer entre les différents états du jeu
*
*/

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
};

typedef std::shared_ptr<GameData> GameDataRef;

/*! \class		Game
* \brief		Classe qui représente le jeu
*
* \details		Classe qui représente le jeu, et qui permet de jouer au jeu
*
*/
class Game
{
public:

	/**
	* \brief		Constructeur
	*
	*Constructeur de la classe Game
	*
	* \param width : Largeur de la fenêtre
	* \param height : Hauteur de la fenêtre
	* \param title : Titre de la fenêtre
	*/
	Game(int width, int height, std::string title);

	/**
	* \brief		Permet de lancer le jeu, et d'afficher à l'écran l'état souhaité
	*
	*Permet de lancer le jeu, et d'afficher à l'écran l'état souhaité, à l'aide du polymorphisme
	*
	*/
	void run();

private:
	const float dt = 1 / 60.0f;/*!< Temps que met chaque itération*/
	sf::Clock _clock;/*!< Horloge du jeu*/

	GameDataRef _data = std::make_shared<GameData>();/*!< référence vers les données de notre jeu, en l'occurence la fenêtre et l'état dans lequel on se trouve*/
};


