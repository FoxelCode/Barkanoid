#include "Game/Level.hpp"

#include <array>

#include "json\json.hpp"
using json = nlohmann::json;

#include "Collision/ListCollider.hpp"
#include "Engine/G.hpp"
#include "Util/Log.hpp"

Level::Level(sf::Vector2f pos, sf::Vector2f maxArea)
	: GameObject(pos), originPos(pos), maxArea(maxArea), bgColour(Palette::Black)
{
	collider = new ListCollider(this);

	LoadLevel("level2");
}

Level::~Level()
{
	ClearLevel();
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
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

void Level::RemoveDead()
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

void Level::ClearLevel()
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

void Level::LoadLevel(std::string levelName)
{
	std::string fileName = levelName + ".json";
	std::string levelData = G::GetAssetManager()->GetLevel(fileName);
	if (levelData == "")
	{
		LOG_ERROR("No data found for " + levelName);
		return;
	}
	json levelJson = json::parse(levelData.c_str());

	// Get BG colour if one is given
	if (levelJson.find("bgColour") != levelJson.end())
	{
		if (levelJson["bgColour"].is_number_unsigned())
			bgColour = Palette::Colours[levelJson["bgColour"].get<unsigned>()];
		else
			LOG_WARNING("\"bgColour\" should be an unsigned integer, assuming 0");
	}
	else
		LOG_WARNING("No \"bgColour\" found in \"" + fileName + "\", assuming 0");

	// Get level size
	size = sf::Vector2u(maxArea.x / Brick::brickSize.x, maxArea.y / Brick::brickSize.y);
	if (levelJson.find("size") != levelJson.end())
	{
		json sizeJson = levelJson["size"];
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
		LOG_WARNING("No \"size\" found in \"" + fileName + "\", assuming " + std::to_string(size.x) + "x" + std::to_string(size.y));

	// Set brick offset based on the level size
	sf::Vector2f newPos = originPos;
	newPos.x += maxArea.x / 2.0f - (size.x * Brick::brickSize.x) / 2.0f;
	SetPosition(newPos);

	// Get variant data
	int* variantData = new int[size.y * size.x];
	if (levelJson.find("brickVariants") != levelJson.end())
	{
		json variantJson = levelJson["brickVariants"];
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
		LOG_ERROR("No \"brickVariants\" found in \"" + fileName + "\"");
		return;
	}

	// Get colour data
	int* colourData = new int[size.y * size.x];
	if (levelJson.find("brickVariants") != levelJson.end())
	{
		json colourJson = levelJson["brickColours"];
		if (colourJson.is_array())
		{
			size_t colourCount = colourJson.size();
			if (colourCount != size.x * size.y)
			{
				LOG_ERROR("brickColours has " + std::to_string(colourCount) + " values (should be " + std::to_string(size.x * size.y) + ")");
				return;
			}
			for (size_t y = 0; y < size.y; y++)
			{
				for (size_t x = 0; x < size.x; x++)
				{
					if (!colourJson.at(y * size.x + x).is_number_unsigned())
					{
						LOG_WARNING("brickColours[" + std::to_string(x) + ", " + std::to_string(y) + "] should be an unsigned integer, assuming 0");
						colourData[y * size.x + x] = 0;
						continue;
					}
					colourData[y * size.x + x] = colourJson.at(y * size.x + x).get<unsigned>();
				}
			}
		}
		else
		{
			LOG_ERROR("brickColours should be an array");
			return;
		}
	}
	else
	{
		LOG_ERROR("No \"brickColours\" found in \"" + fileName + "\"");
		return;
	}

	// Initialise the brick 2D vector with the correct size
	InitBricks();

	// Create the bricks according to JSON data
	CreateBricks(variantData, colourData);

	if (variantData != nullptr)
	{
		delete[] variantData;
		variantData = nullptr;
	}
	if (colourData != nullptr)
	{
		delete[] colourData;
		colourData = nullptr;
	}
}

void Level::InitBricks()
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

void Level::CreateBricks(int* variants, int* colours)
{
	for (size_t y = 0; y < size.y; y++)
	{
		for (size_t x = 0; x < size.x; x++)
		{
			if (variants[y * size.x + x] > 0)
				AddBrick(new Brick(sf::Vector2f(x * 32.0f, y * 16.0f), Palette::Colours[colours[y * size.x + x]], variants[y * size.x + x] - 1), sf::Vector2u(x, y));
		}
	}
}

void Level::AddBrick(Brick* brick, sf::Vector2u pos)
{
	if (bricks[pos.y][pos.x] != nullptr)
		RemoveBrick(pos);
	bricks[pos.y][pos.x] = brick;
	brick->SetParent(this);
	static_cast<ListCollider*>(collider)->AddCollider(brick->GetCollider());
}

void Level::RemoveBrick(sf::Vector2u pos)
{
	bricks[pos.y][pos.x]->SetParent(nullptr);
	static_cast<ListCollider*>(collider)->RemoveCollider(bricks[pos.y][pos.x]->GetCollider());
	if (bricks[pos.y][pos.x] != nullptr)
		delete bricks[pos.y][pos.x];
	bricks[pos.y][pos.x] = nullptr;
}
