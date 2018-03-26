#include "Enemy.h"
#include <time.h>

Enemy::Enemy()
{
	rect.setSize(sf::Vector2f(32, 32));
	rect.setFillColor(sf::Color::Red);
}

void Enemy::updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow & window, Player player)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].rect.move(sf::Vector2f(player.rect.getPosition()));
	}
}

void Enemy::spawnEnemies(std::vector<Enemy>& enemies, Enemy& enemy, sf::RenderWindow& window, Player player)
{
	srand(time(NULL));

	if (spawnCounter < 20)
		spawnCounter++;
	if (spawnCounter >= 20)
	{
		enemy.rect.setPosition(0 , player.rect.getPosition().y);
		enemies.push_back(enemy);
		spawnCounter = 0;
	}
}

void Enemy::drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow & window)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		window.draw(enemies[i].rect);
	}
}




