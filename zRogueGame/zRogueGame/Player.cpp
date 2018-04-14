#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player() : invulnerable(false),
mSpawnerStatus(false)
{
	this->level = 1;
	this->mCurrentExperience = 0;
	this->mExperienceNeeded = this->level * 200;
	this->currency = 0;
	this->maxHP = 100;
	this->attackDamage = 100;
	this->mSpeed = 350.f;
	this->currentHp = maxHP;
	rect.setSize(sf::Vector2f(32.f, 32.f));
	rect.setPosition(sf::Vector2f(1000.f, 200.f));
	rect.setFillColor(sf::Color::White);
}

//Met � jour la position du joueur
//G�re l'animation du joueur
//G�re les collisions
//Met � jour le sprite et le rectangle du joueur
void Player::update(float dt, std::vector<Wall>& walls)
{
	cout << mCurrentExperience << endl;
	sf::Vector2f previousPos(rect.getPosition());

	//Permet de mettre la bonne frame toute les 0.175 secondes
	timePassed += clock.restart().asSeconds();

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

	//Arr�te le joueur quand il croise un mur
	wallCollision(walls, previousPos);

	sprite.setPosition(rect.getPosition());
}

//Test si il y a une collision entre un ennemi et le joueur
bool Player::fireBallCollision(Enemy& enemy)
{

	if (this->rect.getGlobalBounds().intersects(enemy.rect.getGlobalBounds()))
	{
		return true;
	}
	else
		return false;
}

//Test si il y a une collision entre un mur et les projectiles
bool Player::collisionBulletWall(Wall& wall)
{
	if (bullet.rect.getGlobalBounds().intersects(wall.rect.getGlobalBounds()))
		return true;
	else
		return false;
}

//Collision entre tous les murs de l'ar�ne est le joueur
void Player::wallCollision(std::vector<Wall>& walls, sf::Vector2f previousPos)
{
	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i].rect.getGlobalBounds().intersects(this->rect.getGlobalBounds()))
		{
			rect.setPosition(previousPos);
		}
	}
}

void Player::bulletOrcCollision(std::vector<Enemy>& orcs)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		for (size_t j = 0; j < orcs.size(); j++)
		{
			if (orcs[j].rect.getGlobalBounds().intersects(bullets[i].circle.getGlobalBounds()))
			{
				//L'orc touch� perds des hp
				orcs[j].currentHp -= attackDamage;

				if (orcs[j].currentHp <= 0)
				{
					orcs[j].currentHp = 0;
					mCurrentExperience += orcs[j].experienceGiven;
					currency += orcs[j].currency;
					orcs.erase(orcs.begin() + j);
				}

				bullets.erase(bullets.begin() + i);
				break;
			}
		}
	}
}

//Collision projectile joueur et projectile dragon
void Player::fireBallBulletCollision(std::vector<Enemy>& enemies)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		for (size_t j = 0; j < enemies.size(); j++)
		{
			if (enemies[j].rect.getGlobalBounds().intersects(bullets[i].circle.getGlobalBounds()))
			{
				enemies.erase(enemies.begin() + j);
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
	}
}

void Player::losingHp(std::vector<Enemy>& enemy)
{
	//On commence par v�rifier si le temps d'invuln�rabilit� est pass�
	resetInvulnerableTimer();

	for (unsigned i = 0; i < enemy.size(); i++)
	{
		if (!invulnerable)
			sprite.setColor(sf::Color(255, 255, 255, 255));//Remet la couleur du sprite d'origine 

		if (fireBallCollision(enemy[i]))
		{
			if (!invulnerable) // 2 secondes d'invuln�rabilit�s
			{
				this->currentHp -= enemy[i].getDamage();
				invulnerable = true;
				invulnerableTimer = 0;
			}
			else
			{
				sprite.setColor(sf::Color(255, 0, 0, 255));//Change la couleur du sprite � rouge
			}
		}
	}
}

//Lorsque l'on clique gauche sur la souris, on charge les projectiles dans un vecteur
//et on les d�truit s'ils sortent de la fen�tre.
void Player::fireBullets(sf::RenderWindow& window, std::vector<Wall> walls)
{
	mTimeAccumulator += bulletClock.restart().asSeconds(); // Accumule temps
														  //On charge et on tire
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mTimeAccumulator > mBulletDelay)
	{
		bullet.circle.setPosition(mPlayerCenter);
		bullet.setVelocity(aimDirectionNormalized * bullet.getSpeed());
		bullets.push_back(bullet);
		mTimeAccumulator = 0; // On remet � 0 le chrono.
	}

	bulletWallCollision(walls);
}

//On d�ssine les projectiles joueur � l'�cran
void Player::drawBullets(sf::RenderWindow & window)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		window.draw(bullets[i].circle);
	}
}

//Permet de calculer la direction normalis�
void Player::updateVectors(sf::RenderWindow& window)
{
	mPlayerCenter = sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2.f, rect.getPosition().y + rect.getSize().y / 2.f);
	mMousePixelPosition = sf::Mouse::getPosition(window);
	mMouseWorldPosition = window.mapPixelToCoords(mMousePixelPosition);
	aimDirection = mMouseWorldPosition - mPlayerCenter;
	aimDirectionNormalized = aimDirection / (sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2)));
}



//Collision mur et tir du joueur
void Player::bulletWallCollision(std::vector<Wall>& walls)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].circle.move(bullets[i].getVelocity());
		for (size_t j = 0; j < walls.size(); j++)
		{
			if (walls[j].rect.getGlobalBounds().intersects(bullets[i].circle.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
	}
}



//Permet de retirer la vuln�rabilit�
void Player::resetInvulnerableTimer()
{
	invulnerableTimer += invulnerableClock.restart().asSeconds();

	// 2 secondes d'invuln�rabilit�
	if (invulnerableTimer > 2)
	{
		invulnerable = false;
	}
}

//Si le joueur a une collision avec le spawner
//Fait appara�tre les mobs
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

int Player::getCurrentHP()
{
	return this->currentHp;
}

std::vector<Projectile> Player::getBullets()
{
	return this->bullets;
}

bool Player::getSpawnerStatus()
{
	return this->mSpawnerStatus;
}
