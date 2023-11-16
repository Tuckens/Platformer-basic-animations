#pragma once
class Tile
{
private:


	sf::Sprite sprite;
	bool damaging;


public:

	Tile(sf::Texture& run,
		 sf::Texture& walk,
		 sf::Texture& jump,
		 sf::Texture& idle,
		 sf::Texture& hurt,
		 sf::IntRect texture_rect,
		 const bool damaging = false);

	const sf::FloatRect getGlobalBounds();
	virtual ~Tile();


	void update();
	void render(sf::RenderTarget& target);
};

