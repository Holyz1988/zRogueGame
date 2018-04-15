#pragma once

#include "State.hpp"
#include "MenuState.h"
#include "RessourceHolder.h"
#include <vector>

class NewGameState : public State
{
public:
	NewGameState(GameDataRef data);
	void init();

	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	//Permet de passer du menu au jeu principal
	void loadMenu();
	bool isTextClicked(sf::Text text);
	void changeTextDesign(std::vector<sf::Text>& buttons);

private:
	GameDataRef _data;

	RessourceHolder optionScreen;
	sf::Sprite optionBackground;

	std::vector<sf::Text> buttons;
};

