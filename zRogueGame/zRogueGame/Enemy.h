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
* \brief		Class contenant tout la logique et les caract�riques �nemies
*
* \details		Class contenant tout la logique et les caract�riques �nemies
*
*/

class Player;

/*! \class		Enemy
* \brief		Classe contenant toute la logique et les caract�riques �nemies
*
* \details		Classe contenant toute la logique et les caract�riques �nemies
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
	* /param player : r�f�rence de l'objet joueur
	*/
	Enemy(Player& player);
	//Enemy(sf::Vector2f velocity);

	/**
	* \brief		Permet de d�finir la trajectoire des boules de feu
	*
	*Permet de d�finir la trajectoire des boules de feu qui se d�place vers l'axe X du joueur lors de l'apparition de la boule
	*
	* \param enemies : r�f�rence du vecteur d'�nemies � faire bouger
	* \param window : r�f�rence de la fen�tre sur laquel on d�ssine
	* \param dt : deltaTime, le temps mis entre chaque it�ration
	*/
	void updateMovement(std::vector<Enemy>& enemies, sf::RenderWindow& window, float dt);

	/**
	* \brief		Fait apparaitre les boules de feu
	*
	*Fait apparaitre les boules de feu
	*
	* \param enemies : r�f�rence du vecteur de boules de feu
	* \param enemy : r�f�rence de l'�nemi � ins�rer dans le vecteur
	* \param player : r�f�rence du joueur, pour r�cup�rer sa position
	*/
	void spawnFireBalls(std::vector<Enemy>& enemies, Enemy& enemy, Player& player);

	/**
	* \brief		D�ssines les �nemies
	*
	*D�ssines les �nemies
	*
	* \param enemies : r�f�rence du vecteur d'�nemies � d�ssiner
	* \param enemy : r�f�rence de la fen�tre sur laquelle on veut d�ssiner
	*/
	void drawEnemies(std::vector<Enemy>& enemies, sf::RenderWindow& window);

	/**
	* \brief		Gestion de la collision entre un �nemie et un mur
	*
	*Gestion de la collision entre un �nemie et un mur
	*
	* \param enemies : r�f�rence du vecteur de mur sur lequel on v�rifie s'il y a collision
	* \param previousPos : position du joueur lors de l'it�ration pr�c�dente
	*/
	void wallCollision(std::vector<Wall>& walls, sf::Vector2f previousPos);

	/**
	* \brief		Met � jour la position du personnage enemie
	*
	*Met � jour la position du sprite du rectangle enemie, pour qu'ils ne fassent plus qu'un
	*
	*/
	void updatePos();

	/**
	* \brief		Met � jour les vecteurs qui permettent de calculer les divers positions
	*
	*Met � jour les vecteurs qui permettent de calculer les divers positions
	*
	*/
	void updateV(Player& player);
	
	/**
	* \brief		Mouvement �nemies
	*
	*Gestion des mouvements enemies � chaque it�ration, c'est l'IA des monstres
	*
	* \param dt : deltaTime, le temps mis entre chaque it�ration
	* \param walls : r�f�rence vers le vecteur de murs
	*/
	void moveEnemies(float dt, std::vector<Wall>& walls);

	/**
	* \brief		Apparition des �nemies
	*
	*Fait appara�tre les enemies � l'�cran
	*
	* \param enemies : r�f�rence vers le vecteur d'�nemies
	* \param enemie : r�f�rence de l'�nemie � rajouter au vecteur d'�nemies
	*/
	void Enemy::spawEnemies(std::vector<Enemy>& enemies, Enemy& enemy);

	//GETTER & SETTER
	/**
	* \brief		SETTER
	*
	*Permet de changer le vecteur vitesse de l'�nemie
	*
	* \param velocity : nouveau vecteur vitesse
	*/
	void setVelocity(sf::Vector2f velocity);

	/**
	* \brief		GETTER
	*
	*R�cup�re le vecteur vitesse 
	*
	* \return vecteur vitesse de l'�nemie
	*/
	sf::Vector2f getVelocity();

	/**
	* \brief		GETTER
	*
	*R�cup�re les d�gats
	*
	* \return entier repr�sentant les d�gats
	*/
	int getDamage();
	int experienceGiven;/*!< Experience donn� au joueur lors de la mors*/

private:
	sf::Clock clock;/*!< horloge �nemie*/
	sf::Clock clockOrc;/*!< horloge orc*/
	
	sf::Vector2f mVelocity;/*!< vecteur vitesse*/
	float mSpeed; /*!< vitesse de d�placement*/

	sf::Vector2f playerCenter;/*!< coordonn� du center du joueur*/
	sf::Vector2f aimDirection;/*!< Direction de la vis�e*/
	sf::Vector2f aimDirectionNormalized;/*!< Direction de la vis�e sous forme normalis�*/

	Direction mDirection = Direction::DOWN;/*!< Direction vers laquelle l'�nemie fait face, par d�faut, en bas*/

	float timePassed; /*!< Temps �couler*/
	int currentFrame; /*!< It�ration actuel*/// 
	float switchTime; /*!< Temps que prend une it�ration d'animation*/

	int direction;/*!< direction sous forme d'entier*/

	float timeWalking;/*!< Temps de marche d'un orc*/
	int mSpawnCounter;/*!< Compteur qui permet la gestion de l'appation des boules de feux*/
};

