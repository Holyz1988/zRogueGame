#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player() : invulnerable(false),
mSpawnerStatus(false)
{
	this->potion.quantity = 3;
	this->mBulletDelay = 0.2f;
	this->level = 1;
	this->mCurrentExperience = 0;
	this->mExperienceNeeded = 200;
	this->currency = 0;
	this->attackDamage = 5;
	this->mSpeed = 350.f;
	this->currentHp = 100;
	this->maxHP = 100;
	rect.setSize(sf::Vector2f(32.f, 32.f));
	rect.setPosition(sf::Vector2f(1000.f, 200.f));
	rect.setFillColor(sf::Color::White);
}

void Player::update(float dt, std::vector<Wall>& walls)
{
	//cout << "Level : " << level << " | currentXP : " << mCurrentExperience << " | XP Needed : " << mExperienceNeeded << " ID : " << idPlayer << endl;
	sf::Vector2f previousPos(rect.getPosition());

	//Permet de mettre la bonne frame toute les 0.175 secondes
	timePassed += clock.restart().asSeconds();

	bulletWallCollision(walls);

	if (timePassed >= switchTime)
	{
		timePassed -= switchTime;
		currentFrame++;
		if (currentFrame >= 3)
		{
			currentFrame = 0;
		}
	}
	//Mouvement du joueur et animation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->rect.move(0, mSpeed * dt);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 0 * 32, 32, 32));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		this->rect.move(-mSpeed * dt, 0);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 1 * 32, 32, 32));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->rect.move(mSpeed * dt, 0);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 2 * 32, 32, 32));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->rect.move(0, -mSpeed * dt);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 3 * 32, 32, 32));
	}

	//Arrête le joueur quand il croise un mur
	wallCollision(walls, previousPos);
	sprite.setPosition(rect.getPosition());

	levelUp();
	updateHP();
	updateTextDamage(dt);
}

bool Player::fireBallCollision(Enemy& enemy)
{
	if (this->rect.getGlobalBounds().intersects(enemy.rect.getGlobalBounds()))
	{
		return true;
	}
	else
		return false;
}

bool Player::collisionBulletWall(Wall& wall)
{
	if (mBullet.rect.getGlobalBounds().intersects(wall.rect.getGlobalBounds()))
		return true;
	else
		return false;
}

void Player::wallCollision(std::vector<Wall>& walls, sf::Vector2f previousPos)
{
	for (unsigned int i = 0; i < walls.size(); i++)
	{
		if (walls[i].rect.getGlobalBounds().intersects(this->rect.getGlobalBounds()))
		{
			rect.setPosition(previousPos);
		}
	}
}

void Player::bulletOrcCollision(std::vector<Enemy>& orcs)
{
	for (size_t i = 0; i < mBullets.size(); i++)
	{
		for (size_t j = 0; j < orcs.size(); j++)
		{
			if (orcs[j].rect.getGlobalBounds().intersects(mBullets[i].circle.getGlobalBounds()))
			{
				//L'orc touché perds des pv
				orcs[j].currentHp -= attackDamage;

				//Hp perdus
				hpOrcLost.text.setString(to_string(attackDamage));
				hpOrcLost.text.setPosition(orcs[j].rect.getPosition().x, orcs[j].rect.getPosition().y);
				hpOrcLost.textClock.restart();
				vectorHpOrcLost.push_back(hpOrcLost);

				if (orcs[j].currentHp <= 0)
				{
					orcs[j].currentHp = 0;
					mCurrentExperience += orcs[j].experienceGiven * orcs[j].level;
					currency += orcs[j].currency;
					orcs.erase(orcs.begin() + j);
				}

				mBullets.erase(mBullets.begin() + i);
				break;
			}
		}
	}
}


//Collision boule de feu et joueur
void Player::fireBallPlayerCollision(std::vector<Enemy>& enemies)
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
			if (enemies[i].rect.getGlobalBounds().intersects(rect.getGlobalBounds()))
			{
				enemies.erase(enemies.begin() + i);
				break;
			}
	}
}

void Player::losingHpToFireBall(std::vector<Enemy>& enemy, sf::Sound & sound)
{
	//On commence par vérifier si le temps d'invulnérabilité est passé
	resetInvulnerableTimer();

	for (unsigned i = 0; i < enemy.size(); i++)
	{
		if (!invulnerable)
			sprite.setColor(sf::Color(255, 255, 255, 255));//Remet la couleur du sprite d'origine 

		if (fireBallCollision(enemy[i]))
		{
			if (!invulnerable) // 2 secondes d'invulnérabilités
			{
				if (this->currentHp == 1)
				{
					this->currentHp = 0;
				}
				else
				{
					sound.play();
					this->currentHp = 1;
					invulnerable = true;
					invulnerableTimer = 0;
					sprite.setColor(sf::Color(255, 0, 0, 255));//Change la couleur du sprite à rouge
				}
			}
		}
	}
}


