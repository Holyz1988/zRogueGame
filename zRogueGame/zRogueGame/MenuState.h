#pragma once
#include "GameState.h"
#include "RessourceHolder.h"
#include <vector>

class MenuState : public GameState
{
public:
	MenuState(Game* game);


	virtual void handleInput();
	virtual void update(sf::Time dt);
	virtual void draw(sf::Time dt);

private:
	//Permet de passer du menu au jeu principal
	void loadGame();
	bool isTextClicked(sf::Text text);

private:
	RessourceHolder menuScreen;
	sf::Sprite menuSprite;

	std::vector<sf::Text> buttons;
};

