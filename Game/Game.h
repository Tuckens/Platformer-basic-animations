#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "SwagBall.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	void initWindow();
	void intVariables();
	void initFonts();
	void initText();

public:
	Game();
	~Game();

	const bool& getEndGame() const;


	//Functions

	const bool running() const;
	void pollEvents();

	void spawnSwagBalls();
	const int randBallType() const;
	void updateCollision();
	void updateGui();
	void updatePlayer();
	void update();
	void renderGui(sf::RenderTarget* target);
	void render();


};

