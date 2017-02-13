#pragma once

#include <map>
#include <SFML\Graphics\Texture.hpp>

class AssetManager
{
public:
	~AssetManager();
	sf::Texture* loadTexture(std::string filename);

private:
	std::map<std::string, sf::Texture*> textures;
};