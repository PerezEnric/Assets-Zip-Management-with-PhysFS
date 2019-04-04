#include "p2Defs.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1AssetManager.h"
#include "PhysFS/include/physfs.h"
#include "SDL/include/SDL.h"

#pragma comment( lib, "PhysFS/lib/physfs.lib" )

j1AssetManager::j1AssetManager() : j1Module()
{
	name = ("asset_manager");

	//TODO 1: initialize the filesystem


	//This works as a default path
	CreatePath(".");
}

// Destructor
j1AssetManager::~j1AssetManager()
{
	//TODO 1: and close any files opened via PhysicsFS

}

bool j1AssetManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Asset Manager");

	// TODO 2: add an archive to the search path


	return true;
}

bool j1AssetManager::CreatePath(const char* newDir, const char* mount_point)
{
	bool ret = true;
	PHYSFS_mount(newDir, mount_point, 1); //Here we mount an archive file into the virtual filesystem created by init

	if (PHYSFS_mount(newDir, mount_point, 1) == 0)
		LOG("Error: %s\n", PHYSFS_getLastError());
	else
		ret = false;

	return ret;
}

// Make sure that the file exists
bool j1AssetManager::Exists(const char* file) const
{
	return PHYSFS_exists(file);
}

// Here we read the file and allocate needed bytes to a buffer and write all data into it
uint j1AssetManager::LoadData(const char* file, char** buffer) const
{
	uint ret = 0;

	//TODO 3: We need to open and read the file we want to.
	//Make sure that the file is not nullptr
	//Also allocate memory in a buffer of the size of the fil


	//TODO 4: Now we have to read data from a PhysFS filehandle
	//Make sure that the lenght of the data readed is the same as the lenght of the file
	//If it is not, we delete the buffer
	//If they are the same, we return the lenght of the readed data
	//Finally, we close the handle used
	

	return ret;
}

// This is will be used to load an image/fx/music from a memory buffer with SDL
SDL_RWops* j1AssetManager::Load(const char* file) const
{
	char* buffer;
	int size = LoadData(file, &buffer); //We get the size of the data from the previous function

	if (size > 0)
	{
		SDL_RWops* r = SDL_RWFromConstMem(buffer, size); //We prepare a read-only buffer
		
		return r;
	}
	else
		return nullptr;
}
