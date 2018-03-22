#pragma once
#include "GameState.h"
#include "RessourceHolder.h"
#include <vector>

class MenuState : public GameState
{
public:
	MenuState(Game* game);

	virtual void handleInput();
	virtual void update(float dt);
	virtual void draw(float dt);

private:
	//Permet de passer du menu au jeu principal
	void loadGame();
	void loadOptions();
	bool isTextClicked(sf::Text& text);
	void changeTextDesign(std::vector<sf::Text>& buttons);

private:
	RessourceHolder ressources;
	sf::Sprite menuSprite;

	sf::Text mTitle;
	std::vector<sf::Text> mButtons;
};

