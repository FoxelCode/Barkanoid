#include "Engine/AssetManager.hpp"

#include <dirent.h>

#include "Util/StringUtil.hpp"
#include "Util/FileIO.hpp"

const std::string AssetManager::levelFileExtension = "owo";

AssetManager::~AssetManager()
{
	for (std::pair<std::string, sf::Texture*> texPair : textures)
		delete texPair.second;
	textures.clear();
	for (std::pair<std::string, sf::Font*> fntPair : fonts)
		delete fntPair.second;
	fonts.clear();
	levels.clear();
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
	std::vector<std::string> levelFiles;

	DIR* dir = opendir("res/levels/");
	struct dirent* entry = readdir(dir);
	while (entry != NULL)
	{
		// Enumerate all the level files in the levels folder
		if (entry->d_type == DT_REG)
		{
			std::string folderName = entry->d_name;
			if (folderName.find("." + levelFileExtension) != std::string::npos)
				levelFiles.push_back(folderName);
		}
		entry = readdir(dir);
	}
	closedir(dir);

	return levelFiles;
}

const std::string& AssetManager::GetLevel(std::string levelName)
{
	levelName = StringUtil::StripFileExtension(levelName);
	auto it = levels.find(levelName);
	if (it != levels.end())
		return it->second;
	std::string path = "res/levels/" + levelName + "." + levelFileExtension;
	std::string levelData = FileIO::ReadFile(path);
	auto newIt = levels.insert(std::pair<std::string, const std::string>(levelName, levelData));
	return (*newIt.first).second;
}

std::vector<std::string> AssetManager::GetStage(std::string levelName, std::string stageName)
{
	// Get the level data and break it up into clusters
	std::string data = GetLevel(levelName);
	std::vector<std::vector<std::string>> dataClusters = StringUtil::MakeClusters(StringUtil::Split(data));

	// Search the clusters for the correct stage name
	// Start at 1 because the first cluster should just be the stage list
	for (size_t i = 1; i < dataClusters.size(); i++)
	{
		// If the first line of the cluster matches the stage name, we want that
		if (dataClusters[i][0] == stageName)
			return dataClusters[i];
	}
	LOG_ERROR("No stage found with name \"" + stageName + "\" in level \"" + levelName + "\"");
	return std::vector<std::string>();
}