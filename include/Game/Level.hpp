#pragma once

#include "Engine/GameObject.hpp"
#include "Brick.hpp"

class Level : public GameObject
{
public:
	Level(sf::Vector2f pos, sf::Vector2u size);
	~Level();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void RemoveDead();
	void ClearLevel();
	void LoadLevel(std::string levelName);

	sf::Color GetBGColour() { return bgColour; }

private:
	void CreateBricks(int* variants, int* colours);
	void AddBrick(Brick* brick, sf::Vector2u pos);
	void RemoveBrick(sf::Vector2u pos);

	std::vector<std::vector<Brick*>> bricks;
	sf::Vector2u size;
	sf::Color bgColour;
};