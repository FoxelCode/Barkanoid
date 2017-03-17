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

Stage::Stage(sf::Vector2f pos, sf::Vector2f maxArea)
	: GameObject(pos), originPos(pos), maxArea(maxArea), bgColour(Palette::Black)
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

void Stage::Load(std::string stageData)
{
	// Remove the old stage if one exists
	if (bricks.size() > 0U)
	{
		Clear();
	}
	
	if (stageData == "")
	{
		LOG_ERROR("Trying to load Stage with no data");
		return;
	}
	json stageJson = json::parse(stageData.c_str());

	// Get BG colour if one is given
	if (stageJson.find("bgColour") != stageJson.end())
	{
		if (stageJson["bgColour"].is_number_unsigned())
			bgColour = Palette::Colours[stageJson["bgColour"].get<unsigned>()];
		else
			LOG_WARNING("\"bgColour\" should be an unsigned integer, assuming 0");
	}
	else
		LOG_WARNING("No \"bgColour\" found, assuming 0");

	// Get level size
	size = sf::Vector2u((unsigned)(maxArea.x / Brick::brickSize.x), (unsigned)(maxArea.y / Brick::brickSize.y));
	if (stageJson.find("size") != stageJson.end())
	{
		json sizeJson = stageJson["size"];
		if (sizeJson.find("width") != sizeJson.end())
		{
			if (sizeJson["width"].is_number_unsigned())
				size.x = sizeJson["width"].get<unsigned>();
			else
				LOG_WARNING("\"width\" should be an unsigned integer, assuming " + std::to_string(size.x));
		}
		else
			LOG_WARNING("No \"width\" found in \"size\", assuming " + std::to_string(size.x));

		if (sizeJson.find("height") != sizeJson.end())
		{
			if (sizeJson["height"].is_number_unsigned())
				size.y = sizeJson["height"].get<unsigned>();
			else
				LOG_WARNING("\"height\" should be an unsigned integer, assuming " + std::to_string(size.y));
		}
		else
			LOG_WARNING("No \"height\" found in \"size\", assuming " + std::to_string(size.y));
	}
	else
		LOG_WARNING("No \"size\" found, assuming " + std::to_string(size.x) + "x" + std::to_string(size.y));

	// Set brick offset based on the level size
	sf::Vector2f newPos = originPos;
	newPos.x += maxArea.x / 2.0f - (size.x * Brick::brickSize.x) / 2.0f;
	SetPosition(newPos);

	// Get variant data
	int* variantData = new int[size.y * size.x];
	if (stageJson.find("brickVariants") != stageJson.end())
	{
		json variantJson = stageJson["brickVariants"];
		if (variantJson.is_array())
		{
			size_t variantCount = variantJson.size();
			if (variantCount != size.x * size.y)
			{
				LOG_ERROR("brickVariants has " + std::to_string(variantCount) + " values (should be " + std::to_string(size.x * size.y) + ")");
				return;
			}
			for (size_t y = 0; y < size.y; y++)
			{
				for (size_t x = 0; x < size.x; x++)
				{
					if (!variantJson.at(y * size.x + x).is_number_unsigned())
					{
						LOG_WARNING("brickVariants[" + std::to_string(x) + ", " + std::to_string(y) + "] should be an unsigned integer, assuming 0");
						variantData[y * size.x + x] = 0;
						continue;
					}
					variantData[y * size.x + x] = variantJson.at(y * size.x + x).get<unsigned>();
				}
			}
		}
		else
		{
			LOG_ERROR("brickVariants should be an array");
			return;
		}
	}
	else
	{
		LOG_ERROR("No \"brickVariants\" found");
		return;
	}

	// Initialise the brick 2D vector with the correct size
	InitBricks();

	// Set brick count back to 0 before adding new ones
	brickCount = 0;

	// Create the bricks according to JSON data
	CreateBricks(variantData);

	if (variantData != nullptr)
	{
		delete[] variantData;
		variantData = nullptr;
	}
}

void Stage::InitBricks()
{
	for (size_t y = 0; y < size.y; y++)
	{
		bricks.push_back(std::vector<Brick*>());
		for (size_t x = 0; x < size.x; x++)
		{
			bricks[y].push_back(nullptr);
		}
	}
}

void Stage::CreateBricks(int* variants)
{
	for (size_t y = 0; y < size.y; y++)
	{
		for (size_t x = 0; x < size.x; x++)
		{
			int brickIndex = variants[y * size.x + x];
			// Special bricks are denoted with lower case ascii characters, starting with 'a'
			if (brickIndex >= 'a')
			{
				if (brickIndex == SolidBrick::id)
					AddBrick(new SolidBrick(sf::Vector2f(x * 32.0f, y * 16.0f)), sf::Vector2u(x, y));
				else if (brickIndex == InvisibleBrick::id)
					AddBrick(new InvisibleBrick(sf::Vector2f(x * 32.0f, y * 16.0f)), sf::Vector2u(x, y));
				else if (brickIndex == ExplosiveBrick::id)
					AddBrick(new ExplosiveBrick(sf::Vector2f(x * 32.0f, y * 16.0f), std::bind(&Stage::Explode, this, std::placeholders::_1)), sf::Vector2u(x, y));
			}
			else if (brickIndex > 0)
				AddBrick(new RegularBrick(sf::Vector2f(x * 32.0f, y * 16.0f), variants[y * size.x + x] - 1), sf::Vector2u(x, y));
		}
	}
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
	bool found = false;
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
	}
}
