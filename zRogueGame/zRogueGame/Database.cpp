#include "database.h"
#include <stdio.h>
#include <cstring>

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
	//Prend en paramètre un nom de fichier, et un pointeur vers le pointeur
	//Attention à convertir la chaine de caractère en version C, c_str()
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
	//Met le pointeur à NULL
	char * errmsg = 0;

	//Version sans callback
	//3ème paramètre NULL
	if (sqlite3_exec(db, query.c_str(), NULL, 0, &errmsg) != SQLITE_OK)
	{
		//std::cout << errmsg << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}


bool Database::insertPlayer(Player& player)
{
	//On crée des buffer pour stocker la chaine de caracètre sous forme C
	char bMaxHP[100];
	char bAttackDamage[1000];
	char bLevel[100];
	char bCurrency[100];
	char bCurrentXP[100];
	char bExpNeeded[100];
	char bBulletRadius[100];
	char bBulletDelay[100];
	char bPotionQty[100];
	sprintf_s(bMaxHP, "%d", player.maxHP);
	sprintf_s(bAttackDamage, "%d", player.attackDamage);
	sprintf_s(bLevel, "%d", player.level);
	sprintf_s(bCurrency, "%d", player.currency);
	sprintf_s(bCurrentXP, "%d", player.mCurrentExperience);
	sprintf_s(bExpNeeded, "%d", player.mExperienceNeeded);
	sprintf_s(bBulletRadius, "%f", player.getBullet().circle.getRadius());
	sprintf_s(bBulletDelay, "%f", player.getBulletDelay());
	sprintf_s(bPotionQty, "%d", player.getBulletDelay());

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
	query += ",";
	query += bCurrentXP;
	query += ",";
	query += bExpNeeded;
	query += ",";
	query += bBulletRadius;
	query += ",";
	query += bBulletDelay;
	query += ",";
	query += bPotionQty;
	query += ")";

	//std::cout << query << std::endl;

	return executeQuery(query);
}


int Database::getPlayerNumber()
{
	//Attention, bien regarde le rowid
	std::string query = "SELECT count(*) FROM Player";
	int i;
	int count;

	sqlite3_stmt * stmt;
	//strlen longueur de la taille du tableau
	//Tail on s'en fiche, on le met a null
	sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str()) + 1, &stmt, NULL);

	//Tant qu'il y a des données, on les récupères
	do {
		//Fonction step qui renvoi le signal "je suis ou pas dans une ligne"
		i = sqlite3_step(stmt);
		if (i == SQLITE_ROW)
		{
			//params, stmt et l'id de la 1ère colonne
			//Récupère l'id
			count = sqlite3_column_int(stmt, 0);
		}
		else
		{
			//std::cout << "no rows" << std::endl;
		}
	} while (i == SQLITE_ROW); //Tant qu'il y a des données, on itère !

	return count;
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

	//Tant qu'il y a des données, on les récupères
	do {
		//Fonction step qui renvoi le signal "je suis ou pas dans une ligne"
		i = sqlite3_step(stmt);
		if (i == SQLITE_ROW)
		{
			Player player;

			//params, stmt et l'id de la 1ère colonne
			//Récupère l'id
			player.idPlayer = sqlite3_column_int(stmt, 0);
			player.maxHP = sqlite3_column_int(stmt, 1);
			player.attackDamage = sqlite3_column_int(stmt, 2);
			player.level = sqlite3_column_int(stmt, 3);
			player.currency = sqlite3_column_int(stmt, 4);
			player.mCurrentExperience = sqlite3_column_int(stmt, 5);
			player.mExperienceNeeded = sqlite3_column_int(stmt, 6);
			player.setBulletRadius(sqlite3_column_double(stmt, 7));
			player.setBulletDelay(sqlite3_column_double(stmt, 8));
			player.potion.quantity = sqlite3_column_int(stmt, 9);

			players.push_back(player);
		}
	} while (i == SQLITE_ROW); //Tant qu'il y a des données, on itère !

	return players;
}

