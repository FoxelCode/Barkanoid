#include "Level.hpp"

#include "ListCollider.hpp"
#include "Util.hpp"
#include "Log.hpp"

#include <array>

#include "json\json.hpp"
using json = nlohmann::json;

Level::Level(sf::Vector2f pos)
	: GameObject(pos), bgColour(Palette::Black)
{
	collider = new ListCollider(this);

	LoadLevel("level1");
}

void Level::Update(float delta)
{
	for (size_t i = 0; i < bricks.size(); )
	{
		if (!bricks[i]->IsAlive())
		{
			Brick* toErase = bricks[i];
			RemoveBrick(toErase);
			delete toErase;
		}
		else
		{
			i++;
		}
	}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for each (Brick* brick in bricks)
	{
		target.draw(*brick, states);
	}
}

void Level::LoadLevel(std::string levelName)
{
	std::string fileName = levelName + ".json";
	std::string levelData = Util::GetAssetManager()->GetLevel(fileName);
	json levelJson = json::parse(levelData.c_str());

	// Get level size
	sf::Vector2u levelSize = sf::Vector2u(14, 18);
	if (levelJson.find("size") != levelJson.end())
	{
		json sizeJson = levelJson["size"];
		if (sizeJson.find("width") != sizeJson.end())
			if (sizeJson["width"].is_number_unsigned())
				levelSize.x = sizeJson["width"].get<unsigned>();
		if (sizeJson.find("height") != sizeJson.end())
			if (sizeJson["height"].is_number_unsigned())
				levelSize.y = sizeJson["height"].get<unsigned>();
	}
	else
	{
		Log::Print("No [\"size\"] found in \"" + fileName + "\", assuming 14x18", "Level::LoadLevel", LogSeverity::Warning);
	}

	// Get variant data
	if (levelJson.find("brickVariants") != levelJson.end())
	{
		json variantJson = levelJson["brickVariants"];
		int* variantData = new int[levelSize.y * levelSize.x];
		if (variantJson.is_array())
		{
			size_t variantCount = variantJson.size();
			if (variantCount != levelSize.x * levelSize.y)
			{
				Log::Print("BrickVariants has " + std::to_string(variantCount) + " values (should be " + std::to_string(levelSize.x * levelSize.y) + ")", "Level::LoadLevel", LogSeverity::Error);
				return;
			}
		}
	}

	/*int* colourData = new int[levelSize.y * levelSize.x];
	json colours = levelJson["brickColours"];
	bgColour = Palette::Colours[levelJson["bgColour"].get<int>()];
	int index = 0;
	for (json::iterator it = variants.begin(); it != variants.end(); it++)
	{
		variantData[index] = it.value().get<int>();
		index++;
	}
	index = 0;
	for (json::iterator it = colours.begin(); it != colours.end(); it++)
	{
		colourData[index] = it.value().get<int>();
		index++;
	}
	CreateBricks(variantData, colourData, levelSize);*/
}

void Level::CreateBricks(int* variants, int* colours, sf::Vector2u size)
{
	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			if (variants[y * size.x + x] > 0)
				AddBrick(new Brick(sf::Vector2f(x * 32.0f, y * 16.0f), Palette::Colours[colours[y * size.x + x]], variants[y * size.x + x] - 1));
		}
	}
}

void Level::AddBrick(Brick* brick)
{
	bricks.push_back(brick);
	brick->SetParent(this);
	static_cast<ListCollider*>(collider)->AddCollider(brick->GetCollider());
}

void Level::RemoveBrick(Brick* brick)
{
	brick->SetParent(nullptr);
	for (auto it = bricks.begin(); it != bricks.end(); it++)
	{
		if ((*it) == brick)
		{
			bricks.erase(it);
			break;
		}
	}
	static_cast<ListCollider*>(collider)->RemoveCollider(brick->GetCollider());
}
