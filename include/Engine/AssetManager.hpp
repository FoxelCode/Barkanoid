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
	std::string GetLevel(std::string levelName);
	std::string GetStage(std::string levelName, std::string stageName);

private:
	std::string ReadFile(std::string path);

	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Font*> fonts;

	static const std::string levelFileExtension;
	static const std::string stageFileExtension;
};