#include "Enemy.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

Enemy::Enemy() : mVelocity(8.f, 8.f),
mSpawnCounter(20),
timeWalking(3),
mSpeed(10.f),
switchTime(0.175f),
currentFrame(0),
attackDamage(100),
maxHP(100)
{
	rect.setSize(sf::Vector2f(64.f, 64.f));
	rect.setFillColor(sf::Color::White);
}

Enemy::Enemy(sf::Vector2f velocity) : mSpawnCounter(20),
timeWalking(3),
mSpeed(10.f),
switchTime(0.175f),
currentFrame(0),
attackDamage(100),
maxHP(100)
{
	rect.setSize(sf::Vector2f(64.f, 64.f));
	this->mVelocity = velocity;
}

void Enemy::updatePos()
{
	sprite.setPosition(rect.getPosition());
}

void Enemy::updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow & window)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].setVelocity(aimDirectionNormalized * mSpeed);
		enemies[i].rect.move(-getVelocity().x, 0);
		enemies[i].sprite.setPosition(enemies[i].rect.getPosition());
	}
}

//Permet de faire apparaître les ennemies
void Enemy::spawnEnemies(std::vector<Enemy>& enemies, Enemy& enemy, Player & player)
{
	if (mSpawnCounter < 20)
		mSpawnCounter++;
	if (mSpawnCounter >= 20)
	{
		enemy.rect.setPosition(0, player.rect.getPosition().y);
		enemy.setVelocity(aimDirectionNormalized * mSpeed);
		enemies.push_back(enemy);
		mSpawnCounter = 0;
	}
}

//Déssine les ennemies à l'écran 
void Enemy::drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow & window)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		window.draw(enemies[i].sprite);
	}
}

//ENEMI AI
void Enemy::moveEnemies(float dt)
{
	srand(time(NULL));
	timePassed += clock.restart().asSeconds();

	//On change de sprite toutes les 0.175 secondes
	if (timePassed >= switchTime)
	{
		timePassed -= switchTime;
		currentFrame++;
		if (currentFrame >= 9)
		{
			currentFrame = 0;
		}
	}
	//Génére un nombre entre 1 et 4, pour définir la direction dans laquelle l'énnemi va se diriger
	int direction = (rand() % 4) + 1;

	//L'énnemi se déplace pendant 3 secondes avant de changer de direction
	while (timeWalking <= 3)
	{
		timeWalking += clockOrc.getElapsedTime().asSeconds();
		if (direction == 1)
		{
			rect.move(0, mVelocity.y * dt);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 10 * 64, 64, 64));
		}
		else if (direction == 2)
		{
			rect.move(-mVelocity.x * dt, 0);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 9 * 64, 64, 64));
		}
		else if (direction == 3)
		{
			rect.move(mVelocity.x * dt, 0);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 11 * 64, 64, 64));
		}
		else if (direction == 4)
		{
			rect.move(0, -mVelocity.y * dt);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 8 * 64, 64, 64));
		}
		else
		{
			//Rien ne se passe
		}
	}

	//On remet à 0 le compte à rebours
	if (timeWalking >= 3)
		timeWalking = 0;
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




