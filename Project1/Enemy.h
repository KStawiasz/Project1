#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Enemy
{
//Private functions
private:
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initShape();
	void initVariables();

public:
	//Constructors / Destructors
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};