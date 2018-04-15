#include "database.h"
#include <stdio.h>
#include <cstring>
#include <iostream>

Database::Database()
{
	//ctor
	dbFile = "./database.db";
}

Database::~Database()
{
	delete db;
}

void Database::openDatabase()
{
	sqlite3_initialize();
	//Prend en param�tre un nom de fichier, et un pointeur vers le pointeur
	//Attention � convertir la chaine de caract�re en version C, c_str()
	sqlite3_open(dbFile.c_str(), &db);
}

void Database::closeDatabase()
{
	//Utilisation du close v2 !
	sqlite3_close_v2(db);
	sqlite3_shutdown();
}

bool Database::executeQuery(std::string query)
{
	//Met le pointeur � NULL
	char * errmsg = 0;

	//Version sans callback
	//3�me param�tre NULL
	if (sqlite3_exec(db, query.c_str(), NULL, 0, &errmsg) != SQLITE_OK)
	{
		std::cout << errmsg << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}


bool Database::insertPlayer(Player& player)
{
	//On cr�e des buffer pour stocker la chaine de carac�tre sous forme C
	char bMaxHP[100];
	char bAttackDamage[1000];
	char bLevel[100];
	char bCurrency[100];
	sprintf_s(bMaxHP, "%d", player.maxHP);
	sprintf_s(bAttackDamage, "%d", player.attackDamage);
	sprintf_s(bLevel, "%d", player.level);
	sprintf_s(bCurrency, "%d", player.currency);

	std::string query = "INSERT INTO Player VALUES (";

	query += "NULL";
	query += ",";
	query += bMaxHP;
	query += ",";
	query += bAttackDamage;
	query += ",";
	query += bLevel;
	query += ",";
	query += bCurrency;
	query += ")";

	std::cout << query << std::endl;

	return executeQuery(query);
}


std::vector<Player> Database::getAllPlayer()
{
	//Attention, bien regarde le rowid
	std::string query = "SELECT * FROM Player";
	std::vector<Player> players;
	int i;

	sqlite3_stmt * stmt;
	//strlen longueur de la taille du tableau
	//Tail on s'en fiche, on le met a null
	sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str()) + 1, &stmt, NULL);

	//Tant qu'il y a des donn�es, on les r�cup�res
	do {
		//Fonction step qui renvoi le signal "je suis ou pas dans une ligne"
		i = sqlite3_step(stmt);
		if (i == SQLITE_ROW)
		{
			Player player;
			players.push_back(player);

			//params, stmt et l'id de la 1�re colonne
			//R�cup�re l'id
			player.idPlayer = sqlite3_column_int(stmt, 0);
			player.maxHP = sqlite3_column_int(stmt, 1);
			player.attackDamage = sqlite3_column_double(stmt, 2);
			player.level = sqlite3_column_int(stmt, 3);
			player.currency = sqlite3_column_int(stmt, 4);
		}
		else
		{
			std::cout << "no rows" << std::endl;
		}
	} while (i == SQLITE_ROW); //Tant qu'il y a des donn�es, on it�re !

	return players;
}
/*
bool Database::updatePlayer(Player* player)
{
	std::string query = "UPDATE produits SET nom=?, prix=?, qtevendue=? WHERE rowid=?";
	sqlite3_stmt * stmt;
	sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str()) + 1, &stmt, NULL);

	//Cr�ation des bind, comme en csharp, on remplace les ? par les valeurs
	sqlite3_bind_text(stmt, 1, player->nom.c_str(), strlen(produit->nom.c_str()), 0);
	sqlite3_bind_double(stmt, 2, player->prix);
	sqlite3_bind_int(stmt, 3, player->qteVendue);
	sqlite3_bind_int(stmt, 4, player->id);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return true;
}

bool Database::deletePlayer(int id)
{
	std::string query = "DELETE FROM produits WHERE rowid=?";
	sqlite3_stmt * stmt;
	sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str()) + 1, &stmt, NULL);

	//Bind
	sqlite3_bind_int(stmt, 1, id);

	//Execute
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return true;

}
*/