void Player::losingHp(std::vector<Enemy>& enemy, sf::Sound& sound)
{
	//On commence par vérifier si le temps d'invulnérabilité est passé
	resetInvulnerableTimer();

	for (unsigned i = 0; i < enemy.size(); i++)
	{
		if (!invulnerable)
			sprite.setColor(sf::Color(255, 255, 255, 255));//Remet la couleur du sprite d'origine 

		if (fireBallCollision(enemy[i]))
		{
			if (!invulnerable) // 2 secondes d'invulnérabilités
			{
				sound.play();
				this->currentHp -= enemy[i].getDamage();
				invulnerable = true;
				invulnerableTimer = 0;
			}
			else
			{
				sprite.setColor(sf::Color(255, 0, 0, 255));//Change la couleur du sprite à rouge
			}
		}
	}
}

void Player::levelUp()
{
	if (mCurrentExperience >= mExperienceNeeded)
	{
		level++;
		mCurrentExperience = mCurrentExperience - mExperienceNeeded;
		mExperienceNeeded *= 1.50;
		mBullet.circle.setRadius(mBullet.circle.getRadius() + 1);
		mBulletDelay -= 0.01;
		attackDamage += 6;
		maxHP += 50;
		currentHp = maxHP;
	}
}

bool Player::isDead()
{
	return (currentHp <= 0);
}

void Player::fireBullets(sf::RenderWindow& window, std::vector<Wall> walls, sf::Sound& sound)
{
	mTimeAccumulator += mBulletClock.restart().asSeconds();
	// Accumule temps, on charge et on tire

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mTimeAccumulator > mBulletDelay)
	{
		mBullet.circle.setPosition(mPlayerCenter);
		mBullet.setVelocity(mAimDirectionNormalized * mBullet.getSpeed());
		sound.play();
		mBullets.push_back(mBullet);
		mTimeAccumulator = 0; // On remet à 0 le chrono.
	}
	
}

void Player::drawBullets(sf::RenderWindow & window)
{
	for (size_t i = 0; i < mBullets.size(); i++)
	{
		window.draw(mBullets[i].circle);
	}
}

void Player::drawHpLost(sf::RenderWindow& window)
{
	for (int i = 0; i < vectorHpOrcLost.size(); i++)
	{
		window.draw(vectorHpOrcLost[i].text);
	}
}

void Player::updateTextDamage(float dt)
{

	for (int i = 0; i < vectorHpOrcLost.size(); i++)
	{
		if (vectorHpOrcLost[i].textClock.getElapsedTime().asSeconds() > 3.0f)
		{
			vectorHpOrcLost.erase(vectorHpOrcLost.begin() + i);
		}
		else
		{
			vectorHpOrcLost[i].text.move(0, - 140.f * dt);
		}
	}
}

void Player::updateVectors(sf::RenderWindow& window)
{
	mPlayerCenter = sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2.f, rect.getPosition().y + rect.getSize().y / 2.f);
	mMousePixelPosition = sf::Mouse::getPosition(window);
	mMouseWorldPosition = window.mapPixelToCoords(mMousePixelPosition);
	mAimDirection = mMouseWorldPosition - mPlayerCenter;
	mAimDirectionNormalized = mAimDirection / (sqrt(pow(mAimDirection.x, 2) + pow(mAimDirection.y, 2)));
}

void Player::updateHP()
{
	text.setString(to_string(currentHp) + "/" + to_string(maxHP));
	text.setPosition(rect.getPosition().x, rect.getPosition().y - rect.getSize().y / 2);
}

void Player::bulletWallCollision(std::vector<Wall>& walls)
{
	for (size_t i = 0; i < mBullets.size(); i++)
	{
		mBullets[i].circle.move(mBullets[i].getVelocity());
		for (size_t j = 0; j < walls.size(); j++)
		{
			if (walls[j].rect.getGlobalBounds().intersects(mBullets[i].circle.getGlobalBounds()))
			{
				mBullets.erase(mBullets.begin() + i);
				break;
			}
		}
	}
}

void Player::resetInvulnerableTimer()
{
	invulnerableTimer += invulnerableClock.restart().asSeconds();

	// 2 secondes d'invulnérabilité
	if (invulnerableTimer > 2)
	{
		invulnerable = false;
	}
}

void Player::spawnOrcs(Wall& spawnTile)
{
	if (rect.getGlobalBounds().intersects(spawnTile.rect.getGlobalBounds()))
		mSpawnerStatus = true;
}

int Player::getDamage()
{
	return this->attackDamage;
}

void Player::setDamage(int damage)
{
	this->attackDamage = damage;
}

void Player::setBulletDelay(float bulletDelaly)
{
	this->mBulletDelay = bulletDelaly;
}

void Player::setBulletRadius(float bulletRadius)
{
	this->mBullet.circle.setRadius(bulletRadius);
}

int Player::getCurrentHP()
{
	return this->currentHp;
}

std::vector<Projectile> Player::getBullets()
{
	return this->mBullets;
}

bool Player::getSpawnerStatus()
{
	return this->mSpawnerStatus;
}

float Player::getBulletDelay()
{
	return this->mBulletDelay;
}

Projectile Player::getBullet()
{
	return this->mBullet;
}
