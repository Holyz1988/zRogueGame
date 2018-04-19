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
* \brief		donn�es du jeu
*
* \details		classe permettant de lancer le jeu, et de naviguer entre les diff�rents �tats du jeu
*
*/

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
};

typedef std::shared_ptr<GameData> GameDataRef;

/*! \class		Game
* \brief		Classe qui repr�sente le jeu
*
* \details		Classe qui repr�sente le jeu, et qui permet de jouer au jeu
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
	* \param width : Largeur de la fen�tre
	* \param height : Hauteur de la fen�tre
	* \param title : Titre de la fen�tre
	*/
	Game(int width, int height, std::string title);

	/**
	* \brief		Permet de lancer le jeu, et d'afficher � l'�cran l'�tat souhait�
	*
	*Permet de lancer le jeu, et d'afficher � l'�cran l'�tat souhait�, � l'aide du polymorphisme
	*
	*/
	void run();

private:
	const float dt = 1 / 60.0f;/*!< Temps que met chaque it�ration*/
	sf::Clock _clock;/*!< Horloge du jeu*/

	GameDataRef _data = std::make_shared<GameData>();/*!< r�f�rence vers les donn�es de notre jeu, en l'occurence la fen�tre et l'�tat dans lequel on se trouve*/
};


