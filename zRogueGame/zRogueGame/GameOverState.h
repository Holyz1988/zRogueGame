#pragma once
#include "State.hpp"
#include "MenuState.h"
#include "RessourceHolder.h"
#include <vector>

class GameOverState : public State
{
public:
	GameOverState(GameDataRef data);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	sf::View mCamera;
	//Permet de passer du menu au jeu principal
	void loadMenu();
	bool isTextClicked(sf::Text text);
	void changeTextDesign(std::vector<sf::Text>& buttons);

private:
	GameDataRef _data;
	Database* db;
	Player player;

	RessourceHolder ressources;
	sf::Sprite gameOverBackground;
	std::vector<sf::Text> mButtons;
};
