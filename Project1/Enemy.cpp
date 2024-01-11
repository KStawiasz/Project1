#include "Enemy.h"

//Private functions

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 20 + 20); //Randomizer promienia wroga
	this->shape.setPointCount(rand() %20  + 3); //Randomizer punktow obiektu wroga
	this->shape.setFillColor(sf::Color(rand() % 254 + 1, rand() % 254 + 1, rand() % 254 + 1, 255)); //Randomizer koloru wroga na wartosciach RGB, kanal alpha=100%
}

void Enemy::initVariables()
{
	this->type		= 0;
	this->speed		= 4.f;
	this->hpMax		= 10;
	this->hp		= 0;
	this->damage	= 1;
	this->points	= 5;
}

//Constructors / Destructors
Enemy::Enemy(float pos_x, float pos_y)
{
	this->initShape();
	this->initVariables();

	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

//Accessors
const sf::FloatRect Enemy::getBounds() const //Returns rectangle bounding-box around the enemy object
{
	return this->shape.getGlobalBounds();
}

//Functions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}