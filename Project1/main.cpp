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
				
	/////////////////////////////
	//////MENU
	/////////////////////////////

	//int menu_selected_flag = 0;
	//Menu menu(this->window.getSize().x, this->window.getSize().y);
	//// petla wieczna - dopoki okno jest otwarte
	//while (this->window.isOpen())
	//{
	//	// w kazdej iteracji petli sprawdzaj zdarzenia
	//	sf::Event event;
	//	while (this->window.pollEvent(event))
	//	{
	//		// jezeli odebrano zdarzenie "Closed" zamknij okno
	//		if (event.type == sf::Event::Closed)
	//			this->window.close();
	//		//jezeli nacisnieto jakikolwiek przycisk
	//		if (event.type == sf::Event::KeyPressed)
	//		{//obsluga menu z poziomu klawiszy (strzalki)
	//			if (event.key.code == sf::Keyboard::Up)
	//			{
	//				myDelay(250);
	//				menu.moveUp();
	//			}

	//			if (event.key.code == sf::Keyboard::Down)
	//			{
	//				myDelay(250);
	//				menu.moveDown();
	//			}
	//			if (menu_selected_flag == 0)
	//			{//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
	//				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
	//				{
	//					std::cout << "Uruchamiam gre..." << std::endl;
	//					menu_selected_flag = 1;
	//				}

	//				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
	//				{
	//					std::cout << "Najlepsze wyniki..." << std::endl;
	//					menu_selected_flag = 1;
	//				}

	//				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
	//				{
	//					std::cout << "Koniec gry..." << std::endl;
	//					menu_selected_flag = 1;
	//				}

	//			}


	//		}
	//	}



	//	// wyczysc obszar rysowania
	//	window.clear();


	//	// tutaj umiesc procedury rysujace...
	//	// window.draw(...);
	//	if (menu_selected_flag == 0)
	//		menu.draw(window);

	//	// ostatnia czynnosc - wyswietl okno wraz zawartoscia
	//	window.display();
	//}

	//Initalize Game engine
	Game game;
	
	game.run();
	//Koniec gry

	return 0;
}