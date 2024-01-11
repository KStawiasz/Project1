#include "Enemy.h"

//Private functions

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3; //Maksymalna wartoœæ: 10, minimalna: 3
	this->type		= 0;
	this->speed		= static_cast<float>(this->pointCount * 0.2); //static_cast zmienia wartosc pointCount na float
	this->hpMax		= static_cast<int>(this->pointCount); //static_cast zmienia wartosc pointCount na int
	this->hp		= this->hpMax;
	this->damage	= this->pointCount;
	this->points	= this->pointCount; //Punkty za zabicie wroga
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 4.5f); //Randomizer promienia wroga
	this->shape.setPointCount(this->pointCount); //Randomizer punktow obiektu wroga
	this->shape.setFillColor(sf::Color(rand() % 254 + 1, rand() % 254 + 1, rand() % 254 + 1, 255)); //Randomizer koloru wroga na wartosciach RGB, kanal alpha=100%
}

//Constructors / Destructors
Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();

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

const int& Enemy::getPoints() const //Returns points for being killed
{
	return this->points;
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