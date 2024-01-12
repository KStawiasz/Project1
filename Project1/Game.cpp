#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

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

void Game::initGUI()
{
	//Loads font
	this->font.loadFromFile("arial.ttf");

	//Initialize point text
	this->pointText.setPosition(5, 30);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");

	//tekst koniec gry
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(80);
	this->gameOverText.setFillColor(sf::Color::Cyan);
	this->gameOverText.setString("Koniec Gry!");
	this->gameOverText.setPosition(205, 240);



	//Init player GUI - Wskaznik zycia gracza
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color(204, 1, 15, 240));
	this->playerHpBar.setPosition(sf::Vector2f(5, 5));


	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(51, 21, 0, 200));
}

void Game::initSwiat()
{
	if (worldBcgTexture.loadFromFile("textures/background.jpg"))
	{
		std::cout << "Zaladowano teksture swiata!" << "\n";
	}

	else {
		std::cout << "ERROR: Game::InitSwiat: Nie zaladowano tekstury swiata!" << "\n";
	}

	this->worldBcg.setTexture(this->worldBcgTexture);
}

void Game::initSystems()
{
	this->points = 0;
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
	isPaused = false;
	this->initWindow(); //Inicjalizowanie okna
	this->initTextures(); //Inicjalizowanie tekstur
	this->initGUI();
	this->initSwiat(); //Inicjalizowanie swiata
	this->initSystems(); //Inicjalizowanie systemu liczenia punktów
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
		this->updatePollEvents();

		if(this->player->getHp() > 0)
			this->update();

		this->render();
	}
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void Game::displayPauseMenu() //Wyswietla menu pauzy
{
	sf::Text wyjscie;
	sf::Text tekst;
	tekst.setFont(font);
	tekst.setCharacterSize(30);
	tekst.setFillColor(sf::Color::White);
	tekst.setPosition(100, 150);

	tekst.setString("Wcisnij (R), aby wznowic gre! \n\nWyjdz (Esc)");
	this->window->clear();
	this->window->draw(tekst);
	this->window->display();

	// Czekaj na odpowiedni klawisz
	bool waitingForKey = true;
	while (waitingForKey)
	{
		sf::Event e;
		while (this->window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				this->window->close();
				waitingForKey = false;
			}
			else if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::Escape)
				{
					this->window->close();
					waitingForKey = false;
				}
				else if (e.key.code == sf::Keyboard::R)
				{
					waitingForKey = false;
				}
			}
		}
	}
}
void Game::displayHelpScreen() //Wyswietla ekran pomocy F1
{
	sf::Text helpText;
	helpText.setFont(this->font);
	helpText.setCharacterSize(20);
	helpText.setFillColor(sf::Color::White);
	helpText.setPosition(100, 100);
	helpText.setString("Wcisnij (F1) aby wyswietlic to okno. \nPoruszasz sie strzalkami. \nStrzal (spacja).  \n\nWcisnij (R) aby wznowic gre!");

	this->window->clear();
	this->window->draw(helpText);
	this->window->display();

	bool waitingForKey = true;
	while (waitingForKey)
	{
		sf::Event e;
		while (this->window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				this->window->close();
				waitingForKey = false;
			}
			else if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::F1)
				{
					waitingForKey = false;
				}
				else if (e.key.code == sf::Keyboard::R)
				{
					this->isPaused = false;
					waitingForKey = false;
				}
			}
		}
	}
}
void Game::updatePollEvents() //pollEvents sluzy do obslugi zdarzen - zamkniecie okna, nacisniecie klawisza itp.
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			this->window->close();
		}
		else if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Escape)
			{
				if (!this->isPaused)
				{
					this->isPaused = true;
					this->displayPauseMenu();
				}
				else
				{
					this->isPaused = false;
				}
			}
			else if (e.key.code == sf::Keyboard::F1)
			{
				this->displayHelpScreen();
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
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

void Game::updateGUI() //Funkcja updateGUI nale¿y do klasy Game i s³u¿y do aktualizacji interfejsu u¿ytkownika (GUI). Wykorzystuje obiekt klasy std::stringstream o nazwie ss.
{
	std::stringstream ss; //Tworzenie strumienia stringstream do formatowania danych tekstowych, stringstream operuje na lancuchu znakow

	ss << "Points " << this->points; //Operator "<<" jest u¿ywany, aby przekszta³ciæ wartoœæ zmiennej this->points do formatu tekstowego i umieœciæ go w strumieniu ss

	this->pointText.setString(ss.str()); //Tutaj uzyskujemy finalny wynik w postaci tekstu z obiektu ss za pomoc¹ ss.str() i ustawiamy ten tekst jako zawartoœæ obiektu pointText.

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}


void Game::updateSwiat()
{

}

void Game::updateKolizja() //Ograniczanie ruchow gracza, zeby na osi X i Y wrocil do swojej pozycji 
{

	//Lewa bariera
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	//Prawa bariera 
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Gorna bariera
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	//Dolna bariera
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
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
			//Delete bullet when it hits the top of the window
			delete this->bullets.at(counter);  //Because bullets are dynamic, so I delete them first
			this->bullets.erase(this->bullets.begin() + counter); //then erase from the Vector
		}

		++counter; 
	}
}

