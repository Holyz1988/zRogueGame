#pragma once
#include "Character.h"
#include "RessourceHolder.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Wall.h"
#include "TextDisplay.h"
#include "SFML\Audio.hpp"
#include "Items.h"

/**
* \file			Player.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Classe contenant la logique et les caractéristiques du joueur
*
* \details		Classe contenant la logique et les caractéristiques du joueur
*/



class Enemy;


/*! \class		Player
* \brief		Classe contenant la logique et les caractéristiques du joueur
*
* \details		Classe contenant la logique et les caractéristiques du joueur
*
*/
class Player : public Character	
{
public:
	/**
	* \brief	Constructeur
	*
	*Constructeur de la classe Player
	*
	*/
	Player();

	/**
	* \brief	Met à jour toute la logique du joueur
	*
	*Met à jour toute la logique du joueur
	*
	* \param dt : Temps que met une itération
	* \param walls : toutes les tuiles qui représente les murs, le décors et le spawner
	*/
	void update(float dt, std::vector<Wall>& walls);

	/**
	* \brief	Lorsque l'on clique gauche sur la souris, on charge les projectiles dans un vecteur
	*
	*Lorsque l'on clique gauche sur la souris, on charge les projectiles dans un vecteur
	*
	* \param window : Fenêtre dans laquelle on déssine
	* \param walls : toutes les tuiles qui représente les murs, le décors et le spawner
	* \param sound : son d'effet des projectiles joueur
	*/
	void fireBullets(sf::RenderWindow& window, std::vector<Wall> walls, sf::Sound& sound);

	/**
	* \brief	On déssine les projectiles joueur à l'écran
	*
	*On déssine les projectiles joueur à l'écran
	*
	* \param window : Fenêtre dans laquelle on déssine
	*/
	void drawBullets(sf::RenderWindow& window);

	/**
	* \brief	On déssine les points de vies perdus à l'écran
	*
	*On déssine les points de vies perdus à l'écran
	*
	* \param window : référence vers une Fenêtre dans laquelle on déssine
	*/
	void drawHpLost(sf::RenderWindow& window);

	/**
	* \brief	Met à jour la position des HP perdu des mobs
	*
	*Met à jour la position des HP perdu des mobs
	*
	* \param dt : temps entre chaque itération
	*/
	void updateTextDamage(float dt);

	/**
	* \brief	Permet de calculer la direction normalisé
	*
	*Permet de calculer la direction normalisé
	*
	* \param window : Fenêtre dans laquelle on déssine
	*/
	void updateVectors(sf::RenderWindow& window);

	/**
	* \brief	Permet de retirer l'invulnérabilité
	*
	*Permet de retirer l'invulnérabilité
	*
	*/
	void resetInvulnerableTimer();

	
	/**
	* \brief	actionne le spawn des mobs
	*
	*actionne le spawn des mobs
	*
	* \param spawnTile : Tuile qui représente l'endroit ou il faut se mettre pour fait apparaitre les monstres
	*/
	void spawnOrcs(Wall& spawnTile);

	/**
	* \brief	Efface la boule de feu flottante s'il y a collision
	*
	*Efface la boule de feu flottante s'il y a collision
	*
	* \param enemies : référence vers un vecteur d'énnemis
	*/
	void fireBallPlayerCollision(std::vector<Enemy>& enemies);

	/**
	* \brief	Efface la boule de feu flottante s'il y a collision
	*
	*Efface la boule de feu flottante s'il y a collision
	*
	* \param enemy : référence vers un vecteur d'énnemis
	* \param sound : référence vers un son
	*/
	void losingHpToFireBall(std::vector<Enemy>& enemy, sf::Sound& sound);

	/**
	* \brief	Collision mur et tir du joueur
	*
	*Collision mur et tir du joueur
	*
	* \param walls : mur de l'arène
	*/
	void bulletWallCollision(std::vector<Wall>& walls);

	/**
	* \brief	Test si il y a une collision entre un ennemi et le joueur
	*
	*Test si il y a une collision entre un ennemi et le joueur
	*
	* \param enemy : Boule de feu 
	*
	* \return un booléen qui nous informe si la collision a eu lieu ou non
	*/
	bool fireBallCollision(Enemy& enemy);

	/**
	* \brief	Test si il y a une collision entre un mur et les projectiles
	*
	*Test si il y a une collision entre un mur et les projectiles
	*
	* \param wall : Boule de feu
	*
	* \return un booléen qui nous informe si la collision a eu lieu ou non
	*/
	bool collisionBulletWall(Wall& wall);

	/**
	* \brief	Collision entre tous les murs de l'arène et le joueur
	*
	*Collision entre tous les murs de l'arène et le joueur
	*
	* \param walls : mur de l'arène
	* \param previousPos : coordonné de la position précédante du joueur
	*/
	void wallCollision(std::vector<Wall>& walls, sf::Vector2f previousPos);

