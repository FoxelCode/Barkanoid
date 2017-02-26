#pragma once

#include "Engine/GameObject.hpp"
#include "Brick.hpp"

class Level : public GameObject
{
public:
	Level(sf::Vector2f pos, sf::Vector2f maxArea);
	~Level();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void RemoveDead();
	void ClearLevel();
	void LoadLevel(std::string levelName);

	sf::Color GetBGColour() { return bgColour; }

private:
	void CreateBricks(int* variants, int* colours, sf::Vector2u size);
	void AddBrick(Brick* brick);
	void RemoveBrick(Brick* brick);

	std::vector<Brick*> bricks;
	sf::Vector2f maxArea;
	sf::Color bgColour;
};