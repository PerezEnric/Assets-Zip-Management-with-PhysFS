#include "j1AssetManager.h"
#include "p2Log.h"
#include "j1App.h"
#include "SDL/include/SDL.h"
#include "PhysFS/include/physfs.h"

#pragma comment( lib, "PhysFS/lib/physfs.lib" )

j1AssetManager::j1AssetManager()
{
	name.assign("asset_manager");

	PHYSFS_init(nullptr);
	
}

j1AssetManager::~j1AssetManager()
{
	PHYSFS_deinit();
}

