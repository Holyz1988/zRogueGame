#pragma once
#include "sqlite3.h"
#include "Player.h"
#include <string>
#include <vector>

/**
* \file			Database.h
* \author		Amine ZEGHAD
* \version		1.0
* \date			19 april 2018
* \brief		Communication avec la base de donn�e SQLite
*
* \details		Fichier contenant les m�thodes n�cessaires pour la communication avec la base de donn�e 
*
*/

/*! \class Database
* \brief		Communication avec la base de donn�e SQLite
*
* \details		Class contenant les m�thodes n�cessaires pour la communication avec la base de donn�e 
*
*/
class Database
{
public:
	/**
	* \brief		Constructeur
	*
	*Constructeur de la classe Database
	*
	*/
	Database();

	/**
	* \brief		Destructeur
	*
	*Destructeur de la classe Database
	*
	*/
	virtual ~Database();

	/**
	* \brief		Ouvre la connexion � la BDD
	*
	*Ouvre la connexion � la BDD
	*
	*/
	void openDatabase();

	/**
	* \brief		Ferme la connexion � la BDD
	*
	*Ouvre la connexion � la BDD
	*
	*/
	void closeDatabase();

	/**
	* \brief		Execute une requ�te SQL
	*
	*Execute une requ�te SQL
	*
	* \param query : chaine de caract�res contenant la requ�te SQL � �x�cuter
	*
	* \return Un bool�en qui nous informe si la requ�te s'est bien �x�cut� ou pas
	*/
	bool executeQuery(std::string query);
	
	/**
	* \brief		Insert un joueur en BDD
	*
	*Insert un joueur en BDD
	*
	* \param player : stock tout ce qui compose un joueur que l'on va ins�rer en BDD
	*
	* \return Un bool�en qui nous informe si la requ�te s'est bien �x�cut� ou pas
	*/
	bool insertPlayer(Player& player);

	/**
	* \brief		R�cup�re tous les joueurs stock�s en BDD
	*
	*R�cup�re tous les joueurs stock�s en BDD
	*
	* \return Un vecteur contenant les joueurs sauvegard�s en BDD
	*/
	std::vector<Player> getAllPlayer();

	/**
	* \brief		R�cup�re un joueur stock� en BDD
	*
	*R�cup�re un joueur stock� en BDD grace � son identifiant
	*
	* \param id : identifiant du joueur
	*
	* \return Le joueur stock� en BDD et dont l'id correspond
	*/
	Player getPlayer(int id);

	/**
	* \brief		R�cup�re l'identifiant du joueur
	*
	*R�cup�re l'identifiant du joueur en BDD
	*
	* \return L'identifiant du joueur
	*/
	int getPlayerNumber();
	
	/**
	* \brief		Met � jour les statistiques du joueur
	*
	*Met � jour les statistiques du joueur en BDD
	*
	* \param player : r�f�rence de l'objet joueur
	*
	* \return Un bool�en qui nous informe du succ�s ou non de la requ�te
	*/
	bool updatePlayer(Player& player);

	/**
	* \brief		Ecrase une partie
	*
	*Mise � jour en base de donn�es avec les statistiques par d�faut du joueur, ce qui va "cr�er" un nouveau joueur
	*
	* \param id : identifiant du joueur
	*
	* \return Un bool�en qui nous informe du succ�s ou non de la requ�te
	*/
	bool resetPlayer(int id);
	
	

private:
	sqlite3 * db;/*!< Pointeur de type sqlite3*/
	std::string dbFile;/*!< Nom de la base de donn�e cr�e*/
};

