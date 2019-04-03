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

	CreatePath(".");
}

// Destructor
j1AssetManager::~j1AssetManager()
{
	PHYSFS_deinit();
}

bool j1AssetManager::CreatePath(const char* newDir, const char* mount_point)
{
	bool ret = true;
	PHYSFS_mount(newDir, mount_point, 1);

	if (PHYSFS_mount(newDir, mount_point, 1) == 0)
		LOG("Error: %s\n", PHYSFS_getLastError());
	else
		ret = false;

	return ret;
}

bool j1AssetManager::Exists(const char * file) const
{
	return PHYSFS_exists(file);
}

bool j1AssetManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Asset Manager");

	PHYSFS_addToSearchPath("Assets.zip", 1);

	return true;
}

uint j1AssetManager::LoadData(const char* file, char** buffer) const
{
	uint ret = 0;

	PHYSFS_file* data_file = PHYSFS_openRead(file);

	if (data_file != nullptr)
	{
		int file_lenght = PHYSFS_fileLength(data_file);
		*buffer = new char[(uint)file_lenght];
		uint readed = PHYSFS_read(data_file, *buffer, 1, (uint)file_lenght);
		if (readed != file_lenght)
		{
			LOG("Error while reading from file %s: %s\n", file, PHYSFS_getLastError());
			RELEASE(buffer);
		}
		else
			ret = readed;

		PHYSFS_close(data_file);
	}
	else
		LOG("Error while opening file %s: %s\n", file, PHYSFS_getLastError());

	return ret;
}

// And this is how you load an image from a memory buffer with SDL
SDL_RWops* j1AssetManager::Load(const char* file) const
{
	char* buffer;
	int size = LoadData(file, &buffer);

	if (size > 0)
	{
		SDL_RWops* r = SDL_RWFromConstMem(buffer, size);
		
		return r;
	}
	else
		return nullptr;
}

int close_sdl_rwops(SDL_RWops *rw)
{
	RELEASE_ARRAY(rw->hidden.mem.base);
	SDL_FreeRW(rw);
	return 0;
}