	/**
	* \brief	Collision entre les orcs et les projectiles joueur
	*
	*Collision entre les orcs et les projectiles joueur
	*
	* \param orcs : vecteur contenant tous les orcs
	*/
	void bulletOrcCollision(std::vector<Enemy>& orcs);

	/**
	* \brief	Perte de points de vies du joueur et changement de couleur
	*
	*Perte de points de vies du joueur et changement de couleur
	*
	* \param enemy : vecteur contenant tous les enemies
	* \param sound : son d'ambiance des projectiles joueurs
	*/
	void losingHp(std::vector<Enemy>& enemy, sf::Sound& sound);

	/**
	* \brief	Montée en niveau du joueur
	*
	*Montée en niveau du joueur
	*
	*/
	void levelUp();

	/**
	* \brief	Test si le joueur est mort ou non
	*
	*Test si le joueur est mort ou non
	*
	* \return booléen qui nous informe du succès ou non de la mort
	*/
	bool isDead();

	/**
	* \brief	Met à jour les hp lors d'une montée de niveau
	*
	*Met à jour les hp lors d'une montée de niveau
	*
	*/
	void updateHP();

	//Accesseurs
	/**
	* \brief	Getter
	*
	*Getter
	*
	* \return entier représentant les dégats
	*/

	int getDamage();
	/**
	* \brief	Getter
	*
	*Getter
	*
	* \return entier représentant les points de vies
	*/
	int getCurrentHP();

	/**
	* \brief	Getter
	*
	*Getter
	*
	* \return le conteneur de projectiles
	*/
	std::vector<Projectile> getBullets();

	/**
	* \brief	Getter
	*
	*Getter
	*
	* \return le booléen qui nous informe sur le spawner
	*/
	bool getSpawnerStatus();

	/**
	* \brief	Getter
	*
	*Getter
	*
	* \return un flottant qui représente le temps entre chaque tire du joueur
	*/
	float getBulletDelay();

	/**
	* \brief	Getter
	*
	*Getter
	*
	* \return Projectile du joueur
	*/
	Projectile getBullet();

	//Setters

	/**
	* \brief	Setter
	*
	*Setter
	*
	* \param damage : nouveau dégats
	*/
	void setDamage(int damage);

	/**
	* \brief	Setter
	*
	*Setter
	*
	* \param bulletDelaly : délai entre chaque tire du joueur
	*/
	void setBulletDelay(float bulletDelaly);

	/**
	* \brief	Setter
	*
	*Setter
	*
	* \param bulletRadius : taille du projectile joueur
	*/
	void setBulletRadius(float bulletRadius);

	bool mSpawnerStatus;/*!< Etat du spawner de mob*/
	int mCurrentExperience;/*!< Expérience actuelle*/
	int mExperienceNeeded;/*!< Expérience nécéssaire à la montée d'un niveau*/
	int idPlayer;/*!< Identifiant joueur*/

	TextDisplay hpOrcLost;/*!< texte contenant les dégats recu par l'orc*/
	std::vector<TextDisplay> vectorHpOrcLost;/*!< vecteur contenant les textes avec les dégats recu par l'orc*/

	Items potion;/*!< Potion du joueur*/

private:
	sf::Vector2f mPlayerCenter/*!< Coordonnées du centre de la position du joueur*/;
	sf::Vector2f mMouseWorldPosition;/*!< Position de la souris sur le monde*/
	sf::Vector2i mMousePixelPosition;/*!< Position de la souris sur la vue*/
	sf::Vector2f mAimDirection;/*!< Direction vers laquelle on veut faire feu*/
	sf::Vector2f mAimDirectionNormalized;/*!< Direction normalisé vers laquelle on veut faire feu*/

	Projectile mBullet;/*!< Projectile joueur*/
	std::vector<Projectile> mBullets;/*!< tous les projectiles joueur*/

	// Horloge
	sf::Clock mBulletClock;/*!< Horloge des projectiles*/
	sf::Clock invulnerableClock;/*!< Horloge de l'invulnérabilité*/
	sf::Clock clock; /*!< Horloge du joueur*/
	float mTimeAccumulator;/*!< Temps accumulé entre chaque itération*/
	float mBulletDelay;/*!< Temps entre chaque projectile tiré*/

	float timePassed;/*!< Temps écouler*/ 
	float switchTime = 0.3f;/*!< Temps que prend une frame d'animation*/ 
	int currentFrame = 0;/*!< On commence à la 1ère frame*/ 

	float invulnerableTimer;/*!< chrono de l'invulnérabilité*/

	//Stats
	bool invulnerable;/*!< Booléen qui nous informe sur l'invulnérabilité du joueur*/
};

