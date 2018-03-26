#pragma once
#include "Entity.h"
#include "RessourceHolder.h"

class Projectile : public Entity
{
public:
	Projectile();

	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f velocity);

	float getSpeed();
	void setSpeed(float speed);
	
private:
	float radius;
	sf::Vector2f Velocity;
	float mSpeed; //200 pixels / secondes

	int attackDamage = 10;
};

