#pragma once

enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING };

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture run;
	sf::Texture walk;
	sf::Texture jump;
	sf::Texture idle;
	sf::Texture hurt;

	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;


	bool movingX;
	bool movingY;

	sf::Clock animationTimer;

	bool animationSwitch;
	short animState;
	sf::IntRect currentFrame;

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	Player();
	virtual ~Player();

	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;


	void setPosition(const float x, const float y);
	void resetVelocityY();

	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

