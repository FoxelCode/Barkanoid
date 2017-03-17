#include "Engine/AssetManager.hpp"

#include <fstream>
#include <dirent.h>

const std::string AssetManager::levelFileExtension = "owo";
const std::string AssetManager::stageFileExtension = "uwu";

AssetManager::~AssetManager()
{
	for each (std::pair<std::string, sf::Texture*> texPair in textures)
	{
		delete texPair.second;
	}
	textures.clear();
	for each (std::pair<std::string, sf::Font*> fntPair in fonts)
	{
		delete fntPair.second;
	}
	fonts.clear();
}

sf::Texture* AssetManager::GetTexture(std::string filename)
{
	std::map<std::string, sf::Texture*>::iterator it = textures.find(filename);
	if (it != textures.end())
		return it->second;
	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile("res/graphics/" + filename);
	textures.insert(std::pair<std::string, sf::Texture*>(filename, tex));
	return tex;
}

sf::Font* AssetManager::GetFont(std::string filename)
{
	std::map<std::string, sf::Font*>::iterator it = fonts.find(filename);
	if (it != fonts.end())
		return it->second;
	sf::Font* fnt = new sf::Font();
	fnt->loadFromFile("res/fonts/" + filename);
	fonts.insert(std::pair<std::string, sf::Font*>(filename, fnt));
	return fnt;
}

std::vector<std::string> AssetManager::GetLevels()
{
	std::vector<std::string> folders;

	DIR* dir = opendir("res/levels/");
	struct dirent* entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			// Ignore the folder itself and its parent
			std::string folderName = entry->d_name;
			if (folderName != "." && folderName != "..")
				folders.push_back(folderName);
		}
		entry = readdir(dir);
	}
	closedir(dir);

	return folders;
}

std::string AssetManager::GetLevel(std::string levelName)
{
	std::string path = "res/levels/" + levelName + "/level." + levelFileExtension;
	return ReadFile(path);
}

std::string AssetManager::GetStage(std::string levelName, std::string stageName)
{
	std::string path = "res/levels/" + levelName + "/" + stageName + "." + stageFileExtension;
	return ReadFile(path);
}

std::string AssetManager::ReadFile(std::string path)
{
	std::string output;
	std::string line;
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.is_open())
	{
		LOG_ERROR("Couldn't open file: " + path);
		return "";
	}

	while (!inFile.eof())
	{
		std::getline(inFile, line);
		output += line + "\n";
	}
	output.pop_back();
	inFile.close();
	return output;
}
