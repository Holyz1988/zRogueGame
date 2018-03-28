#include "Wall.h"


Wall::Wall()
{
	rect.setSize(sf::Vector2f(32.f, 32.f));
	rect.setPosition(sf::Vector2f(0.f, 0.f));
	rect.setFillColor(sf::Color::Black);
}

