#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 8.f;
	this->hpMax = 10;
	this->hp = hpMax;
	
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));

}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{
}

const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
		this->shape.move(-this->movementSpeed, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->shape.move(this->movementSpeed, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->shape.move(0.f, -this->movementSpeed);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->shape.move(0.f, this->movementSpeed);
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{

	
	if (this->shape.getGlobalBounds().left < 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);

	if (this->shape.getGlobalBounds().top < 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{

	updateInput();

	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
