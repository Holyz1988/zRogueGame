#pragma once
#include "SFML\Graphics.hpp"

/**
* \file			Entity.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		représentation d'une entité du jeu
*
* \details		représentation d'une entité du jeu
*
*/


/*! \class		Entity
* \brief		Classe qui représente une entité du jeu
*
* \details		Classe qui représente une entité du jeu, sa position, sa représentation ...
*
*/
class Entity
{
public:
	sf::Vector2f position;/*!< Position de l'entité*/
	sf::CircleShape circle;/*!< Forme de cercle de l'entité*/
	sf::RectangleShape rect;/*!< Forme réctangulaire de l'entité*/
	sf::Sprite sprite;/*!< représentation graphique de l'entité*/
	sf::Text text;/*!< Texte de l'entité*/
};

