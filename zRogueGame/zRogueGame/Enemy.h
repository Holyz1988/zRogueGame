#pragma once
#include "Entity.h"
#include "RessourceHolder.h"
#include "Player.h"

class Enemy : public Entity
{
public:
	Enemy();

	void updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow& window, Player player);
	void spawnEnemies(std::vector<Enemy>& enemies, Enemy& enemy, sf::RenderWindow& window, Player player);
	void drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow& window);

private:
	sf::Vector2f Velocity;
	float speed; //200 pixels / secondes
	
	int spawnCounter = 20;

	int attackDamage = 10;
	int maxHP = 100;
};

