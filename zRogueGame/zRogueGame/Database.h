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
	Player getPlayer(int id);
	int getPlayerNumber();
	
	bool updatePlayer(Player& player);
	bool resetPlayer(int id);
	
	

private:
	//On cr�e un pointeur sur une db de type sqlite3
	sqlite3 * db;
	std::string dbFile;
};

