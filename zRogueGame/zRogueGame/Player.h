#pragma once
#include "Entity.h"
#include "RessourceHolder.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Wall.h"

class Enemy;

class Player : public Entity
{
public:
	Player();

	void update(float dt);
	void fireBullets(sf::RenderWindow& window, std::vector<Wall> walls);
	void drawBullets(sf::RenderWindow& window);
	void updateVectors(sf::RenderWindow& window);
	void bulletCollision(std::vector<Enemy>& enemies);

	void wallCollision(std::vector<Wall>& walls);

	void resetInvulnerableTimer();

	//actionne le spawn des mobs
	void spawnOrcs(Wall& spawnTile);

	//Accesseurs
	int getDamage();
	int getCurrentHP();
	std::vector<Projectile> getBullets();
	bool getSpawnerStatus();

	//Setters
	void setDamage(int damage);

	bool colisionPlayerFireball(Enemy& enemy);
	bool collisionBulletWall(Wall& wall);
	void losingHp(Enemy& enemy);
	

private:
	//Vecteurs qui permettent de construire le tire du joueur
	sf::Vector2f playerCenter;
	sf::Vector2f mouseWorldPosition;
	sf::Vector2i mousePixelPosition;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalized;

	Projectile bullet;// Projectile
	std::vector<Projectile> bullets;// Conteneurs de projectiles

	sf::Clock bulletClock;
	sf::Clock invulnerableClock;
	float timeAccumulator;
	const float bulletDelay = 0.1f;

	sf::Clock clock; // Horloge

	//
	float timePassed; // Temps écouler
	float switchTime = 0.3f; // Temps que prend une frame d'animation

	int currentFrame = 0; // On comment à la 1ère frame

	float invulnerableTimer;

	//Stats
	int attackDamage = 5;
	int currentHp;
	int maxHP = 100;
	float mSpeed = 150.f;
	bool invulnerable;

	//Spawn
	bool mSpawnerStatus;
};

