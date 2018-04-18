#include "Game.h"
#include "Database.h"
#include <iostream>

int main()
{
	std::string query = "CREATE TABLE IF NOT EXISTS Player (idPlayer INTEGER PRIMARY KEY, maxHP INT, attackDamage INT, level INT, currency INT, currentXP INT, expNeeded INT, bulletRadius FLOAT, bulletDelay FLOAT)";
	std::string query2 = "CREATE TABLE IF NOT EXISTS Items (idItem INTEGER PRIMARY KEY, name TEXT, quantity INT, FKidPlayer integer NOT NULL, FOREIGN KEY(FKidPlayer) REFERENCES Player(idPlayer))";

	Database* db = new Database();

	db->openDatabase();

	db->executeQuery(query);
	db->executeQuery(query2);
	
	db->closeDatabase();


	Game game(800, 600, "zPainGame");

	//game.run();

	

	return 0;
}