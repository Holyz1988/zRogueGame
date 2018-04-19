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
* \brief		Classe contenant la logique et les caract�ristiques du joueur
*
* \details		Classe contenant la logique et les caract�ristiques du joueur
*/



class Enemy;


/*! \class		Player
* \brief		Classe contenant la logique et les caract�ristiques du joueur
*
* \details		Classe contenant la logique et les caract�ristiques du joueur
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
	* \brief	Met � jour toute la logique du joueur
	*
	*Met � jour toute la logique du joueur
	*
	* \param dt : Temps que met une it�ration
	* \param walls : toutes les tuiles qui repr�sente les murs, le d�cors et le spawner
	*/
	void update(float dt, std::vector<Wall>& walls);

	/**
	* \brief	Lorsque l'on clique gauche sur la souris, on charge les projectiles dans un vecteur
	*
	*Lorsque l'on clique gauche sur la souris, on charge les projectiles dans un vecteur
	*
	* \param window : Fen�tre dans laquelle on d�ssine
	* \param walls : toutes les tuiles qui repr�sente les murs, le d�cors et le spawner
	* \param sound : son d'effet des projectiles joueur
	*/
	void fireBullets(sf::RenderWindow& window, std::vector<Wall> walls, sf::Sound& sound);

	/**
	* \brief	On d�ssine les projectiles joueur � l'�cran
	*
	*On d�ssine les projectiles joueur � l'�cran
	*
	* \param window : Fen�tre dans laquelle on d�ssine
	*/
	void drawBullets(sf::RenderWindow& window);

	/**
	* \brief	On d�ssine les points de vies perdus � l'�cran
	*
	*On d�ssine les points de vies perdus � l'�cran
	*
	* \param window : r�f�rence vers une Fen�tre dans laquelle on d�ssine
	*/
	void drawHpLost(sf::RenderWindow& window);

	/**
	* \brief	Met � jour la position des HP perdu des mobs
	*
	*Met � jour la position des HP perdu des mobs
	*
	* \param dt : temps entre chaque it�ration
	*/
	void updateTextDamage(float dt);

	/**
	* \brief	Permet de calculer la direction normalis�
	*
	*Permet de calculer la direction normalis�
	*
	* \param window : Fen�tre dans laquelle on d�ssine
	*/
	void updateVectors(sf::RenderWindow& window);

	/**
	* \brief	Permet de retirer l'invuln�rabilit�
	*
	*Permet de retirer l'invuln�rabilit�
	*
	*/
	void resetInvulnerableTimer();

	
	/**
	* \brief	actionne le spawn des mobs
	*
	*actionne le spawn des mobs
	*
	* \param spawnTile : Tuile qui repr�sente l'endroit ou il faut se mettre pour fait apparaitre les monstres
	*/
	void spawnOrcs(Wall& spawnTile);

	/**
	* \brief	Efface la boule de feu flottante s'il y a collision
	*
	*Efface la boule de feu flottante s'il y a collision
	*
	* \param enemies : r�f�rence vers un vecteur d'�nnemis
	*/
	void fireBallPlayerCollision(std::vector<Enemy>& enemies);

	/**
	* \brief	Efface la boule de feu flottante s'il y a collision
	*
	*Efface la boule de feu flottante s'il y a collision
	*
	* \param enemy : r�f�rence vers un vecteur d'�nnemis
	* \param sound : r�f�rence vers un son
	*/
	void losingHpToFireBall(std::vector<Enemy>& enemy, sf::Sound& sound);

	/**
	* \brief	Collision mur et tir du joueur
	*
	*Collision mur et tir du joueur
	*
	* \param walls : mur de l'ar�ne
	*/
	void bulletWallCollision(std::vector<Wall>& walls);

	/**
	* \brief	Test si il y a une collision entre un ennemi et le joueur
	*
	*Test si il y a une collision entre un ennemi et le joueur
	*
	* \param enemy : Boule de feu 
	*
	* \return un bool�en qui nous informe si la collision a eu lieu ou non
	*/
	bool fireBallCollision(Enemy& enemy);

	/**
	* \brief	Test si il y a une collision entre un mur et les projectiles
	*
	*Test si il y a une collision entre un mur et les projectiles
	*
	* \param wall : Boule de feu
	*
	* \return un bool�en qui nous informe si la collision a eu lieu ou non
	*/
	bool collisionBulletWall(Wall& wall);

	/**
	* \brief	Collision entre tous les murs de l'ar�ne et le joueur
	*
	*Collision entre tous les murs de l'ar�ne et le joueur
	*
	* \param walls : mur de l'ar�ne
	* \param previousPos : coordonn� de la position pr�c�dante du joueur
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
	* \brief	Mont�e en niveau du joueur
	*
	*Mont�e en niveau du joueur
	*
	*/
	void levelUp();

	/**
	* \brief	Test si le joueur est mort ou non
	*
	*Test si le joueur est mort ou non
	*
	* \return bool�en qui nous informe du succ�s ou non de la mort
	*/
	bool isDead();

	/**
	* \brief	Met � jour les hp lors d'une mont�e de niveau
	*
	*Met � jour les hp lors d'une mont�e de niveau
	*
	*/
	void updateHP();

	//Accesseurs
	/**
	* \brief	Getter
	*
	*Getter
	*
	* \return entier repr�sentant les d�gats
	*/

	int getDamage();
	/**
	* \brief	Getter
	*
	*Getter
	*
	* \return entier repr�sentant les points de vies
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
	* \return le bool�en qui nous informe sur le spawner
	*/
	bool getSpawnerStatus();

	/**
	* \brief	Getter
	*
	*Getter
	*
	* \return un flottant qui repr�sente le temps entre chaque tire du joueur
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
	* \param damage : nouveau d�gats
	*/
	void setDamage(int damage);

	/**
	* \brief	Setter
	*
	*Setter
	*
	* \param bulletDelaly : d�lai entre chaque tire du joueur
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
	int mCurrentExperience;/*!< Exp�rience actuelle*/
	int mExperienceNeeded;/*!< Exp�rience n�c�ssaire � la mont�e d'un niveau*/
	int idPlayer;/*!< Identifiant joueur*/

	TextDisplay hpOrcLost;/*!< texte contenant les d�gats recu par l'orc*/
	std::vector<TextDisplay> vectorHpOrcLost;/*!< vecteur contenant les textes avec les d�gats recu par l'orc*/

	Items potion;/*!< Potion du joueur*/

