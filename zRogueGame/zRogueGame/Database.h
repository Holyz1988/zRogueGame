#pragma once

#include "sqlite3.h"
#include "Player.h"
#include <string>
#include <vector>

class Database
{
public:
	Database();
	virtual ~Database();

	void openDatabase();
	void closeDatabase();
	bool executeQuery(std::string query);
	
	bool insertPlayer(Player& player);
	//On revoir un pointeur sur un vecteur de produit
	std::vector<Player> getAllPlayer();
	/*
	bool updatePlayer(Player* player);
	bool deletePlayer(int id);
	*/
	

private:
	//On crée un pointeur sur une db de type sqlite3
	sqlite3 * db;
	std::string dbFile;
};

