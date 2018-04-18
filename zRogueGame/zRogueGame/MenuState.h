#pragma once
#include "State.hpp"
#include "Game.h"
#include "RessourceHolder.h"
#include "Database.h"
#include "Player.h"
#include <vector>

class MenuState : public State
{
public:
	MenuState(GameDataRef data);

	void init();

	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	//Permet de passer du menu au jeu principal
	void loadGame();
	void loadOptions();
	void loadSaves();
	void loadPlayers();
	bool isTextClicked(sf::Text& text);
	void changeTextDesign(std::vector<sf::Text>& buttons);

private:
	GameDataRef _data;
	Database* db;
	Player player;

	RessourceHolder ressources;
	sf::Sprite menuSprite;

	sf::Text mTitle;
	std::vector<sf::Text> mButtons;
};

