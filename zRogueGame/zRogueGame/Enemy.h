#pragma once
#include "Entity.h"
#include "RessourceHolder.h"
#include "Player.h"

class Player;

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(sf::Vector2f velocity);

	void updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow& window);
	void spawnEnemies(std::vector<Enemy>& enemies, Enemy& enemy, Player& player);
	void drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow& window);

	void updatePos();
	void updateV(Player& player);

	void moveEnemies(float dt);

	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity();

private:
	sf::Clock clock;
	sf::Clock clockOrc;
	sf::Vector2f mVelocity;
	float mSpeed; //200 pixels / secondes

	sf::Vector2f playerCenter;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalized;

	float timePassed; // Temps écouler
	int currentFrame; // On comment à la 1ère frame
	float switchTime; // Temps que prend une frame d'animation

	float timeWalking;
	int mSpawnCounter;

	int attackDamage;
	int maxHP;
};

