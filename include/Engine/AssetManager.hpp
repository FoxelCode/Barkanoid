#pragma once

#include <map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class AssetManager
{
public:
	~AssetManager();
	sf::Texture* GetTexture(std::string filename);
	sf::Font* GetFont(std::string filename);
	std::string GetLevel(std::string filename);

private:
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Font*> fonts;
};