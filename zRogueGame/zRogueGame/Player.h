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

	void fireBallBulletCollision(std::vector<Enemy>& enemies);
	void bulletWallCollision(std::vector<Wall>& walls);
	bool fireBallCollision(Enemy& enemy);
	bool collisionBulletWall(Wall& wall);
	void wallCollision(std::vector<Wall>& walls, sf::Vector2f previousPos);
	void bulletOrcCollision(std::vector<Enemy>& orcs);
	void losingHp(std::vector<Enemy>& enemy);


	void levelUp();
	bool isDead();

	//Accesseurs
	int getDamage();
	int getCurrentHP();
	std::vector<Projectile> getBullets();
	bool getSpawnerStatus();
	float getBulletDelay();
	Projectile getBullet();

	//Setters
	void setDamage(int damage);
	void setBulletDelay(float bulletDelaly);
	void setBulletRadius(float bulletRadius);

	bool mSpawnerStatus;
	int mCurrentExperience;
	int mExperienceNeeded;
	int idPlayer;

private:
	//Vecteurs qui permettent de construire le tire du joueur
	sf::Vector2f mPlayerCenter;
	sf::Vector2f mMouseWorldPosition;
	sf::Vector2i mMousePixelPosition;
	sf::Vector2f mAimDirection;
	sf::Vector2f mAimDirectionNormalized;

	Projectile mBullet;
	std::vector<Projectile> mBullets;

	// Horloge
	sf::Clock mBulletClock;
	sf::Clock invulnerableClock;
	sf::Clock clock; 
	float mTimeAccumulator;
	float mBulletDelay;

	float timePassed; // Temps écouler
	float switchTime = 0.3f; // Temps que prend une frame d'animation
	int currentFrame = 0; // On comment à la 1ère frame

	float invulnerableTimer;

	//Stats
	bool invulnerable;
};

