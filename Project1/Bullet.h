#pragma once

#include<SFML/Graphics.hpp>

#include<iostream>

class Bullet
{
//Private functions
private:	
	sf::Sprite shape;

	sf::Vector2f direction;	
	float movementSpeed; //Variable responsible for the movement speed

public:
	//Constructors / Destructors
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Accessor 
	const sf::FloatRect getBounds() const; //Collision with enemies, reads the bounds of the bullet

	//Functions
	void update();
	void render(sf::RenderTarget* target); //*oznacza wskaünik
};