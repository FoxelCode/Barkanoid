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
	: GameObject(pos), originPos(pos), maxArea(maxArea), bgColour(sf::Color::Black)
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
	for (size_t y = 0; y < size.y; y++)
	{
		for (size_t x = 0; x < size.x; x++)
		{
			if (bricks[y][x] != nullptr)
			{
				if (!bricks[y][x]->IsAlive())
				{
					RemoveBrick(sf::Vector2u(x, y));
				}
			}
		}
	}
}

void Stage::Clear()
{
	static_cast<ListCollider*>(collider)->Clear();
	for (size_t y = 0; y < size.y; y++)
	{
		for (size_t x = 0; x < size.x; x++)
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

	std::vector<std::vector<int>> brickValues;
	for (size_t i = 1; i < stageData.size(); i++)
	{
		std::vector<int> row = StringUtil::MakeIndices(stageData[i]);
		brickValues.push_back(row);
	}

	// Set brick count back to 0 before adding new ones
	brickCount = 0;
}

void Stage::CreateBrick(int variant, sf::Vector2u pos)
{
	sf::Vector2f brickPos = sf::Vector2f((int)(pos.x * Brick::brickSize.x), (int)(pos.y * Brick::brickSize.y));
	// Special bricks are denoted with lower case ascii characters, starting with 'a'
	if (variant >= 'a')
	{
		if (variant == SolidBrick::id)
			AddBrick(new SolidBrick(brickPos), pos);
		else if (variant == InvisibleBrick::id)
			AddBrick(new InvisibleBrick(brickPos), pos);
		else if (variant == ExplosiveBrick::id)
			AddBrick(new ExplosiveBrick(brickPos, std::bind(&Stage::Explode, this, std::placeholders::_1)), pos);
	}
	else if (variant > 0)
		AddBrick(new RegularBrick(brickPos, variant - 1), pos);
}

void Stage::AddBrick(Brick* brick, sf::Vector2u pos)
{
	if (bricks[pos.y][pos.x] != nullptr)
		RemoveBrick(pos);
	bricks[pos.y][pos.x] = brick;
	brick->SetParent(this);
	static_cast<ListCollider*>(collider)->AddCollider(brick->GetCollider());

	// Don't count solid bricks towards the brickCount, as they can't be destroyed at all
	if (dynamic_cast<SolidBrick*>(brick))
		return;
	brickCount++;
}

void Stage::RemoveBrick(sf::Vector2u pos)
{
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
	/*bool found = false;
	sf::Vector2i index;
	for (size_t y = 0; y < size.y; y++)
	{
		for (size_t x = 0; x < size.x; x++)
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

	for (size_t y = 0; y < size.y; y++)
	{
		for (size_t x = 0; x < size.x; x++)
		{
			if (x >= (index.x - 1) && x <= (index.x + 1)
				&& y >= (index.y - 1) && y <= (index.y + 1))
			{
				if (bricks[y][x] != nullptr && bricks[y][x]->IsAlive())
					bricks[y][x]->Kill();
			}
		}
	}*/
}
