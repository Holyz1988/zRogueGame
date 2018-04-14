#include "Enemy.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

#define INITIAL_ENEMY_NUMBER 10
#define BLOCK_SIZE 32
#define BLOCK_NUMBER 40

using namespace std;

Enemy::Enemy() : mVelocity(15.f, 15.f),
mSpawnCounter(20),
timeWalking(3),
direction(1),
mSpeed(400.f),
switchTime(0.175f),
currentFrame(0),
attackDamage(10),
maxHP(100)
{
	srand(time(NULL));
	rect.setSize(sf::Vector2f(64.f, 64.f));
	rect.setFillColor(sf::Color::Color(255, 116, 14));
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(0.4f);
}

Enemy::Enemy(sf::Vector2f velocity) : mSpawnCounter(20),
timeWalking(3),
direction(1),
mSpeed(10.f),
switchTime(0.175f),
currentFrame(0),
attackDamage(10),
maxHP(100)
{
	srand(time(NULL));
	rect.setSize(sf::Vector2f(64.f, 64.f));
	this->mVelocity = velocity;
}

void Enemy::updatePos()
{
	sprite.setPosition(rect.getPosition());
}

//Permet de définir la trajectoire des boules de feu
//se déplace vers l'axe X du joueur lors de l'apparition
//de la boule
void Enemy::updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow& window, float dt)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].rect.move(-getVelocity().x * dt, 0);
		enemies[i].sprite.setPosition(enemies[i].rect.getPosition());
	}
}

//Permet de faire apparaître les boules de feu
void Enemy::spawnFireBalls(std::vector<Enemy>& fireBalls, Enemy& fireBall, Player& player)
{
	if (mSpawnCounter < 200)
		mSpawnCounter++;
	if (mSpawnCounter >= 200)
	{
		fireBall.rect.setPosition(0, player.rect.getPosition().y);
		fireBall.setVelocity(aimDirectionNormalized * mSpeed);
		fireBalls.push_back(fireBall);
		mSpawnCounter = 0;
	}
}

//Déssine les ennemies à l'écran 
void Enemy::drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow& window)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		window.draw(enemies[i].sprite);
	}
}

//ENEMI AI
void Enemy::moveEnemies(float dt)
{
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
	if (timeWalking > 3)
	{ 
		direction = (rand() % 4) + 1;
	}
	
	mDirection = static_cast<Direction>(direction);

	//L'énnemi se déplace pendant 3 secondes avant de changer de direction
	if (timeWalking <= 3)
	{
		timeWalking += clockOrc.restart().asSeconds();
		switch (mDirection)
		{
		case Direction::DOWN:
			rect.move(0, mVelocity.y * dt);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 10 * 64, 64, 64));
			break;	
		case Direction::LEFT:
			rect.move(-mVelocity.x * dt, 0);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 9 * 64, 64, 64));
			break;
		case Direction::RIGHT:
			rect.move(mVelocity.x * dt, 0);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 11 * 64, 64, 64));
			break;
		case Direction::TOP:
			rect.move(0, -mVelocity.y * dt);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 8 * 64, 64, 64));
			break;
		default:
			break;
		}
	}
	else
	{
		//Compte à rebours à 0
		timeWalking = 0;
	}
}

//Fait apparaître les enemies à l'écran
void Enemy::spawEnemies(std::vector<Enemy>& enemies, Enemy& enemy)
{
	for (int i = 0; i < INITIAL_ENEMY_NUMBER; i++)
	{
		enemy.rect.setPosition((rand() % (32 * 38)) + 32, (rand() % (32 * 13)) + 32);
		enemies.push_back(enemy);
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

int Enemy::getDamage()
{
	return this->attackDamage;
}




