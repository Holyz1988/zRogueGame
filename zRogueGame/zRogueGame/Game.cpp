#include "Game.h"
#include "GameState.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//On démarre l'application
Game::Game(  ) : window( sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Z Rogue like" )
{
	//window.setFramerateLimit(60);
}

//On détruit les pointeurs crée avec new
Game::~Game( )
{
	while (!states.empty())
		popState();
}

void Game::pushState( GameState * state )
{
	states.push_back( state );
}

void Game::popState( )
{
	states.back();
	delete states.back( );
	states.pop_back();
}

//Renvoi le dernier élement du vecteur, donc le mode de jeu dans lequel on est.
GameState * Game::currentState( )
{
	if ( states.empty( ) )
		return nullptr;
	else
		return states.back( );
}

void Game::gameLoop( )
{
	sf::Clock clock;

	while (window.isOpen())
	{
		//Controle des FPS
		float dt = clock.restart().asSeconds();

		if ( currentState( ) == nullptr )
			continue;

		//Récupérer les saisies utilisateurs pendant l'état acutel de notre jeu (menu, maingame, pause, etc)
		currentState( )->handleInput( );
		currentState( )->update( dt );

		window.clear( sf::Color::Black );

		currentState( )->draw( dt );

		window.display( );
	}
}

void Game::previousState()
{
	states.pop_back();
}
