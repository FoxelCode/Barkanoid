#pragma once

#include "Game.hpp"
#include "AssetManager.hpp"
#include "AudioManager.hpp"

class G
{
public:
	static void SetGame(Game* game)
	{
		ASSERT(G::game == nullptr);
		G::game = game;
	}
	static void SetAssetManager(AssetManager* mgr)
	{
		ASSERT(G::asset == nullptr);
		G::asset = mgr;
	}
	static void SetAudioManager(AudioManager* audio)
	{
		ASSERT(G::audio == nullptr);
		G::audio = audio;
	}

	static Game* GetGame() { return game; }
	static AssetManager* GetAssetManager() { return asset; }
	static AudioManager* GetAudioManager() { return audio; }

private:
	static Game* game;
	static AssetManager* asset;
	static AudioManager* audio;
};