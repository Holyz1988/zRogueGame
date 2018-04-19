#pragma once
#include "SFML\Graphics.hpp"

/**
* \file			Entity.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		repr�sentation d'une entit� du jeu
*
* \details		repr�sentation d'une entit� du jeu
*
*/


/*! \class		Entity
* \brief		Classe qui repr�sente une entit� du jeu
*
* \details		Classe qui repr�sente une entit� du jeu, sa position, sa repr�sentation ...
*
*/
class Entity
{
public:
	sf::Vector2f position;/*!< Position de l'entit�*/
	sf::CircleShape circle;/*!< Forme de cercle de l'entit�*/
	sf::RectangleShape rect;/*!< Forme r�ctangulaire de l'entit�*/
	sf::Sprite sprite;/*!< repr�sentation graphique de l'entit�*/
	sf::Text text;/*!< Texte de l'entit�*/
};

