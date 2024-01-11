#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

#include<iostream>


class Player
{
private:
	sf::Texture texture; //Variable that holds texture of a sprite
	sf::Sprite sprite;

	float movementSpeed; //Variable responsible for the movement speed

	float attackCooldown; //Cooldown ataku
	float attackCooldownMax; 

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	//Constructors / Destructors
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;	//Pozwala na kreowanie pociskow na pozycji gracza
	const sf::FloatRect getBounds() const;	//Struktura sluzaca do reprezentowania obszarow kolizji
											//funkcja getBounds jest deklaracj¹ metody w klasie, która zwraca obiekt sf::FloatRect reprezentuj¹cy granice obiektu, ale nie modyfikuje ¿adnych danych w obiekcie

	//Modifiers
	void setPosition(const sf::Vector2f pos); //Zmienia/Zatrzymuje pozycje statku
	void setPosition(const float x, const float y); //Zmienia/Zatrzymuje pozycje statku


	//Functions
	void move(const float dirX, const float dirY); //Funkcja inicjujaca ruch
	const bool canAttack(); //Bool reprezentuje 'true' or 'false'

	void updateAttack(); 
	void update();
	void render(sf::RenderTarget& target); //sf::RenderTarget to klasa w SFML, która reprezentuje obiekt, na którym mo¿na renderowaæ grafikê
};											//& oznacza referencje

