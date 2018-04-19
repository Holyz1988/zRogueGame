#pragma once
#include "Character.h"
#include "RessourceHolder.h"
#include "Player.h"
#include "Wall.h"

/**
* \file			Enemy.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Class contenant tout la logique et les caractériques énemies
*
* \details		Class contenant tout la logique et les caractériques énemies
*
*/

class Player;

/*! \class		Enemy
* \brief		Classe contenant toute la logique et les caractériques énemies
*
* \details		Classe contenant toute la logique et les caractériques énemies
*
*/
class Enemy : public Character
{
public:
	enum Direction { DOWN = 1, LEFT, RIGHT, TOP };

	/**
	* \brief		Constructeur
	*
	*Constructeur de la classe Enemy
	*
	*/
	Enemy();

	/**
	* \brief		Constructeur
	*
	*Constructeur de la classe Enemy
	*
	* /param player : référence de l'objet joueur
	*/
	Enemy(Player& player);
	//Enemy(sf::Vector2f velocity);

	/**
	* \brief		Permet de définir la trajectoire des boules de feu
	*
	*Permet de définir la trajectoire des boules de feu qui se déplace vers l'axe X du joueur lors de l'apparition de la boule
	*
	* \param enemies : référence du vecteur d'énemies à faire bouger
	* \param window : référence de la fenêtre sur laquel on déssine
	* \param dt : deltaTime, le temps mis entre chaque itération
	*/
	void updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow& window, float dt);

	/**
	* \brief		Fait apparaitre les boules de feu
	*
	*Fait apparaitre les boules de feu
	*
	* \param enemies : référence du vecteur de boules de feu
	* \param enemy : référence de l'énemi à insérer dans le vecteur
	* \param player : référence du joueur, pour récupérer sa position
	*/
	void spawnFireBalls(std::vector<Enemy>& enemies, Enemy& enemy, Player& player);

	/**
	* \brief		Déssines les énemies
	*
	*Déssines les énemies
	*
	* \param enemies : référence du vecteur d'énemies à déssiner
	* \param enemy : référence de la fenêtre sur laquelle on veut déssiner
	*/
	void drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow& window);

	/**
	* \brief		Gestion de la collision entre un énemie et un mur
	*
	*Gestion de la collision entre un énemie et un mur
	*
	* \param enemies : référence du vecteur de mur sur lequel on vérifie s'il y a collision
	* \param previousPos : position du joueur lors de l'itération précédente
	*/
	void wallCollision(std::vector<Wall>& walls, sf::Vector2f previousPos);

	/**
	* \brief		Met à jour la position du personnage enemie
	*
	*Met à jour la position du sprite du rectangle enemie, pour qu'ils ne fassent plus qu'un
	*
	*/
	void updatePos();

	/**
	* \brief		Met à jour les vecteurs qui permettent de calculer les divers positions
	*
	*Met à jour les vecteurs qui permettent de calculer les divers positions
	*
	*/
	void updateV(Player& player);
	
	/**
	* \brief		Mouvement énemies
	*
	*Gestion des mouvements enemies à chaque itération, c'est l'IA des monstres
	*
	* \param dt : deltaTime, le temps mis entre chaque itération
	* \param walls : référence vers le vecteur de murs
	*/
	void moveEnemies(float dt, std::vector<Wall>& walls);

	/**
	* \brief		Apparition des énemies
	*
	*Fait apparaître les enemies à l'écran
	*
	* \param enemies : référence vers le vecteur d'énemies
	* \param enemie : référence de l'énemie à rajouter au vecteur d'énemies
	*/
	void Enemy::spawEnemies(std::vector<Enemy>& enemies, Enemy& enemy);

	//GETTER & SETTER
	/**
	* \brief		SETTER
	*
	*Permet de changer le vecteur vitesse de l'énemie
	*
	* \param velocity : nouveau vecteur vitesse
	*/
	void setVelocity(sf::Vector2f velocity);

	/**
	* \brief		GETTER
	*
	*Récupère le vecteur vitesse 
	*
	* \return vecteur vitesse de l'énemie
	*/
	sf::Vector2f getVelocity();

	/**
	* \brief		GETTER
	*
	*Récupère les dégats
	*
	* \return entier représentant les dégats
	*/
	int getDamage();
	int experienceGiven;/*!< Experience donné au joueur lors de la mors*/

private:
	sf::Clock clock;/*!< horloge énemie*/
	sf::Clock clockOrc;/*!< horloge orc*/
	
	sf::Vector2f mVelocity;/*!< vecteur vitesse*/
	float mSpeed; /*!< vitesse de déplacement*/

	sf::Vector2f playerCenter;/*!< coordonné du center du joueur*/
	sf::Vector2f aimDirection;/*!< Direction de la visée*/
	sf::Vector2f aimDirectionNormalized;/*!< Direction de la visée sous forme normalisé*/

	Direction mDirection = Direction::DOWN;/*!< Direction vers laquelle l'énemie fait face, par défaut, en bas*/

	float timePassed; /*!< Temps écouler*/
	int currentFrame; /*!< Itération actuel*/// 
	float switchTime; /*!< Temps que prend une itération d'animation*/

	int direction;/*!< direction sous forme d'entier*/

	float timeWalking;/*!< Temps de marche d'un orc*/
	int mSpawnCounter;/*!< Compteur qui permet la gestion de l'appation des boules de feux*/
};

