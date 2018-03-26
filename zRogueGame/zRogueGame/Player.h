#pragma once
#include "Entity.h"
#include "RessourceHolder.h"
#include "Projectile.h"

class Player : public Entity
{
public:
	Player();

	void update(float dt);
	void fireBullets(sf::RenderWindow& window);
	void drawBullets(sf::RenderWindow& window);
	void updateVectors(sf::RenderWindow& window);

	//Getters et Setters
	int getDamage();
	void setDamage(int damage);

private:
	//Information sur le joueur et les balles
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosition;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalized;

	Projectile bullet;// Projectile
	std::vector<Projectile> bullets;// Conteneurs de projectiles

	sf::Clock bulletClock;
	float timeAccumulator;
	const float bulletDelay = 0.2f;

	RessourceHolder ressource;
	sf::Clock clock; // Horloge

	float timePassed; // Temps écouler
	int currentFrame = 0; // On comment à la 1ère frame
	float movementSpeed = 150.f; //100 pixels / secondes
	float switchTime = 0.3f; // Temps que prend une frame d'animation

	int attackDamage = 10;
	int maxHP = 100;
};

