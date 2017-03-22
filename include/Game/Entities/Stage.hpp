#pragma once

#include "Engine/GameObject.hpp"
#include "Bricks/Brick.hpp"

class Stage : public GameObject
{
public:
	Stage(sf::Vector2f pos, sf::Vector2f maxArea);
	~Stage();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void RemoveDead();
	void Clear();
	void Load(std::vector<std::string> stageData);

	sf::Color GetBGColour() { return bgColour; }
	size_t GetBrickCount() { return brickCount; }

private:
	void CreateBrick(int variant, sf::Vector2u pos);
	void AddBrick(Brick* brick, sf::Vector2u pos);
	void RemoveBrick(sf::Vector2u pos);

	void Explode(Brick* brick);

	std::vector<std::vector<Brick*>> bricks;
	size_t brickCount;
	sf::Vector2f originPos;
	sf::Vector2f maxArea;
	sf::Vector2u size;
	sf::Color bgColour;
};