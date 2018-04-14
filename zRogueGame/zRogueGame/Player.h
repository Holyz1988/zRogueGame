#pragma once
#include "Character.h"
#include "RessourceHolder.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Wall.h"

class Enemy;

class Player : public Character	
{
public:
	Player();

	void update(float dt, std::vector<Wall>& walls);
	void fireBullets(sf::RenderWindow& window, std::vector<Wall> walls);
	void drawBullets(sf::RenderWindow& window);
	void updateVectors(sf::RenderWindow& window);

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

	void fireBallBulletCollision(std::vector<Enemy>& enemies);
	void bulletWallCollision(std::vector<Wall>& walls);
	bool fireBallCollision(Enemy& enemy);
	bool collisionBulletWall(Wall& wall);
	void wallCollision(std::vector<Wall>& walls, sf::Vector2f previousPos);
	void bulletOrcCollision(std::vector<Enemy>& orcs);


	void losingHp(std::vector<Enemy>& enemy);

	bool mSpawnerStatus;
	int mCurrentExperience;
	int mExperienceNeeded;

private:
	//Vecteurs qui permettent de construire le tire du joueur
	sf::Vector2f mPlayerCenter;
	sf::Vector2f mMouseWorldPosition;
	sf::Vector2i mMousePixelPosition;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalized;


	Projectile bullet;
	std::vector<Projectile> bullets;

	// Horloge
	sf::Clock bulletClock;
	sf::Clock invulnerableClock;
	sf::Clock clock; 
	float mTimeAccumulator;
	const float mBulletDelay = 0.1f;

	float timePassed; // Temps écouler
	float switchTime = 0.3f; // Temps que prend une frame d'animation
	int currentFrame = 0; // On comment à la 1ère frame

	float invulnerableTimer;

	//Stats
	bool invulnerable;
	
};

