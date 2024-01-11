//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//#define MAX_LICZBA_POZIOMOW 3
//
//class Menu
//
//{
//	//Private functions
//private:
//	sf::Font font;
//	sf::Text menu[MAX_LICZBA_POZIOMOW];//maksymalna liczba poziomow
//	int selectedItem = 0;
//
//public:
//	//Constructors / Destructors
//	Menu(float width, float height);
//	~Menu() {};
//
//	//Functions
//	void moveUp();//przesun do gory
//	void moveDown();//przesun w dol
//	int getSelectedItem() { return selectedItem; } //zwroc poziom menu
//	void draw(sf::RenderWindow& window); //rysuj menu w oknie
//};