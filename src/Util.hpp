#pragma once

#include <assert.h>
#include "AssetManager.hpp"

class Util
{
public:
	static void SetAssetManager(AssetManager* mgr)
	{
		assert(asset == nullptr);
		asset = mgr;
	}
	static AssetManager* GetAssetManager() { return asset; }

private:
	static AssetManager* asset;
};