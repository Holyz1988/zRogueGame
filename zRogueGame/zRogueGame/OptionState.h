#pragma once
#include "GameState.h"
#include "RessourceHolder.h"
#include <vector>

class OptionState : public GameState
{
public:
	OptionState(Game* game);

	virtual void handleInput();
	virtual void update(float dt);
	virtual void draw(float dt);

private:
	//Permet de passer du menu au jeu principal
	void loadMenu();
	bool isTextClicked(sf::Text text);
	void changeTextDesign(std::vector<sf::Text>& buttons);

private:
	RessourceHolder optionScreen;
	sf::Sprite optionBackground;

	std::vector<sf::Text> buttons;
};


