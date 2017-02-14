#include "AssetManager.hpp"

AssetManager::~AssetManager()
{
	for each (std::pair<std::string, sf::Texture*> texPair in textures)
	{
		delete texPair.second;
	}
}

sf::Texture* AssetManager::GetTexture(std::string filename)
{
	std::map<std::string, sf::Texture*>::iterator it = textures.find(filename);
	if (it != textures.end())
		return it->second;
	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile("res\\" + filename);
	textures.insert(std::pair<std::string, sf::Texture*>(filename, tex));
	return tex;
}
