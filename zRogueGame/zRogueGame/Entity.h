#pragma once
#include "SFML\Graphics.hpp"

class Entity
{
public:
	sf::Vector2f position;
	sf::CircleShape circle;
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Text text;
};

