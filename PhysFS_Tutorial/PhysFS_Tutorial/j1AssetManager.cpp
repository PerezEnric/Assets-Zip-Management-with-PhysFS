#include "j1AssetManager.h"
#include "p2Log.h"
#include "j1App.h"
#include "SDL/include/SDL.h"
#include "PhysFS/src/physfs.h"

#pragma comment( lib, "PhysFS/libx86/physfs.lib" )

j1AssetManager::j1AssetManager()
{
	name.assign("asset_manager");

	//char* base_path = SDL_GetBasePath();
	PHYSFS_init(nullptr);
	
}

j1AssetManager::~j1AssetManager()
{
	PHYSFS_deinit();
}
//
//bool j1AssetManager::Awake(pugi::xml_node &config)
//{
//	bool ret = true;
//	for (pugi::xml_node path = config.child("path"); path; path = path.next_sibling("path"))
//	{
//		LoadPath(path.child_value(), nullptr);
//	}
//
//	//char* write_path = SDL_GetPrefPath(App->GetOrganization(), App->GetTitle());
//
//	//if (PHYSFS_setWriteDir(write_path) == 0)
//	//	LOG("File System error while creating write dir: %s\n", PHYSFS_getLastError());
//	//else
//	//{
//	//	// We add the writing directory as a reading directory too with speacial mount point
//	//	LOG("Writing directory is %s\n", write_path);
//	//	AddPath(write_path, GetSaveDirectory());
//	//}
//
//	/*SDL_free(write_path);*/
//
//	return ret;
//}
//
//bool j1AssetManager::LoadPath(const char* zip_path, const char* mount_point)
//{
//	bool ret = true;
//
//	PHYSFS_mount(zip_path, mount_point, 1);
//
//	if (PHYSFS_mount(zip_path, mount_point, 1) == 0)
//	{
//		LOG("Error while adding zip path (%s): %s\n", zip_path, PHYSFS_getLastError());
//	}
//
//	return ret;
//}
//
//bool j1AssetManager::CleanUp()
//{
//	return true;
//}
