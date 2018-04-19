#pragma once
#include "Entity.h"
#include "RessourceHolder.h"

/**
* \file			Projectile.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe qui possède toute les caractérique et la logique d'un projectile
*
* \details		Classe qui possède toute les caractérique et la logique d'un projectile
*
*/


/*! \class		Projectile
* \brief		Classe qui possède toute les caractérique et la logique d'un projectile
*
* \details		Classe qui possède toute les caractérique et la logique d'un projectile
*
*/

class Projectile : public Entity
{
public:
	Projectile();

	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f velocity);

	float getSpeed();
	void setSpeed(float speed);
	
private:
	float radius;/*!< */
	sf::Vector2f Velocity;/*!< */
	float mSpeed;/*!< */ //bullet speed
};

