#pragma once

#include <map>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	void PreloadSounds();

	void PlayMusic(const std::string& fileName, bool reset = true);
	void PlaySound(const std::string& fileName);

private:
	static const std::string musicPath;
	static const std::string soundPath;
	static const size_t maxSoundsPerFile;

	sf::Music music;
	std::string currentMusicFileName;

	std::map<std::string, sf::SoundBuffer*> soundBuffers;
	std::map<std::string, std::vector<sf::Sound*>> sounds;
};