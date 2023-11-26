#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animState = IDLE;
	this->movingX = false;
	this->movingY = false;
}

void Player::initTexture()
{
	if (!this->walk.loadFromFile("Textures/Woodcutter/Woodcutter_walk.png"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD THE PLAYER SHEET!" << "\n";
	if (!this->idle.loadFromFile("Textures/Woodcutter/Woodcutter_idle.png"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD THE PLAYER SHEET!" << "\n";
	if (!this->jump.loadFromFile("Textures/Woodcutter/Woodcutter_jump.png"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD THE PLAYER SHEET!" << "\n";
	if (!this->run.loadFromFile("Textures/Woodcutter/Woodcutter_run.png"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD THE PLAYER SHEET!" << "\n";
}

void Player::initSprite()
{
	this->sprite.setTexture(this->idle);
	this->currentFrame = sf::IntRect(0, 0, 48, 48);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(3.f, 3.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 5.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.92f;
	this->gravity = 4.f;
	this->velocityMaxY = 5.f;
	this->velocity.x = 0;
	this->velocity.y = 0;

}

Player::Player()
{
	this->initVariables();
	this->initAnimations();
	this->initTexture();
	this->initSprite();
	this->initPhysics();
}

Player::~Player()
{
}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;
	
	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;

}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	this->velocity.x += dir_x * this->acceleration;
	

	if (std::abs(this->velocity.x) < this->velocityMax) {
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}


void Player::updatePhysics()
{
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.y) < this->velocityMaxY) {
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	this->sprite.move(this->velocity.x, 0.f);

	this->velocity *= this->drag;

	if (std::abs(this->velocity.x) < this->velocityMin) {
		this->velocity.x = 0.f;
	}

	if (std::abs(this->velocity.y) < this->velocityMin) {
		this->velocity.y = 0.f;
	}

	this->sprite.move(0.f, this->velocity.y);
}


void Player::updateMovement()
{
	this->animState = IDLE;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		this->velocity.x = -6.f;
		this->animState = MOVING_LEFT;
		this->sprite.setScale(-3.f, 3.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 5.f, 0.f);
		this->animationSwitch = true;
		this->movingX = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		this->velocity.x = 6.f;
		this->animState = MOVING_RIGHT;
		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin( 0.f, 0.f);
		this->animationSwitch = true;
		this->movingX = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		this->velocity.y = -8.f;
		this->animState = JUMPING;
		this->animationSwitch = true;
		this->movingY = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->movingY) {
		this->velocity.y = 8.f;
		this->animationSwitch = true;
		this->movingY = true;
	}

	if (this->velocity.y == 0.f) {
		this->movingY = false;
	}
}

void Player::updateAnimations()
{
	if (this->animState == IDLE) {
		this->sprite.setTexture(this->idle);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
				this->currentFrame.left += 48.f;
				if (this->currentFrame.left >= 144.f) 
					this->currentFrame.left = 0;
				
			
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == MOVING_RIGHT) {
		this->sprite.setTexture(this->run);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			
			this->currentFrame.left += 48.f;
			if (this->currentFrame.left >= 240.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}

	else if (this->animState == MOVING_LEFT) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			this->sprite.setTexture(this->run);
			this->currentFrame.left += 48.f;
			if (this->currentFrame.left >= 240.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-3.f, 3.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width/5.f, 0.f);
	}

	else if (this->animState == JUMPING) {
		this->sprite.setTexture(this->jump);
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			this->currentFrame.left += 48.f;
			if (this->currentFrame.left >= 240.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(2.f);
	circ.setPosition(this->sprite.getPosition());

	target.draw(circ);
}
