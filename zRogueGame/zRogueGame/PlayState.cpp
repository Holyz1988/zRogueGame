#include "PlayState.h"
#include "OptionState.h"
#include "GameOverState.h"
#include <iostream>
#include <math.h>

#include <iostream>

using namespace std;

PlayState::PlayState(GameDataRef data, Player& player) : _data(data),
mPlayer(player),
mOrc(mPlayer)
{
}

PlayState::PlayState(GameDataRef data) : _data(data),
mOrc(mPlayer)
{
}


PlayState::~PlayState()
{

}
//: mOrc(sf::Vector2f(10.f, 10.f))
void PlayState::init()
{
	srand(time(NULL));
	//Chargement du sol
	mRessources.loadTexture("Tiles", "ressources/tiles.png");
	mTile.sprite.setTexture(mRessources.getTexture("Tiles"));
	mTile.sprite.setTextureRect(sf::IntRect(7 * 32, 32, 32, 32));
	mTile.initGround(mGround, mTile);

	//Chargement des murs
	mWall.sprite.setTexture(mRessources.getTexture("Tiles"));
	mWall.sprite.setTextureRect(sf::IntRect(3 * 32, 32, 32, 32));
	mWall.initArena(mWalls, mWall);

	//Chargement du spawner mob
	mSpawnTile.sprite.setTexture(mRessources.getTexture("Tiles"));
	mSpawnTile.sprite.setTextureRect(sf::IntRect(3 * 32, 5 * 32, 3 * 32, 3 * 32));

	//Chargement du joueur
	mRessources.loadTexture("Player", "ressources/mainPlayer.png");
	mPlayer.sprite.setTexture(mRessources.getTexture("Player"));
	mPlayer.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	//Chargement des dragons
	mRessources.loadTexture("Dragon", "ressources/Enemy_dragon2.png");
	mDragon.sprite.setTexture(mRessources.getTexture("Dragon"));
	mDragon.sprite.setTextureRect(sf::IntRect(0, 0, 128, 160));
	mDragon.rect.setPosition(sf::Vector2f(200, 200));

	//Chargement des orcs
	mRessources.loadTexture("Orc", "ressources/orc.png");
	mOrc.sprite.setTexture(mRessources.getTexture("Orc"));
	mOrc.sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

	//Chargement des boules de feux
	mRessources.loadTexture("Enemy1", "ressources/fireball.png");
	mFireBall.sprite.setTexture(mRessources.getTexture("Enemy1"));
	mFireBall.sprite.setTextureRect(sf::IntRect(0, 4 * 64, 64, 64));

	//Chargement de la police du HUD
	mRessources.loadFont("HUDFont", "ressources/Lobster-Regular.ttf");
	mRessources.loadFont("OverlayFont", "ressources/gomarice_game_continue_02.ttf");
	HPText.text.setFont(mRessources.getFont("HUDFont"));
	EXPText.text.setFont(mRessources.getFont("HUDFont"));
	currencyText.text.setFont(mRessources.getFont("HUDFont"));
	levelText.text.setFont(mRessources.getFont("HUDFont"));
	potionText.text.setFont(mRessources.getFont("HUDFont"));
	buyingPotionText.text.setFont(mRessources.getFont("HUDFont"));
	buyingExpText.text.setFont(mRessources.getFont("HUDFont"));


	//Police joueur
	mPlayer.text.setFont(mRessources.getFont("HUDFont"));
	mPlayer.text.setCharacterSize(14);
	mPlayer.text.setOutlineColor(sf::Color::Black);
	mPlayer.text.setOutlineThickness(1.f);

	//Police monstre
	mOrc.text.setFont(mRessources.getFont("HUDFont"));
	mOrc.text.setCharacterSize(14);
	mOrc.text.setOutlineColor(sf::Color::Black);
	mOrc.text.setOutlineThickness(1.f);

	//Police Tuile spawner
	mSpawnTile.text.setFont(mRessources.getFont("OverlayFont"));
	mSpawnTile.text.setCharacterSize(20);
	mSpawnTile.text.setFillColor(sf::Color::White);
	mSpawnTile.text.setOutlineColor(sf::Color::Red);
	mSpawnTile.text.setOutlineThickness(2.f);

	//Police HP ORC
	mPlayer.hpOrcLost.text.setFont(mRessources.getFont("OverlayFont"));
	mPlayer.hpOrcLost.text.setCharacterSize(30);
	mPlayer.hpOrcLost.text.setFillColor(sf::Color::Red);
	mPlayer.hpOrcLost.text.setOutlineThickness(2.f);
	mPlayer.hpOrcLost.text.setOutlineColor(sf::Color::Black);

	//Music et sons
	if (!backGroundMusic.openFromFile("music.ogg"))
	{
		cout << "erreur" << endl;
	}
	backGroundMusic.setLoop(true);
	backGroundMusic.play();
	backGroundMusic.setVolume(20);

	if (!bufferPlayerHit.loadFromFile("playerhit.ogg"))
	{
		cout << "erreur" << endl;
	}
	soundHit.setBuffer(bufferPlayerHit);
	soundHit.setVolume(20);

	if (!bufferFireBullet.loadFromFile("shot.ogg"))
	{
		cout << "erreur" << endl;
	}
	soundBullet.setBuffer(bufferFireBullet);
	soundBullet.setVolume(20);

	db = new Database();
	db->openDatabase();
}

