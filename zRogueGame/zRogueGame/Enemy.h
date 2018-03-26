#pragma once
#include "Entity.h"
#include "RessourceHolder.h"
#include "Player.h"

class Player;

class Enemy : public Entity
{
public:
	Enemy();

	void updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow& window);
	void spawnEnemies(std::vector<Enemy>& enemies, Enemy& enemy, Player& player);
	void drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow& window);

	void updateV(Player& player);

	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity();

private:
	sf::Vector2f mVelocity;
	float mSpeed; //200 pixels / secondes

	sf::Vector2f playerCenter;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalized;

	int mSpawnCounter = 20;

	int attackDamage = 10;
	int maxHP = 100;
};

