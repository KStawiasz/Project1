#include "Bullet.h"

//Private functions



//Constructors / Destructors
Bullet::Bullet()
{
	this->movementSpeed = 5.f;
}

Bullet::Bullet(sf::Texture * texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(pos_x, pos_y);
	this->shape.scale(0.06f, 0.06f);

	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
}

Bullet::~Bullet()
{

}

//Accessor 
const sf::FloatRect Bullet::getBounds() const //Collision with enemies, reads the bounds of the bullet
{
	return this->shape.getGlobalBounds();
}

//Functions
void Bullet::update()
{
	//Movement
	this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape); 
}