private:
	sf::Vector2f mPlayerCenter/*!< Coordonn�es du centre de la position du joueur*/;
	sf::Vector2f mMouseWorldPosition;/*!< Position de la souris sur le monde*/
	sf::Vector2i mMousePixelPosition;/*!< Position de la souris sur la vue*/
	sf::Vector2f mAimDirection;/*!< Direction vers laquelle on veut faire feu*/
	sf::Vector2f mAimDirectionNormalized;/*!< Direction normalis� vers laquelle on veut faire feu*/

	Projectile mBullet;/*!< Projectile joueur*/
	std::vector<Projectile> mBullets;/*!< tous les projectiles joueur*/

	// Horloge
	sf::Clock mBulletClock;/*!< Horloge des projectiles*/
	sf::Clock invulnerableClock;/*!< Horloge de l'invuln�rabilit�*/
	sf::Clock clock; /*!< Horloge du joueur*/
	float mTimeAccumulator;/*!< Temps accumul� entre chaque it�ration*/
	float mBulletDelay;/*!< Temps entre chaque projectile tir�*/

	float timePassed;/*!< Temps �couler*/ 
	float switchTime = 0.3f;/*!< Temps que prend une frame d'animation*/ 
	int currentFrame = 0;/*!< On commence � la 1�re frame*/ 

	float invulnerableTimer;/*!< chrono de l'invuln�rabilit�*/

	//Stats
	bool invulnerable;/*!< Bool�en qui nous informe sur l'invuln�rabilit� du joueur*/
};

