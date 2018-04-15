#include "Projectile.h"
#include <math.h>


Projectile::Projectile() : Velocity(0.f, 0.f),
						   mSpeed(10.f)
{
	this->circle.setRadius(4.f);
	this->circle.setFillColor(sf::Color::Color(255, 116, 14));
	this->circle.setOutlineColor(sf::Color::Red);
	this->circle.setOutlineThickness(1.8f);
}

sf::Vector2f Projectile::getVelocity()
{
	return this->Velocity;
}

void Projectile::setVelocity(sf::Vector2f velocity)
{
	this->Velocity = velocity;
}

float Projectile::getSpeed()
{
	return this->mSpeed;
}

void Projectile::setSpeed(float speed)
{
	this->mSpeed = speed;
}
