#pragma once
#include "Entity.h"
#include "RessourceHolder.h"

class Player : public Entity
{
public:
	Player();

	void update(float dt);
private:
	RessourceHolder ressource;
	sf::Clock clock; // Horloge
	float timePassed; // Temps �couler
	int currentFrame = 0; // On comment � la 1�re frame
	float movementSpeed = 200.f; //100 px / secondes
	float switchTime = 0.3f; // Temps que prend une frame d'animation

};

