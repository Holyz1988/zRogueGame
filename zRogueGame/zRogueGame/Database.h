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
* \brief		Communication avec la base de donnée SQLite
*
* \details		Fichier contenant les méthodes nécessaires pour la communication avec la base de donnée 
*
*/

/*! \class Database
* \brief		Communication avec la base de donnée SQLite
*
* \details		Class contenant les méthodes nécessaires pour la communication avec la base de donnée 
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
	* \brief		Ouvre la connexion à la BDD
	*
	*Ouvre la connexion à la BDD
	*
	*/
	void openDatabase();

	/**
	* \brief		Ferme la connexion à la BDD
	*
	*Ouvre la connexion à la BDD
	*
	*/
	void closeDatabase();

	/**
	* \brief		Execute une requête SQL
	*
	*Execute une requête SQL
	*
	* \param query : chaine de caractères contenant la requête SQL à éxécuter
	*
	* \return Un booléen qui nous informe si la requête s'est bien éxécuté ou pas
	*/
	bool executeQuery(std::string query);
	
	/**
	* \brief		Insert un joueur en BDD
	*
	*Insert un joueur en BDD
	*
	* \param player : stock tout ce qui compose un joueur que l'on va insérer en BDD
	*
	* \return Un booléen qui nous informe si la requête s'est bien éxécuté ou pas
	*/
	bool insertPlayer(Player& player);

	/**
	* \brief		Récupère tous les joueurs stockés en BDD
	*
	*Récupère tous les joueurs stockés en BDD
	*
	* \return Un vecteur contenant les joueurs sauvegardés en BDD
	*/
	std::vector<Player> getAllPlayer();

	/**
	* \brief		Récupère un joueur stocké en BDD
	*
	*Récupère un joueur stocké en BDD grace à son identifiant
	*
	* \param id : identifiant du joueur
	*
	* \return Le joueur stocké en BDD et dont l'id correspond
	*/
	Player getPlayer(int id);

	/**
	* \brief		Récupère l'identifiant du joueur
	*
	*Récupère l'identifiant du joueur en BDD
	*
	* \return L'identifiant du joueur
	*/
	int getPlayerNumber();
	
	/**
	* \brief		Met à jour les statistiques du joueur
	*
	*Met à jour les statistiques du joueur en BDD
	*
	* \param player : référence de l'objet joueur
	*
	* \return Un booléen qui nous informe du succès ou non de la requête
	*/
	bool updatePlayer(Player& player);

	/**
	* \brief		Ecrase une partie
	*
	*Mise à jour en base de données avec les statistiques par défaut du joueur, ce qui va "créer" un nouveau joueur
	*
	* \param id : identifiant du joueur
	*
	* \return Un booléen qui nous informe du succès ou non de la requête
	*/
	bool resetPlayer(int id);
	
	

private:
	sqlite3 * db;/*!< Pointeur de type sqlite3*/
	std::string dbFile;/*!< Nom de la base de donnée crée*/
};

