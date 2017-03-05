#pragma once

#include "Engine/GameObject.hpp"
#include "Brick.hpp"

class Stage : public GameObject
{
public:
	Stage(sf::Vector2f pos, sf::Vector2f maxArea);
	~Stage();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void RemoveDead();
	void Clear();
	void Load(std::string stageData);

	sf::Color GetBGColour() { return bgColour; }
	size_t GetBrickCount() { return brickCount; }

private:
	void InitBricks();
	void CreateBricks(int* variants, int* colours);
	void AddBrick(Brick* brick, sf::Vector2u pos);
	void RemoveBrick(sf::Vector2u pos);

	std::vector<std::vector<Brick*>> bricks;
	size_t brickCount;
	sf::Vector2f originPos;
	sf::Vector2f maxArea;
	sf::Vector2u size;
	sf::Color bgColour;
};