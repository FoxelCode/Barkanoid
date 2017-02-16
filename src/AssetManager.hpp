#pragma once

#include <map>
#include <SFML\Graphics\Texture.hpp>

class AssetManager
{
public:
	~AssetManager();
	sf::Texture* GetTexture(std::string filename);
	std::string GetLevel(std::string filename);

private:
	std::map<std::string, sf::Texture*> textures;
};