#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class AssetManager
{
public:
	~AssetManager();
	/// <summary>
	/// <para>Gets a texture with the given filename, loading and storing it if it isn't already.</para>
	/// </summary>
	/// <param name="filename">Texture filename. The file should be in /res/graphics.</param>
	/// <returns>Pointer to the loaded texture.</returns>
	sf::Texture* GetTexture(std::string filename);

	/// <summary>
	/// <para>Gets a font with the given filename, loading and storing it if it isn't already.</para>
	/// </summary>
	/// <param name="filename">Font filename. The file should be in /res/fonts.</param>
	/// <returns>Pointer to the loaded font.</returns>
	sf::Font* GetFont(std::string filename);

	/// <summary>
	/// <para>Returns a list of all the level files in /res/levels.</para>
	/// </summary>
	/// <returns>All the level files in /res/levels.</returns>
	std::vector<std::string> GetLevels();

	/// <summary>
	/// <para>Gets a level with the given name, loading and storing it if it isn't already.</para>
	/// </summary>
	/// <param name="levelName">Level name. Can have the file extension with it, but it'll be ignored.</param>
	/// <returns>The contents of the level file.</returns>
	const std::string& GetLevel(std::string levelName);

	/// <summary>
	/// <para>Gets a stage with the given name, within a level with the given name.</para>
	/// <para>Also loads the level data if it hasn't been loaded already.</para>
	/// </summary>
	/// <param name="levelName">Name of the level the stage is in.</param>
	/// <param name="stageName">Stage name.</param>
	/// <returns>A cluster of stage data.</returns>
	std::vector<std::string> GetStage(std::string levelName, std::string stageName);

private:
	// Assets, mapped to their filenames or names.
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, const std::string> levels;

	static const std::string levelFileExtension;
};