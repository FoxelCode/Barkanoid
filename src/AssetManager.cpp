#include "AssetManager.hpp"

#include <fstream>

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
	tex->loadFromFile("res\\gfx\\" + filename);
	textures.insert(std::pair<std::string, sf::Texture*>(filename, tex));
	return tex;
}

std::string AssetManager::GetLevel(std::string filename)
{
	std::string output;
	std::string line;
	std::ifstream inFile;
	inFile.open("res\\lvl\\" + filename);
	if (!inFile.is_open())
		return "";
	while (!inFile.eof())
	{
		std::getline(inFile, line);
		output += line;
	}
	inFile.close();
	return output;
}
