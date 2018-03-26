#include "Enemy.h"
#include <time.h>
#include <iostream>

Enemy::Enemy() : mVelocity(0.f,0.f),
				 mSpeed(8.f)
{
	rect.setSize(sf::Vector2f(32, 32));
	rect.setFillColor(sf::Color::Red);
}

void Enemy::updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow & window)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].setVelocity(aimDirectionNormalized * mSpeed);
		enemies[i].rect.move(-getVelocity().x, 0);
	}
}

//Permet de faire apparaître les ennemies
void Enemy::spawnEnemies(std::vector<Enemy>& enemies, Enemy& enemy, Player & player)
{
	if (mSpawnCounter < 20)
		mSpawnCounter++;
	if (mSpawnCounter >= 20)
	{
		enemy.rect.setPosition(0 , player.rect.getPosition().y);
		enemy.setVelocity(aimDirectionNormalized * mSpeed);
		enemies.push_back(enemy);
		mSpawnCounter = 0;
	}
}

void Enemy::drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow & window)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		window.draw(enemies[i].rect);
	}
}

void Enemy::updateV(Player& player)
{
	this->playerCenter = sf::Vector2f(player.rect.getPosition().x + player.rect.getSize().x / 2.f, player.rect.getPosition().y + player.rect.getSize().y / 2.f);
	this->aimDirection = rect.getPosition() - playerCenter;
	this->aimDirectionNormalized = aimDirection / (sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2)));
}

void Enemy::setVelocity(sf::Vector2f velocity)
{
	this->mVelocity = velocity;
}

sf::Vector2f Enemy::getVelocity()
{
	return this->mVelocity;
}




