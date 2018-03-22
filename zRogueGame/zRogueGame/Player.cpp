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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		rect.move(-movementSpeed * dt, 0);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 1 * 32, 32, 32));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rect.move(movementSpeed * dt, 0);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 2 * 32, 32, 32));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		rect.move(0, -movementSpeed * dt);
		sprite.setTextureRect(sf::IntRect(currentFrame * 32, 3 * 32, 32, 32));
	}
	

	sprite.setPosition(rect.getPosition());
}

