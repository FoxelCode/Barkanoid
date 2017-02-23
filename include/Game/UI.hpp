#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Paddle.hpp"

class UI : public sf::Drawable
{
public:
	UI(sf::Vector2u size);
	~UI();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void SetLives(size_t amount);

private:
	sf::Vector2u size;

	std::vector<Paddle*> lives;
	sf::Vector2f livesPos;
	float livesSpacing;
	float lifeWidth;
};