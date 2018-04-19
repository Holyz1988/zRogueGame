#pragma once

#include "MenuState.h"
#include "State.hpp"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Database.h"
#include "TextDisplay.h"
//#include "SFML\Audio.hpp"

/**
* \file			PlayState.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe permettant de g�rer l'�tat lorsqu'on est entrain de jouer
*
* \details		Classe permettant de g�rer l'�tat lorsqu'on est entrain de jouer
*
*/


/*! \class		PlayState
* \brief		Classe permettant de g�rer l'�tat lorsqu'on est entrain de jouer
*
* \details		Classe permettant de g�rer l'�tat lorsqu'on est entrain de jouer
*
*/

class PlayState : public State
{
public:
	/**
	* \brief	Constructeur
	*
	*Constructeur de l'�tat jouer, en chargeant un joueur en BDD
	*
	* \param data : stock les donn�es communes associ�es � chaque �tat (fen�tre, �tat actuel)
	* \param player : r�f�rence vers un objet joueur
	*/
	PlayState(GameDataRef data, Player& player);

	/**
	* \brief	Constructeur
	*
	*Constructeur de l'�tat jouer
	*
	* \param data : stock les donn�es communes associ�es � chaque �tat (fen�tre, �tat actuel)
	*/
	PlayState(GameDataRef data);

	/**
	* \brief	Destructeur
	*
	*Destructeur de l'�tat jouer
	*
	*/
	~PlayState();

	/**
	* \brief	Initialise l'�tat jouer
	*
	*Initialise l'�tat jouer, avec toutes les ressources n�c�ssaires
	*
	*/
	void init();

	/**
	* \brief	gestion de la saisie utilisateur
	*
	*gestion de la saisie utilisateur
	*
	*/
	void handleInput();

	/**
	* \brief	mise a jour de la logique de l'�tat jouer
	*
	*mise a jour de la logique de l'�tat jouer
	*
	* \param dt : temps que met une it�ration
	*/
	void update(float dt);

	/**
	* \brief	affiche l'�tat jouer
	*
	*Met � jour la position du joueur, G�re l'animation du joueur, G�re les collisions, Met � jour le sprite et le rectangle du joueur
	*
	* \param dt : temps que met une it�ration
	*/
	void draw(float dt);

private:

	//void pauseGame();
	/**
	* \brief	Centre la cam�ra sur le joueur
	*
	*Centre la cam�ra sur le joueur
	*
	*/
	void centerCamera();


	//void updateVectors();
	//void fireBullets();
	//void drawBullets();

	/**
	* \brief	Place les informations du joueur et de la partie � l'�cran, c'est le HUD
	*
	*Place les informations du joueur et de la partie � l'�cran, c'est le HUD
	*
	*/
	void positionHUD(Player& player);

	void spawnerPlayerCollision();

private:
	Database* db;/*!< Pointeur vers un objet database, permet la communication avec la BDD*/
	GameDataRef _data;/*!< donn�es communes aux �tats (fen�tre, �tat actuel)*/
	sf::View mCamera;/*!< Vue centr� sur le joueur*/

	RessourceHolder mRessources;/*!< Objet RessourceHolder, stock les textures et les fonts*/
	sf::Sprite mSpritePlayer;/*!< sprite du joueur*/
	sf::Vector2f mPosPlayer;/*!< Coordon�e de la position du joueur */
	Player mPlayer;/*!< Objet joueur*/

	//Dragon
	Enemy mDragon;/*!< Objet repr�sentant un dragon*/

	//Boules de feu
	Enemy mFireBall;/*!< */
	std::vector<Enemy> mFireBalls;/*!< */

	//Orcs
	Enemy mOrc;/*!< Objet orcs*/
	std::vector<Enemy> mOrcs;/*!< Vecteur d'objet orcs*/

	//Murs
	Wall mWall;/*!< Objet Wall, repr�sentant les tuiles murs*/
	std::vector<Wall> mWalls;/*!< vecteur de murs*/

	//Sols
	Wall mTile;/*!< Objet repr�sentant les tuiles sols*/
	std::vector<Wall> mGround;/*!< vecteur de tuiles, que l'on remplit avec les sprites sols*/

	//Zone de spawn
	Wall mSpawnTile;/*!< Tuile qui permet de faire apparaitre les orcs*/

	//HUD
	TextDisplay HPText;/*!< Vie du joueur*/
	TextDisplay EXPText;/*!< Exp du joueur*/
	TextDisplay currencyText;/*!< Argent du joueur*/
	TextDisplay levelText;/*!< Niveau du joueur*/
	TextDisplay potionText;/*!< nombre de potion*/
	TextDisplay buyingPotionText;/*!< touche qu'il faut utlisier pour acheter une potion*/
	TextDisplay buyingExpText;/*!< touche qu'il faut utlisier pour acheter 100 EXP*/

	sf::Music backGroundMusic;/*!< Musique de fond*/
	sf::SoundBuffer bufferFireBullet;/*!< buffer du son projecile*/
	sf::SoundBuffer bufferPlayerHit;/*!< buffer du son joueur touch�*/
	sf::Sound soundBullet;/*!< son projecile*/
	sf::Sound soundHit;/*!< son joueur touch�*/
};