bool Database::updatePlayer(Player& player)
{
	std::string query = "UPDATE Player SET maxHP=?, attackDamage=?, level=?, currency=?, currentXP=?, expNeeded=?, bulletRadius=?, bulletDelay=?, potionQty=? WHERE idPlayer=?";
	sqlite3_stmt * stmt;
	sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str()) + 1, &stmt, NULL);

	//Création des bind, comme en csharp, on remplace les ? par les valeurs
	//sqlite3_bind_text(stmt, 1, player.maxHP.c_str(), strlen(produit->nom.c_str()), 0);
	sqlite3_bind_int(stmt, 1, player.maxHP);
	sqlite3_bind_int(stmt, 2, player.attackDamage);
	sqlite3_bind_int(stmt, 3, player.level);
	sqlite3_bind_int(stmt, 4, player.currency);
	sqlite3_bind_int(stmt, 5, player.mCurrentExperience);
	sqlite3_bind_int(stmt, 6, player.mExperienceNeeded);
	sqlite3_bind_double(stmt, 7, player.getBullet().circle.getRadius());
	sqlite3_bind_double(stmt, 8, player.getBulletDelay());
	sqlite3_bind_int(stmt, 9, player.potion.quantity);
	sqlite3_bind_int(stmt, 10, player.idPlayer);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return true;
}

Player Database::getPlayer(int id)
{
	std::string query = "SELECT * FROM Player WHERE idPlayer=?";
	int i;
	Player player;

	sqlite3_stmt * stmt;
	//strlen longueur de la taille du tableau
	//Tail on s'en fiche, on le met a null
	sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str()) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 0, id);
	sqlite3_step(stmt);

	//Tant qu'il y a des données, on les récupères
		//Fonction step qui renvoi le signal "je suis ou pas dans une ligne"
			//params, stmt et l'id de la 1ère colonne
			//Récupère l'id
	player.idPlayer = sqlite3_column_int(stmt, 0);
	player.maxHP = sqlite3_column_int(stmt, 1);
	player.attackDamage = sqlite3_column_int(stmt, 2);
	player.level = sqlite3_column_int(stmt, 3);
	player.currency = sqlite3_column_int(stmt, 4);
	player.mCurrentExperience = sqlite3_column_int(stmt, 5);
	player.mExperienceNeeded = sqlite3_column_int(stmt, 6);
	player.setBulletRadius(sqlite3_column_double(stmt, 7));
	player.setBulletDelay(sqlite3_column_double(stmt, 8));
	
	sqlite3_finalize(stmt);

	return player;
}

bool Database::resetPlayer(int id)
{
	std::string query = "UPDATE Player SET maxHP=?, attackDamage=?, level=?, currency=?, currentXP=?, expNeeded=?, bulletRadius=?, bulletDelay=?, potionQty=? WHERE idPlayer=?";
	sqlite3_stmt * stmt;
	sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str()) + 1, &stmt, NULL);
	Player player;

	//Création des bind, comme en csharp, on remplace les ? par les valeurs
	//sqlite3_bind_text(stmt, 1, player.maxHP.c_str(), strlen(produit->nom.c_str()), 0);
	sqlite3_bind_int(stmt, 1, player.maxHP);
	sqlite3_bind_int(stmt, 2, player.attackDamage);
	sqlite3_bind_int(stmt, 3, player.level);
	sqlite3_bind_int(stmt, 4, player.currency);
	sqlite3_bind_int(stmt, 5, player.mCurrentExperience);
	sqlite3_bind_int(stmt, 6, player.mExperienceNeeded);
	sqlite3_bind_double(stmt, 7, player.getBullet().circle.getRadius());
	sqlite3_bind_double(stmt, 8, player.getBulletDelay());
	sqlite3_bind_int(stmt, 9, player.potion.quantity);
	sqlite3_bind_int(stmt, 10, id);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return true;
}

