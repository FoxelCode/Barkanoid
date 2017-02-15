#pragma once

#include "GameObject.hpp"
#include "Brick.hpp"

class Level : public GameObject
{
public:
	Level(sf::Vector2f pos);
	virtual void Update(float delta);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void AddBrick(Brick* brick);
	void RemoveBrick(Brick* brick);

private:
	std::vector<Brick*> bricks;
};