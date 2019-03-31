#include "p2Defs.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1AssetManager.h"
#include "PhysFS2/include/physfs.h"
#include "SDL/include/SDL.h"

#pragma comment( lib, "PhysFS2/lib/physfs.lib" )

j1AssetManager::j1AssetManager() : j1Module()
{
	name = ("asset_manager");

	PHYSFS_init(nullptr);

}

// Destructor
j1AssetManager::~j1AssetManager()
{
	PHYSFS_deinit();
}

bool j1AssetManager::CreatePath(const char* zip_path, const char* mount_point)
{
	bool ret = true;
	PHYSFS_mount(zip_path, mount_point, 1);

	if (PHYSFS_mount(zip_path, mount_point, 1) == 0)
		LOG("Error while adding a path or zip(%s): %s\n", zip_path, PHYSFS_getLastError());
	else
		ret = false;

	return ret;
}

bool j1AssetManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Asset Manager");

	PHYSFS_addToSearchPath("Assets.zip", 1);

	for (pugi::xml_node path = config.child("path"); path; path = path.next_sibling("path"))
	{
		CreatePath(config.child_value());
	}

	return true;
}

uint j1AssetManager::LoadData(const char* file, char** buffer)
{
	uint ret = 0;

	PHYSFS_file* data_file = PHYSFS_openRead(file);

	if (data_file != nullptr)
	{
		int file_lenght = PHYSFS_fileLength(data_file);
		*buffer = new char[(uint)file_lenght];
		PHYSFS_sint64 readed = PHYSFS_read(data_file, *buffer, 1, (PHYSFS_sint64)file_lenght);
		if (readed != file_lenght)
		{
			LOG("Error while reading from file %s: %s\n", file, PHYSFS_getLastError());
			RELEASE_ARRAY(buffer);
		}
		else
			ret = (uint)readed;

		PHYSFS_close(data_file);
	}
	else
		LOG("Error while opening file %s: %s\n", file, PHYSFS_getLastError());

	return ret;
}

