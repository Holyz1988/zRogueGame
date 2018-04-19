#include "Enemy.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

#define INITIAL_ENEMY_NUMBER 25
#define BLOCK_SIZE 32
#define BLOCK_NUMBER 40

using namespace std;

Enemy::Enemy() : mVelocity(25.f, 25.f),
mSpawnCounter(20),
timeWalking(3),
direction(1),
mSpeed(400.f),
switchTime(0.175f),
timePassed(0),
currentFrame(0)
{
	this->level = 1;
	this->experienceGiven = 30;
	this->rect.setSize(sf::Vector2f(32.f, 50.f));
	this->rect.setFillColor(sf::Color::White);
	this->currency = level * 10;
	this->maxHP = level * 100;
	this->attackDamage = level * 20;
	this->mSpeed = 250.f;
	this->currentHp = maxHP;
}

Enemy::Enemy(Player& player) : mVelocity(25.f, 25.f),
mSpawnCounter(20),
timeWalking(3),
direction(1),
mSpeed(400.f),
switchTime(0.175f),
timePassed(0),
currentFrame(0)
{
	this->level = player.level;
	this->experienceGiven = 10 * player.level;
	this->rect.setSize(sf::Vector2f(32.f, 50.f));
	this->rect.setFillColor(sf::Color::White);
	this->currency = 20;
	this->maxHP = 100 * player.level;
	this->attackDamage = 20 + (10 * player.level);
	this->mSpeed = 250.f;
	this->currentHp = maxHP;
}

/*
Enemy::Enemy(sf::Vector2f velocity) : mSpawnCounter(20),
timeWalking(3),
direction(1),
mSpeed(10.f),
switchTime(0.175f),
currentFrame(0)
{
	rect.setSize(sf::Vector2f(64.f, 64.f));
	this->mVelocity = velocity;
}
*/

void Enemy::updatePos()
{
	this->sprite.setPosition(this->rect.getPosition().x - 16, this->rect.getPosition().y - 17);
}

void Enemy::drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow& window)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		window.draw(enemies[i].sprite);
		window.draw(enemies[i].text);
	}
}

void Enemy::wallCollision(std::vector<Wall>& walls, sf::Vector2f previousPos)
{
	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i].rect.getGlobalBounds().intersects(this->rect.getGlobalBounds()))
		{
			rect.setPosition(previousPos);
		}
	}
}

//ENEMI AI
void Enemy::moveEnemies(float dt, std::vector<Wall>& walls)
{
	sf::Vector2f previousPos(rect.getPosition());
	timePassed += clock.restart().asSeconds();

	//On change de sprite toutes les 0.175 secondes
	if (timePassed >= switchTime)
	{
		timePassed = 0;
		currentFrame++;
		if (currentFrame >= 9)
		{
			currentFrame = 0;
		}
	}

	//G�n�re un nombre entre 1 et 4, pour d�finir la direction dans laquelle l'�nnemi va se diriger
	if (timeWalking > 3)
	{
		direction = (rand() % 4) + 1;
	}

	mDirection = static_cast<Direction>(direction);

	//L'�nnemi se d�place pendant 3 secondes avant de changer de direction
	if (timeWalking <= 3)
	{
		timeWalking += clockOrc.restart().asSeconds();
		switch (mDirection)
		{
		case Direction::DOWN:
			this->rect.move(0, mVelocity.y * dt);
			this->sprite.setTextureRect(sf::IntRect(currentFrame * 64, 10 * 64, 64, 64));
			break;
		case Direction::LEFT:
			this->rect.move(-mVelocity.x * dt, 0);
			this->sprite.setTextureRect(sf::IntRect(currentFrame * 64, 9 * 64, 64, 64));
			break;
		case Direction::RIGHT:
			this->rect.move(mVelocity.x * dt, 0);
			this->sprite.setTextureRect(sf::IntRect(currentFrame * 64, 11 * 64, 64, 64));
			break;
		case Direction::TOP:
			this->rect.move(0, -mVelocity.y * dt);
			this->sprite.setTextureRect(sf::IntRect(currentFrame * 64, 8 * 64, 64, 64));
			break;
		default:
			break;
		}
	}
	else
	{
		//Compte � rebours � 0
		timeWalking = 0;
	}

	//Stop l'orc s'il rencontre un mur
	wallCollision(walls, previousPos);

	//Synchronise le rectangle et le sprite
	updatePos();
	text.setString(to_string(currentHp) + "/" + to_string(maxHP));
	text.setPosition(rect.getPosition().x, rect.getPosition().y - rect.getSize().y / 2);
}

void Enemy::spawEnemies(std::vector<Enemy>& enemies, Enemy& enemy, Wall& spawnTile, Player& player)
{
	for (int i = 0; i < INITIAL_ENEMY_NUMBER; i++)
	{
		do
		{
			//On met les nouvelles stats aux orcs
			enemy.rect.setPosition((rand() % (32 * 36)) + 32, (rand() % (32 * 10)) + 50);
			enemy.level = player.level;
			enemy.maxHP = player.level * 100;
			enemy.currentHp = enemy.maxHP;
			enemy.attackDamage = player.level * 20;
		} while (enemy.rect.getGlobalBounds().intersects(spawnTile.rect.getGlobalBounds()));

		enemy.sprite.setPosition(enemy.rect.getPosition());
		enemy.clockOrc.restart();//on redemarre l'horloge pour l'animation
		enemies.push_back(enemy);
	}
}

void Enemy::updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow& window, float dt)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].rect.move(-getVelocity().x * dt, 0);
		enemies[i].sprite.setPosition(enemies[i].rect.getPosition());
	}
}

void Enemy::spawnFireBalls(std::vector<Enemy>& fireBalls, Enemy& fireBall, Player& player)
{
	if (mSpawnCounter < 50)
		mSpawnCounter++;
	if (mSpawnCounter >= 50)
	{
		fireBall.rect.setPosition(0, player.rect.getPosition().y);
		fireBall.setVelocity(aimDirectionNormalized * mSpeed);
		fireBalls.push_back(fireBall);
		mSpawnCounter = 0;
	}
}

void Enemy::updateV(Player& player)
{
	this->playerCenter = sf::Vector2f(player.rect.getPosition().x + player.rect.getSize().x / 2.f, player.rect.getPosition().y + player.rect.getSize().y / 2.f);
	this->aimDirection = rect.getPosition() - playerCenter;
	this->aimDirectionNormalized = aimDirection / (sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2)));

	if (currentHp = maxHP)
	{
		maxHP = maxHP * player.level;
	}
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




