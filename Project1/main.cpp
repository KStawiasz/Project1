/*
Projekt Krystian Stawiasz s194625
Tytu³ gry: Space Ship
Scenariusz nr 1
*/

#include <iostream>
#include "Game.h"
#include "Player.h"
#include <time.h>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

using namespace std;


int main()
{
	srand(static_cast<unsigned int>(time(0)));	// Inicjalizacja generatora liczb pseudolosowych
												//std::srand(static_cast<unsigned>(std::time(NULL)));

	//Init Game engine
	Game game;
	
	
	game.run();
	//koniec gry

	return 0;
}