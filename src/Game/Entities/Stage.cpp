#include "Game/Entities/Stage.hpp"

#include <array>

#include "JSON\json.hpp"
using json = nlohmann::json;

#include "Collision/ListCollider.hpp"
#include "Engine/G.hpp"
#include "Game/Entities/Bricks/RegularBrick.hpp"
#include "Game/Entities/Bricks/SolidBrick.hpp"
#include "Game/Entities/Bricks/InvisibleBrick.hpp"
#include "Game/Entities/Bricks/ExplosiveBrick.hpp"
#include "Util/StringUtil.hpp"

Stage::Stage(sf::Vector2f pos, sf::Vector2f maxArea)
	: GameObject(pos), brickCount(0U), originPos(pos), maxArea(maxArea), rowCount(0U), bgColour(sf::Color::Black)
{
	collider = new ListCollider(this);
}

Stage::~Stage()
{
	Clear();
}

void Stage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for each (std::vector<Brick*> row in bricks)
	{
		for each (Brick* brick in row)
		{
			if (brick != nullptr)
				target.draw(*brick, states);
		}
	}
}

void Stage::RemoveDead()
{
	size_t rowSize;
	for (size_t y = 0; y < rowCount; y++)
	{
		rowSize = bricks[y].size();
		for (size_t x = 0; x < rowSize; x++)
		{
			if (bricks[y][x] != nullptr && !bricks[y][x]->IsAlive())
			{
				RemoveBrick(sf::Vector2u(x, y));
			}
		}
	}
}

void Stage::Clear()
{
	static_cast<ListCollider*>(collider)->Clear();
	size_t rowSize;
	for (size_t y = 0; y < rowCount; y++)
	{
		rowSize = bricks[y].size();
		for (size_t x = 0; x < rowSize; x++)
		{
			delete bricks[y][x];
			bricks[y][x] = nullptr;
		}
		bricks[y].clear();
	}
	bricks.clear();
}

void Stage::Load(std::vector<std::string> stageData)
{
	// Remove the old stage if one exists
	if (!bricks.empty())
		Clear();
	
	if (stageData.empty())
	{
		LOG_ERROR("Trying to load Stage with no data");
		return;
	}

	// Extract integer values for bricks from the stage data
	std::vector<std::vector<int>> brickValues;
	for (size_t i = 1; i < stageData.size(); i++)
	{
		std::vector<int> row = StringUtil::MakeIndices(stageData[i]);
		brickValues.push_back(row);
	}

	// Set brick count back to 0 before adding new ones
	brickCount = 0;

	// Check that the level only has rows with one size
	if (brickValues.size() == 0)
	{
		LOG_ERROR("Can't load stage with no rows in brickValues");
		return;
	}
	else
	{
		size_t rowSize = brickValues[0].size();
		for (size_t row = 1; row < brickValues.size(); row++)
		{
			if (brickValues[row].size() != rowSize)
			{
				LOG_ERROR("Can't load stage with non-uniform row sizes");
				return;
			}
		}
	}

	InitialiseBricks(brickValues);
	rowCount = brickValues.size();

	// Create brick rows based on stage data
	for (size_t row = 0; row < rowCount; row++)
	{
		CreateRow(row, brickValues[row]);
	}
}

void Stage::InitialiseBricks(const std::vector<std::vector<int>>& brickVariants)
{
	for (const std::vector<int>& row : brickVariants)
	{
		bricks.push_back(std::vector<Brick*>(row.size()));
	}
}

void Stage::CreateRow(size_t rowIndex, const std::vector<int>& rowVariants)
{
	if (rowIndex >= rowCount)
	{
		LOG_ERROR("Can't create row " + std::to_string(rowIndex) + " because the stage only has " + std::to_string(rowCount) + " rows");
		return;
	}

	float rowXOffset = maxArea.x / 2.0f - ((float)rowVariants.size() / 2.0f) * (float)Brick::brickSize.x;

	for (size_t x = 0; x < rowVariants.size(); x++)
	{
		if (rowVariants[x] > 0U)
		{
			Brick* brick = CreateBrick(rowVariants[x]);
			brick->SetPosition(sf::Vector2f(x * (float)Brick::brickSize.x + rowXOffset, rowIndex * (float)Brick::brickSize.y));
			AddBrick(brick, sf::Vector2u(x, rowIndex));
		}
	}
}

Brick* Stage::CreateBrick(int variant)
{
	// Special bricks are denoted with lower case ascii characters, starting with 'a'
	if (variant >= 'a')
	{
		if (variant == SolidBrick::id)
			return new SolidBrick(sf::Vector2f());
		else if (variant == InvisibleBrick::id)
			return new InvisibleBrick(sf::Vector2f());
		else if (variant == ExplosiveBrick::id)
			return new ExplosiveBrick(sf::Vector2f(), std::bind(&Stage::Explode, this, std::placeholders::_1));
	}
	else if (variant > 0)
		return new RegularBrick(sf::Vector2f(), variant - 1);
	return nullptr;
}

void Stage::AddBrick(Brick* brick, sf::Vector2u pos)
{
	if (bricks[pos.y][pos.x] != nullptr)
	{
		if (dynamic_cast<SolidBrick*>(bricks[pos.y][pos.x]) == nullptr)
			brickCount--;
		RemoveBrick(pos);
	}

	bricks[pos.y][pos.x] = brick;
	brick->SetParent(this);
	static_cast<ListCollider*>(collider)->AddCollider(brick->GetCollider());

	// Don't count solid bricks towards the brickCount, as they can't be destroyed
	if (dynamic_cast<SolidBrick*>(brick))
		return;
	brickCount++;
}

void Stage::RemoveBrick(sf::Vector2u pos)
{
	if (pos.y >= rowCount || pos.x >= bricks[pos.y].size())
	{
		LOG_ERROR("(" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") is outside the Stage");
		return;
	}

	if (bricks[pos.y][pos.x] != nullptr)
	{
		bricks[pos.y][pos.x]->SetParent(nullptr);
		static_cast<ListCollider*>(collider)->RemoveCollider(bricks[pos.y][pos.x]->GetCollider());
		delete bricks[pos.y][pos.x];
		bricks[pos.y][pos.x] = nullptr;
		brickCount--;
	}
}

void Stage::Explode(Brick* brick)
{
	bool found = false;
	sf::Vector2i index;
	size_t rowSize;
	for (size_t y = 0; y < rowCount; y++)
	{
		rowSize = bricks[y].size();
		for (size_t x = 0; x < rowSize; x++)
		{
			if (bricks[y][x] == brick)
			{
				found = true;
				index = sf::Vector2i(x, y);
				break;
			}
		}
		if (found) break;
	}
	if (!found)
	{
		LOG_ERROR("Trying to explode a brick that doesn't exist");
		return;
	}

	for (size_t y = 0; y < rowCount; y++)
	{
		rowSize = bricks[y].size();
		for (size_t x = 0; x < rowSize; x++)
		{
			if (x >= (index.x - 1) && x <= (index.x + 1)
				&& y >= (index.y - 1) && y <= (index.y + 1))
			{
				if (bricks[y][x] != nullptr && bricks[y][x]->IsAlive())
					bricks[y][x]->Kill();
			}
		}
	}
}
