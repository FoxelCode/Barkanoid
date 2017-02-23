#pragma once

#include "AssetManager.hpp"

class G
{
public:
	static void SetAssetManager(AssetManager* mgr)
	{
		ASSERT(asset == nullptr);
		asset = mgr;
	}
	static AssetManager* GetAssetManager() { return asset; }

private:
	static AssetManager* asset;
};