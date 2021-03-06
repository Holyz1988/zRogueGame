#pragma once
#include "Entity.h"
#include "RessourceHolder.h"

/**
* \file			Projectile.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe qui poss�de toute les caract�rique et la logique d'un projectile
*
* \details		Classe qui poss�de toute les caract�rique et la logique d'un projectile
*
*/


/*! \class		Projectile
* \brief		Classe qui poss�de toute les caract�rique et la logique d'un projectile
*
* \details		Classe qui poss�de toute les caract�rique et la logique d'un projectile
*
*/

class Projectile : public Entity
{
public:
	/**
	* \brief	Construteur
	*
	*Construteur
	*
	*/
	Projectile();

	//ACCESORS

	/**
	* \brief	GETTER
	*
	*GETTER
	*
	* \return Vecteur vitesse du projectile
	*/
	sf::Vector2f getVelocity();

	/**
	* \brief	SETTER
	*
	*SETTER
	*
	* \param velocity nouveau vecteur vitesse � appliquer au projectile
	*/
	void setVelocity(sf::Vector2f velocity);

	/**
	* \brief	GETTER
	*
	*GETTER
	*
	* \return Un float repr�sentant la vitesse du projectile 
	*/
	float getSpeed();

	/**
	* \brief	SETTER
	*
	*SETTER
	*
	* \param speed : nouvelle vitesse projectile
	*/
	void setSpeed(float speed);
	
private:
	float radius;/*!< rayon projectile*/
	sf::Vector2f Velocity;/*!< vecteur vitesse projectile*/
	float mSpeed;/*!< vitesse projectile*/
};

