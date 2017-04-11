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

	/// <summary>
	/// <para>Loads all .wav files from /res/sounds.</para>
	/// <para>This is done so the game doesn't have to load these sounds (and possibly cause lag) when they're first played.</para>
	/// </summary>
	void PreloadSounds();

	/// <summary>
	/// <para>Plays a music file with the given filename.</para>
	/// </summary>
	/// <param name="fileName">Music filename.</param>
	/// <param name="reset">If false and the music file with the given name is already playing, it won't restart from the beginning. When true, the music will start from the beginning.</param>
	void PlayMusic(const std::string& fileName, bool reset = true);

	/// <summary>
	/// <para>Plays a sound with the given filename from the list of sounds already loaded with PreloadSounds.</para>
	/// </summary>
	/// <param name="fileName">Sound filename.</param>
	void PlaySound(const std::string& fileName);

	void SetMute(bool mute);
	void ToggleMute();

private:
	static const std::string musicPath;
	static const std::string soundPath;
	/// <summary>
	/// <para>Max amount of instances of the same sound that can play at the same time.</para>
	/// </summary>
	static const size_t maxSoundsPerFile;
	static const float musicVolume;

	bool mute;

	sf::Music music;
	std::string currentMusicFileName;

	std::map<std::string, sf::SoundBuffer*> soundBuffers;
	std::map<std::string, std::vector<sf::Sound*>> sounds;
};