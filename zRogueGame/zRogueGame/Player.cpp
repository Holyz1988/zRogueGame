#include "Player.h"
#include <iostream>

Player::Player() : invulnerable(false)
{
	this->currentHp = maxHP;
	rect.setSize(sf::Vector2f(32.f, 32.f));
	rect.setPosition(sf::Vector2f(200.f, 200.f));
}

//Met � jour la position du joueur
void Player::update(float dt)
{
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
	sprite.setPosition(rect.getPosition());
}

//M�thode qui test si il ya une collision entre un ennemi et le joueur
bool Player::colisionPlayerFireball(Enemy& enemy)
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
	if (bullet.rect.getGlobalBounds().intersects(wall.rect.getGlobalBounds()))
		return true;
	else
		return false;
}

void Player::losingHp(Enemy& enemy)
{
	if (colisionPlayerFireball(enemy))
	{
		resetInvulnerableTimer();

		if (!invulnerable) // 2 secondes d'invuln�rabilit�s
		{
			this->currentHp -= enemy.getDamage();
			invulnerable = true;
			invulnerableTimer = 0;
		}
	}
}

//Lorsque l'on clique gauche sur la souris, on charge les projectiles dans un vecteur
//et on les d�truit s'ils sortent de la fen�tre.
void Player::fireBullets(sf::RenderWindow& window, std::vector<Wall> walls)
{
	timeAccumulator += bulletClock.restart().asSeconds(); // Accumule temps
														  //On charge et on tire
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timeAccumulator > bulletDelay)
	{
		bullet.circle.setPosition(playerCenter);
		bullet.setVelocity(aimDirectionNormalized * bullet.getSpeed());
		bullets.push_back(bullet);
		timeAccumulator = 0; // On remet � 0 le chrono.
	}

	wallCollision(walls);
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
	playerCenter = sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2.f, rect.getPosition().y + rect.getSize().y / 2.f);
	mousePixelPosition = sf::Mouse::getPosition(window);
	mouseWorldPosition = window.mapPixelToCoords(mousePixelPosition);
	aimDirection = mouseWorldPosition - playerCenter;
	aimDirectionNormalized = aimDirection / (sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2)));
}

//Collision projectile joueur et projectile dragon
void Player::bulletCollision(std::vector<Enemy>& enemies)
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

//Collision mur et tir du joueur
void Player::wallCollision(std::vector<Wall>& walls)
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

	if (invulnerableTimer > 2) // 2 secondes d'invuln�rabilit�
		invulnerable = false;
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