void PlayState::handleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Ferme la fenêtre */
		case sf::Event::Closed:
			db->updatePlayer(mPlayer);
			db->closeDatabase();
			this->_data->window.close();
			break;

		case sf::Event::KeyPressed:
		//Spawns orcs
			if (event.key.code == sf::Keyboard::E)
			{
				if (mPlayer.getSpawnerStatus() && !mSpawnTile.locked)
				{
					mSpawnTile.locked = true;
					mOrc.spawEnemies(mOrcs, mOrc, mSpawnTile, mPlayer);
				}
			}
			//Utilisation de potions
			if (event.key.code == sf::Keyboard::R)
			{
				if (mPlayer.potion.quantity > 0)
				{
					//Si le joueur n'est pas au maximum de sa vie, on utilise une potion
					if (mPlayer.currentHp != mPlayer.maxHP)
					{
						mPlayer.potion.quantity--;
						mPlayer.currentHp += 50;
						if (mPlayer.currentHp > mPlayer.maxHP)
						{
							mPlayer.currentHp = mPlayer.maxHP;
						}
					}
					else
					{
						//Ne rien faire
					}
				}
			}

			//Achat de potion et d'experience
			if (event.key.code == sf::Keyboard::F1)
			{
				if (mPlayer.currency >= 40)
				{
					mPlayer.currency -= 40;
					mPlayer.potion.quantity++;
				}
			}

			if (event.key.code == sf::Keyboard::F2)
			{
				if (mPlayer.currency >= 100)
				{
					mPlayer.currency -= 100;
					mPlayer.mCurrentExperience += 100;
				}
			}
			break;
		}
	}
}

void PlayState::update(float dt)

{	
	//Ecran fin de partie si le joueur meurt
	if (mPlayer.isDead())
	{
		db->updatePlayer(mPlayer);
		db->closeDatabase();
		backGroundMusic.stop();
		this->_data->machine.addState(StateRef(new GameOverState(this->_data)), true);
	}


	//Si tous les orcs meurent, on libère le spawner de mob
	if (mOrcs.empty())
	{
		mSpawnTile.locked = false;
	}

	//Mise à jour des positions et actions enemies
	mFireBall.spawnFireBalls(mFireBalls, mFireBall, mPlayer);//Spawn les enemies
	mFireBall.updateV(mPlayer);//MAJ des positions enemies
	mFireBall.updateMovement(mFireBalls, this->_data->window, dt);//MAJ des mouvement enimies
	mFireBall.updatePos();

	//Mise à jour du dragon
	mDragon.updatePos();

	//Mise à jour de l'orc
	for (unsigned int i = 0; i < mOrcs.size(); i++)
	{
		mOrcs[i].moveEnemies(dt, mWalls);
	}

	//Mise à jour des positions et actions du joueur
	mPlayer.losingHp(mOrcs, soundHit);
	mPlayer.losingHpToFireBall(mFireBalls, soundHit);
	mPlayer.fireBallPlayerCollision(mFireBalls);
	mPlayer.fireBullets(this->_data->window, mWalls, soundBullet);//MAJ des projectiles
	mPlayer.updateVectors(this->_data->window);//MAJ des positions joueur
	mPlayer.update(dt, mWalls);//Met à jour la position du joueur
	mPlayer.bulletOrcCollision(mOrcs); // Détruit le projectile joueur s'il rencontre un orc

	//HUD
	positionHUD(mPlayer);

	//Apparition du message d'explication
	spawnerPlayerCollision();

	//On place la caméra
	centerCamera();
	this->_data->window.setView(mCamera);
}

