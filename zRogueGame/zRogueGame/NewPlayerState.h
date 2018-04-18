#pragma once

#include "State.hpp"
#include "MenuState.h"
#include "RessourceHolder.h"
#include <vector>

class NewPlayerState : public State
{
public:
	NewPlayerState(GameDataRef data);
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
	std::vector<Player> players;
	Database* db;

	RessourceHolder ressources;
	sf::Sprite newGameBackground;

	sf::Text mTitle;
	std::vector<sf::Text> mButtons;
};
