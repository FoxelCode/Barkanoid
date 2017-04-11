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
	void InitialiseBricks(const std::vector<std::vector<int>>& brickVariants);
	void CreateRow(size_t rowIndex, const std::vector<int>& rowVariants);
	Brick* CreateBrick(int variant);
	void AddBrick(Brick* brick, sf::Vector2u pos);
	void RemoveBrick(sf::Vector2u pos);

	/// <summary>
	/// <para>Detonates a brick, destroying it and other bricks around it.</para>
	/// </summary>
	void Explode(Brick* brick);

	std::vector<std::vector<Brick*>> bricks;
	size_t brickCount;
	sf::Vector2f originPos;
	sf::Vector2f maxArea;
	size_t rowCount;
	sf::Color bgColour;
};