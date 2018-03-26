#include "Player.h"

Player::Player()
{
	rect.setSize(sf::Vector2f(32.f, 32.f));
	rect.setPosition(sf::Vector2f(200.f, 200.f));
}

void Player::update(float dt)
{
	timePassed += clock.getElapsedTime().asSeconds();
	clock.restart();

	if (timePassed >= switchTime)
	{
		timePassed -= switchTime;
		currentFrame++;
		if (currentFrame >= 3)
		{
			currentFrame = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		rect.move(0, movementSpeed * dt);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 0 * 32, 32, 32));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		rect.move(-movementSpeed * dt, 0);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 1 * 32, 32, 32));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rect.move(movementSpeed * dt, 0);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 2 * 32, 32, 32));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		rect.move(0, -movementSpeed * dt);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 3 * 32, 32, 32));
	}

	sprite.setPosition(rect.getPosition());
}

int Player::getDamage()
{
	return this->attackDamage;
}

void Player::setDamage(int damage)
{
	this->attackDamage = damage;
}

void Player::fireBullets(sf::RenderWindow& window)
{
	timeAccumulator += bulletClock.restart().asSeconds(); // Accumule temps
														  //On charge et on tire
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timeAccumulator > bulletDelay)
	{
		bullet.circle.setPosition(playerCenter);
		bullet.setVelocity(aimDirectionNormalized * bullet.getSpeed());
		bullets.push_back(bullet);
		timeAccumulator = 0; // On remet à 0 le chrono.
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].circle.move(bullets[i].getVelocity());

		//Si le projectile sors de l'écran, on le détruit.
		if (bullets[i].circle.getPosition().x < 0 ||
			bullets[i].circle.getPosition().y < 0 ||
			bullets[i].circle.getPosition().x > window.getSize().x ||
			bullets[i].circle.getPosition().y > window.getSize().y)
		{
			bullets.erase(bullets.begin());
		}
	}
}

void Player::drawBullets(sf::RenderWindow & window)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		window.draw(bullets[i].circle);
	}
}

void Player::updateVectors(sf::RenderWindow& window)
{
	playerCenter = sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2.f, rect.getPosition().y + rect.getSize().y / 2.f);
	mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
	aimDirection = mousePosition - playerCenter;
	aimDirectionNormalized = aimDirection / (sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2)));
}

