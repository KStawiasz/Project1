#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Enemy
{
//Private functions
private:
	unsigned pointCount; //Inicjuje zmienne losowe
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points; //Punkty za zabicie wroga

	void initVariables();
	void initShape();

public:
	//Constructors / Destructors
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const; //This returns how many points every enemy will give me

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};