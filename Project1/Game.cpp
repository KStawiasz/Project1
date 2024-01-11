#include "Game.h"

//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Ship Game", sf::Style::Close | sf::Style::Titlebar); //Window with close and title
	this->window->setFramerateLimit(60);												
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initPlayer()
{
	this->player = new Player(); //Player pointer = new player
}

void Game::initEnemies()
{	
	this->spawnTimerMax = 40.f; //Maksymalny czas miedzy spawnami wrogow
	this->spawnTimer = this->spawnTimerMax; //Ustawia aktualny czas do spawnu wroga
}


//Constructors / Destructors
Game::Game()
{
	this->initWindow(); //Inicjalizowanie okna
	this->initTextures(); //Inicjalizowanie tekstur
	this->initPlayer(); //Inicjalizowanie gracza
	this->initEnemies(); //Inicjalizowanie wrogow
}

Game::~Game()
{
	delete this->window; //Cleaning memory
	delete this->player;

	//Delete textures (Cleaning dynamic objects)
	for (auto &i : this->textures) //Pêtla "for" bêdzie iterowaæ przez wszystkie pary klucz-wartoœæ w kontenerze, wartoœæ to wskaŸnik do obiektu tekstury
	{
		delete i.second; //Usuwa ka¿dy obiekt tekstury za pomoc¹ operatora
	}

	//Delete bullets (Cleaning memory)
	for (auto *i : this->bullets) //Pêtla "for" bêdzie iterowaæ przez wszystkie elementy w kontenerze this->bullets, a ka¿dy element bêdzie dostêpny jako wskaŸnik i. auto* oznacza, ¿e kompilator powinien automatycznie okreœliæ typ wskaŸnika.
	{
		delete i; //Usuwa obiekt wskazany jako "i"
	} 

	//Delete Enemies (Cleaning memory)
	for (auto* i : this->enemies) //Pêtla "for" bêdzie iterowaæ przez wszystkie elementy w kontenerze this->enemies, a ka¿dy element bêdzie dostêpny jako wskaŸnik i. auto* oznacza, ¿e kompilator powinien automatycznie okreœliæ typ wskaŸnika.
	{
		delete i; //Usuwa obiekt wskazany jako "i"
	}

}

//Functions
void Game::run()
{
	//as soon as we close the window, function "game.run()" exits and main returns 0
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvents() //pollEvents sluzy do obslugi zdarzen - zamkniecie okna, nacisniecie klawisza itp.
{
	sf::Event e;
	while (this->window->pollEvent(e)) //Grabs event from the window and shoves into ev variable, checks if the close button is pressed
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();	//Window closes, when the button Close is pressed
		else if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) //If a key was pressed and key;s code is escape then window->close
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move the player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	//Function that checks for input
		this->player->move(-1.f, 0.f);					//Move (X, Y)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->player->move(0.f, 1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x+34.f, this->player->getPos().y, 0.f, -2.f, 5.f)); //metoda push_back dodaje nowy element na koniec danego wektora
	}
}

void Game::updateBullets()
{
	unsigned counter = 0; //Zmienna o nazwie counter i typie unsigned (przechowuje liczby nieujemne, pocz¹tkowa wartoœæ tej zmiennej to 0)
	for (auto *bullet : this->bullets)
	{
		bullet->update();

		//Removing bullet if its not visible, or meets the condition
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) //Deletes bullet when it hits the top of the screen
		{
			//Delete bullet
			delete this->bullets.at(counter); //Because Bullets are dynamic I have to delete them 
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

		}

		++counter; 
	}
}

void Game::updateEnemiesAndCombat() //Spawns enemies
{
	this->spawnTimer += 0.5f; //Timer stale wzrasta
	if (this->spawnTimer >= this->spawnTimerMax) //Warunek sprawdzaj¹cy, czy aktualny czas do spawnu wroga jest wiêkszy lub równy maksymalnemu czasowi do spawnu.
	{
		this->enemies.push_back(new Enemy(rand() % 600, -100.f));  //metoda push_back dodaje nowy element na koniec danego wektora, losuje pozycje (x, y)
		this->spawnTimer = 0.f; //Jesli warunek jest spelniony, to ustawia timer spawnu na 0.0
	}

	for (int i = 0; i < this->enemies.size(); ++i)
	{
		this->enemies[i]->update();
		
		for (int k = 0; k < this->bullets.size(); ++k) 
		{
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds())) 
			{
				this->bullets.erase(this->bullets.begin() + k); //Deletes bullet po trafieniu
				this->enemies.erase(this->enemies.begin() + i); //Deletes enemy po trafieniu
			}
		}

		//Usuwanie wroga na dole ekranu
		if (this->enemies[i]->getBounds().top > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i); //Usuwanie z wektora za pomoca funkcji erase
			std::cout << this->enemies.size() << "\n";
		}													//Usuwa coœ z pocz¹tku oraz pozycje zmiennej "i"
	}
}

void Game::update() //Game updates, positions etc 
{
	this->updatePollEvents();

	this->updateInput();

	this->player->update();

	this->updateBullets();

	this->updateEnemiesAndCombat();
}

void Game::render() //Draws all the updated stuff
{
	this->window->clear(); 

	//Draw all the stuff here:
	this->player->render(*this->window); //Renders a player in the window directly

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window); //Renders bullet in the window
	}

	for (auto *enemy : this->enemies)
	{
		enemy->render(this->window); //Renders enemy in the window
	}

	this->window->display();
}