void PlayState::draw(float dt)
{
	//On déssine le monde
	mWall.drawArena(mWalls, this->_data->window);
	mTile.drawGround(mGround, this->_data->window);
	mSpawnTile.drawSpawner(mSpawnTile, this->_data->window);

	//On déssine le joueur et les boules
	this->_data->window.draw(this->mPlayer.sprite);
	mPlayer.drawBullets(this->_data->window);

	//Boules de feux
	mFireBall.drawEnemies(mFireBalls, this->_data->window);

	//Dragon
	//game->window.draw(this->mDragon.sprite);

	//Orcs
	mPlayer.spawnOrcs(mSpawnTile);
	mOrc.drawEnemies(mOrcs, this->_data->window);
	mPlayer.drawHpLost(this->_data->window);

	//On dessine le HUD
	this->_data->window.draw(HPText.text);
	this->_data->window.draw(EXPText.text);
	this->_data->window.draw(currencyText.text);
	this->_data->window.draw(levelText.text);
	this->_data->window.draw(potionText.text);
	this->_data->window.draw(buyingPotionText.text);
	this->_data->window.draw(buyingExpText.text);

	this->_data->window.draw(mPlayer.text);

	this->_data->window.draw(mSpawnTile.text);
}


void PlayState::centerCamera()
{
	this->mCamera.setSize(sf::Vector2f((float)this->_data->window.getSize().x, (float)this->_data->window.getSize().y));
	this->mCamera.setCenter(mPlayer.rect.getPosition());
	this->mCamera.zoom(1.f);
}

void PlayState::positionHUD(Player& player)
{
	//HP
	float hpPositionX;
	float hpPositionY;

	hpPositionX = mPlayer.rect.getPosition().x - this->_data->window.getSize().x / 2;
	hpPositionY = mPlayer.rect.getPosition().y - this->_data->window.getSize().y / 2;

	HPText.text.setString("Points de vies : " + to_string(mPlayer.currentHp) + "/" + to_string(mPlayer.maxHP));
	HPText.text.setPosition(hpPositionX, hpPositionY);

	//EXP
	float expPositionX;
	float expPositionY;

	expPositionX = mPlayer.rect.getPosition().x - this->_data->window.getSize().x / 2;
	expPositionY = mPlayer.rect.getPosition().y - this->_data->window.getSize().y / 2 + 32;

	EXPText.text.setString("Expérience : " + to_string(mPlayer.mCurrentExperience) + "/" + to_string(mPlayer.mExperienceNeeded));
	EXPText.text.setPosition(expPositionX, expPositionY);

	//GOLD
	float goldPositionX;
	float goldPositionY;

	goldPositionX = mPlayer.rect.getPosition().x - this->_data->window.getSize().x / 2;
	goldPositionY = mPlayer.rect.getPosition().y - this->_data->window.getSize().y / 2 + 64;

	currencyText.text.setString("Or : " + to_string(mPlayer.currency));
	currencyText.text.setPosition(goldPositionX, goldPositionY);

	//Level
	float levelPositionX;
	float levelPositionY;

	levelPositionX = mPlayer.rect.getPosition().x + this->_data->window.getSize().x / 2 - 120;
	levelPositionY = mPlayer.rect.getPosition().y - this->_data->window.getSize().y / 2;

	levelText.text.setString("Niveau : " + to_string(mPlayer.level));
	levelText.text.setPosition(levelPositionX, levelPositionY);

	//potionText
	float potionPositionX;
	float potionPositionY;

	potionPositionX = mPlayer.rect.getPosition().x + this->_data->window.getSize().x / 2 - 120;
	potionPositionY = mPlayer.rect.getPosition().y - this->_data->window.getSize().y / 2 + 25;

	potionText.text.setString("Potions x " + to_string(mPlayer.potion.quantity));
	potionText.text.setPosition(potionPositionX, potionPositionY);

	//buyingPotionText
	float buyingPotionPositionX;
	float buyingPotionPositionY;

	buyingPotionPositionX = mPlayer.rect.getPosition().x - this->_data->window.getSize().x / 2;
	buyingPotionPositionY = mPlayer.rect.getPosition().y + 220;

	buyingPotionText.text.setString("F1 : Potion de soin (40 Or)");
	buyingPotionText.text.setPosition(buyingPotionPositionX, buyingPotionPositionY);


	//buyingExpText
	float buyingExpPositionX;
	float buyingExpPositionY;

	buyingExpPositionX = mPlayer.rect.getPosition().x - this->_data->window.getSize().x / 2;
	buyingExpPositionY = mPlayer.rect.getPosition().y + 245;

	buyingExpText.text.setString("F2 : 100 EXP (100 Or)");
	buyingExpText.text.setPosition(buyingExpPositionX, buyingExpPositionY);
}

void PlayState::spawnerPlayerCollision()
{
	std::cout << mSpawnTile.locked << std::endl;
	if (mPlayer.rect.getGlobalBounds().intersects(mSpawnTile.rect.getGlobalBounds()) && !mSpawnTile.locked)
	{
			mSpawnTile.text.setPosition(mPlayer.rect.getPosition().x - 200, mPlayer.rect.getPosition().y - 200);
			mSpawnTile.text.setString("Appuyer sur E pour faire apparaitre la vague d'ennemis");
	}
	else
	{
		mSpawnTile.text.setString("");
	}
}
