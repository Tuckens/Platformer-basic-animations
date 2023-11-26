#include "Game.h"

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(1536, 864);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::intVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	this->points = 0;

}

void Game::initFonts()
{
	if (!this->font .loadFromFile("Fonts/PixellettersFull.ttf")) {
		std::cout << "ERROR::GAME::INITFONT::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}

void Game::initText()
{

	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(80);
	this->endGameText.setPosition(sf::Vector2f(300, 400));
	this->endGameText.setString("YOU ARE DEAD, EXIT THE GAME!");
}

Game::Game()
{
	this->intVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool& Game::getEndGame() const
{
	return this->endGame;
}


//Functions


const bool Game::running() const
{
	return this->window->isOpen()/* && this->endGame == false */;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent)) {
		switch (this->sfmlEvent.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnSwagBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else {
		if (this->swagBalls.size() < this->maxSwagBalls) {
			this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));

			this->spawnTimer = 0.f;
		}
	}
}

const int Game::randBallType() const
{
	int type = SwagBallTypes::DEFAULT;
	int randValue = rand() & 100 + 1;
	if (randValue > 60 && randValue <= 80)
		type = SwagBallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = SwagBallTypes::HEALING;
	return type;
}

void Game::updateCollision()
{
	for (size_t i = 0; i < this->swagBalls.size(); i++) {
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds())) {
			switch (this->swagBalls[i].getType()) {
			case SwagBallTypes::DEFAULT:
				this->points++;
				break;
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(1);
				break;
			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
				break;


			}
			

			this->swagBalls.erase(this->swagBalls.begin() + i);
		}

	}
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
	   << "Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";

	this->guiText.setString(ss.str());
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;

}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false) {
		this->spawnSwagBalls();

		this->updatePlayer();

		this->updateCollision();
		this->updateGui();
	}
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render()
{
	this->window->clear();

	this->player.render(this->window);

	for (auto i : this->swagBalls) {
		i.render(*this->window);
	}

	this->renderGui(this->window);

	if (this->endGame)
		this->window->draw(this->endGameText);

	this->window->display();

}

