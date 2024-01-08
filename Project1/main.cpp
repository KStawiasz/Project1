/*
Projekt Krystian Stawiasz s194625
Tytu³ gry: Space Ship
Scenariusz nr 1
*/

#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{

	//Okno 
	sf::RenderWindow window(sf::VideoMode(640, 480), "Space Ship", sf::Style::Titlebar | sf::Style::Close);
	sf::Event ev;

	//Petla gry
	while (window.isOpen())
	{
		//zdarzenia polling
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}

		//Update

		//Render
		window.clear(sf::Color::Magenta); //Clear old frame

		//Draw your game 

		window.display(); // Tell app that window is done drawing 
	}

	//koniec gry
	return 0;
}