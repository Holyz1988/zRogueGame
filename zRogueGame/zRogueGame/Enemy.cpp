#include "Enemy.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

#define INITIAL_ENEMY_NUMBER 10

Enemy::Enemy() : mVelocity(8.f, 8.f),
mSpawnCounter(20),
timeWalking(3),
mSpeed(400.f),
switchTime(0.175f),
currentFrame(0),
attackDamage(10),
maxHP(100)
{
	rect.setSize(sf::Vector2f(64.f, 64.f));
	rect.setFillColor(sf::Color::Color(255, 116, 14));
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(0.4f);
}

Enemy::Enemy(sf::Vector2f velocity) : mSpawnCounter(20),
timeWalking(3),
mSpeed(10.f),
switchTime(0.175f),
currentFrame(0),
attackDamage(10),
maxHP(100)
{
	rect.setSize(sf::Vector2f(64.f, 64.f));
	this->mVelocity = velocity;
}

void Enemy::updatePos()
{
	sprite.setPosition(rect.getPosition());
}

//Permet de d�finir la trajectoire des boules de feu
//se d�place vers l'axe X du joueur lors de l'apparition
//de la boule
void Enemy::updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow& window, float dt)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].rect.move(-getVelocity().x * dt, 0);
		enemies[i].sprite.setPosition(enemies[i].rect.getPosition());
	}
}

//Permet de faire appara�tre les boules de feu
void Enemy::spawnEnemies(std::vector<Enemy>& enemies, Enemy& enemy, Player& player)
{
	if (mSpawnCounter < 200)
		mSpawnCounter++;
	if (mSpawnCounter >= 200)
	{
		enemy.rect.setPosition(0, player.rect.getPosition().y);
		enemy.setVelocity(aimDirectionNormalized * mSpeed);
		enemies.push_back(enemy);
		mSpawnCounter = 0;
	}
}

//D�ssine les ennemies � l'�cran 
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
	//G�n�re un nombre entre 1 et 4, pour d�finir la direction dans laquelle l'�nnemi va se diriger
	int direction = (rand() % 4) + 1;
	mDirection = static_cast<Direction>(direction);

	//L'�nnemi se d�place pendant 3 secondes avant de changer de direction
	while (timeWalking <= 3)
	{
		timeWalking += clockOrc.getElapsedTime().asSeconds();
		if (mDirection == Direction::DOWN)
		{
			rect.move(0, mVelocity.y * dt);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 10 * 64, 64, 64));
		}
		else if (mDirection == Direction::LEFT)
		{
			rect.move(-mVelocity.x * dt, 0);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 9 * 64, 64, 64));
		}
		else if (mDirection == Direction::RIGHT)
		{
			rect.move(mVelocity.x * dt, 0);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 11 * 64, 64, 64));
		}
		else if (mDirection == Direction::TOP)
		{
			rect.move(0, -mVelocity.y * dt);
			sprite.setTextureRect(sf::IntRect(currentFrame * 64, 8 * 64, 64, 64));
		}
		else
		{
			//Rien ne se passe
		}
	}

	//On remet � 0 le compte � rebours
	if (timeWalking >= 3)
		timeWalking = 0;
}

void Enemy::moveEnemies(std::vector<Enemy>& enemies, Enemy& enemy, Player& player)
{
	for (size_t i = 0; i < INITIAL_ENEMY_NUMBER; i++)
	{
		enemy.rect.setPosition(0, player.rect.getPosition().y);
		enemy.setVelocity(aimDirectionNormalized * mSpeed);
		enemies.push_back(enemy);
		mSpawnCounter = 0;
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




