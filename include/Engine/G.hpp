#pragma once

#include "Game.hpp"
#include "AssetManager.hpp"

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
		asset = mgr;
	}

	static Game* GetGame() { return game; }
	static AssetManager* GetAssetManager() { return asset; }

private:
	static Game* game;
	static AssetManager* asset;
};