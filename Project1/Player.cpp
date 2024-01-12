#include "Player.h"


//Private functions
void Player::initVariables()
{
	this->movementSpeed = 9.f;
	this->attackCooldownMax = 5.f;
	this->attackCooldown = this->attackCooldownMax; //Sprawia, ze pierwszy atak bedzie instant

	this->hpMax = 70;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	//Load a texture from file 
	if (texture.loadFromFile("textures/statek.png")) 
	{
		std::cout << "Zaladowano teksture statku!" << "\n";
	}

	else {
		std::cout << "ERROR: Player::InitTexture: Nie zaladowano tekstury statku!" << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite. Obiekt Player ustawia swoj¹ teksturê na teksturê, która jest przechowywana w obiekcie sprite
	this->sprite.setTexture(this->texture); 
	this->sprite.setPosition(350.f, 700.f);

	//Resize the sprite
	this->sprite.scale(0.07f, 0.07f);

}

//Constructors / Destructors
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}		
	
Player::~Player()
{

}

 //Accessor
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition(); //Zwraca pozycje statku z klasy Player i nadaje ja obiektowi, na ktorym jest wywolana ta metoda, w moim wypadku dla playera
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

//Modifiers
void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp) //ustawianie wartosci hp
{
	this->hp = hp;
}

void Player::loseHp(const int value) //tracenie hp za kazdym razem
{
	this->hp -= value; //Upewnienie, ze hp moze wyniesc najmniej 0
	if (this->hp < 0)
		this->hp = 0;
}

//Functions
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY); //Sta³a predkosc * kierunek X/Y
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) //maksymalny czas od ostatniego ataku, który musi up³yn¹æ przed kolejnym atakiem
	{
		this->attackCooldown = 0.f; //Resetuje czas od ostatniego ataku na 0sekund, co oznacza, ze gracz moze atakowac znowu
		return true; //Gracz moze zaatakowac od nowa
	}

	return false; //Zwraca false, jesli attackCooldown > MaxCooldown, wstrzymuje ataki gracza
}

void Player::updateAttack() //Funkcja Cooldownu ataku 
{
	if (this->attackCooldown < this->attackCooldownMax) //Warunek sprawdzaj¹cy, czy aktualny czas od ostatniego ataku jest mniejszy ni¿ maksymalny czas od ostatniego ataku
		this->attackCooldown += 0.5f; //Aktualizowanie czasu od ostatniego ataku
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}