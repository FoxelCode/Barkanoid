#pragma once

#include "GameObject.hpp"
#include "Brick.hpp"

class Level : public GameObject
{
public:
	Level(sf::Vector2f pos);
	virtual void Update(float delta);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void LoadLevel(int* variants, int* colours, sf::Vector2u size);
	sf::Color GetBGColour() { return bgColour; }

private:
	void AddBrick(Brick* brick);
	void RemoveBrick(Brick* brick);

	std::vector<Brick*> bricks;
	sf::Color bgColour;
};