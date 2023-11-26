#include "stdafx.h"
#include "Tile.h"



Tile::Tile(sf::Texture& run, sf::Texture& walk, sf::Texture& jump, sf::Texture& idle, sf::Texture& hurt, sf::IntRect texture_rect, bool damaging)
	:damaging(damaging)
{
	this->sprite.setTexture(run);

}

const sf::FloatRect Tile::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

Tile::~Tile()
{
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