void Game::updateEnemies() //Spawns enemies
{
	//Spawning
	this->spawnTimer += 0.5f; //Timer stale wzrasta
	if (this->spawnTimer >= this->spawnTimerMax) //Warunek sprawdzaj¹cy, czy aktualny czas do spawnu wroga jest wiêkszy lub równy maksymalnemu czasowi do spawnu.
	{
		this->enemies.push_back(new Enemy(rand() % 600, -100.f));  //metoda push_back dodaje nowy element na koniec danego wektora, losuje pozycje (x, y)
		this->spawnTimer = 0.f; //Jesli warunek jest spelniony, to ustawia timer spawnu na 0.0
	}

	//Update
	unsigned counter = 0; //Zmienna o nazwie counter i typie unsigned (przechowuje liczby nieujemne, pocz¹tkowa wartoœæ tej zmiennej to 0)
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Removing enemy if its not visible, or meets the condition
		if (enemy->getBounds().top > this->window->getSize().y) //Deletes enemy when it hits the bottom of the screen
		{
			//Delete enemy when it hits the bottom of the window
			delete this->enemies.at(counter); //Because enemies are dynamic, so I delete them first
			this->enemies.erase(this->enemies.begin() + counter); //then erase from the Vector
		}
		//Player hits an enemy
		else if (enemy->getBounds().intersects(this->player->getBounds())) //Deletes enemy when touches the player
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage()); //Pobiera wartoœæ obra¿eñ od aktualnego wroga, na którym aktualnie iteruje pêtla
			delete this->enemies.at(counter); //Because enemies are dynamic, so I delete them first
			this->enemies.erase(this->enemies.begin() + counter); //then erase from the Vector
		}

		++counter;

	}

	if (Game::enemiesDestroyed > 0) 
    {
        for (auto& enemy : this->enemies) 
        {
            float currentSpeed = enemy->getSpeed();
            enemy->setSpeed(currentSpeed + (currentSpeed * Game::enemySpeedIncreaseRate * Game::enemiesDestroyed));
        }
    }


}

void Game::updateCombat()
{	//Usuwanie wroga przy zestrzeleniu
	for (int i = 0; i < this->enemies.size(); ++i) //Petla iterujaca po wszystkich obiektach w wektorze 'Enemies'
	{
		bool enemy_deleted = false; //zmienna sledzaca, czy wrog juz zostal usuniety
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++) //Uzywamy wektora bullet w petli, size_t do deklaracji k w petli, ktora iteruje wektor pociskow, pêtla wzgledem wszystkik pociskow. Petla sprawdza, czy pocisk przecina obszar wroga
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())) //Sprawdza kolizje dwoch wektorow, intersect to funkcja przeciecia
			{
				this->points += this->enemies[i]->getPoints(); //Dodaje punkty za trafienie
				this->enemiesDestroyed++; // Zwiêksz licznik zniszczonych wrogów

				delete this->enemies[i];  //Because enemies are dynamic, so I delete them first
				this->enemies.erase(this->enemies.begin() + i); //then erase from the Vector

				delete this->bullets[k];  //Because bullets are dynamic, so I delete them first
				this->bullets.erase(this->bullets.begin() + k); //then erase from the Vector
				
				enemy_deleted = true;	//Przerywa petle wewnetrzna, poniewaz wrog zostal juz trafiony i usuniety
			}
		}
	}
}

void Game::update() //Game updates, positions etc 
{
	this->updateInput();

	this->player->update();

	this->updateKolizja();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();
	
	this->updateSwiat();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderSwiat()
{
	this->window->draw(this->worldBcg);
}

void Game::render() //Draws (renders) all the updated stuff
{
	this->window->clear(); 

	//Draw background
	this->renderSwiat();

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

	this->renderGUI();

	//napis Koniec Gry!
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}