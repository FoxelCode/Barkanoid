#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class AssetManager
{
public:
	~AssetManager();
	sf::Texture* GetTexture(std::string filename);
	sf::Font* GetFont(std::string filename);
	std::vector<std::string> GetLevels();
	const std::string& GetLevel(std::string levelName);
	std::vector<std::string> GetStage(std::string levelName, std::string stageName);

private:
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, const std::string> levels;

	static const std::string levelFileExtension;
};