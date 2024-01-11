#pragma once

#include<map>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


class Game
{
private:
	//Create and manage window, wskaŸnika na klase okna
	sf::RenderWindow* window;

	//Resources - it handels all the textures
	std::map<std::string, sf::Texture*> textures; //Map is a container class that maps 2 things together, for each string there is gonna be a texture
	std::vector<Bullet*> bullets; //Vektor obiektów klasy "Bullet" 

	//Player
	Player* player; //Wskaznik na klase Player
	
	//Enemies
	float spawnTimer; 
	float spawnTimerMax;
	std::vector<Enemy*> enemies; //To bedzie updateowane w funkcjach i pozniej renderowane
	 
	//Private functions
	void initWindow(); //Inicjalizuje obiekt okna
	void initTextures(); //Loads all the textures in the game

	void initPlayer(); //Inicjalizuje obiekt gracza
	void initEnemies(); //Inicjalizuje obiekt wroga


public:
	//Constructors / Destructors
	Game();
	virtual ~Game();


	//Functions
	void run();

	void updatePollEvents(); //pollEvents sluzy do obslugi zdarzen - zamkniecie okna, nacisniecie klawisza itp.
	void updateInput(); 
	void updateBullets();
	void updateEnemiesAndCombat(); //Also handles spawn timers
	void update(); //Aktualizuje stan gry. Mo¿e to obejmowaæ ruch postaci, reakcje na interakcje u¿ytkownika itp
	void render(); //Renderuje obecny stan gry na ekranie. To mo¿e obejmowaæ rysowanie postaci, t³a, obiektów itp
};

