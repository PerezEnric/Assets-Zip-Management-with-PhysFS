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

	//Here we initialize the filesystem
	PHYSFS_init(nullptr);

	//This works as a default path
	CreatePath(".");
}

// Destructor
j1AssetManager::~j1AssetManager()
{
	//Here we close any files opened via PhysicsFS, blanks the search / write paths,
	//frees memory, and invalidates all of your file handles.
	PHYSFS_deinit();
}

bool j1AssetManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Asset Manager");

	// Here we set up any archives that will be read from. This
	//adds an archive to the search path (as its name says)
	PHYSFS_addToSearchPath("Assets.zip", 1);

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

	PHYSFS_file* data_file = PHYSFS_openRead(file); //We open and read the file we want to 

	if (data_file != nullptr)
	{
		int file_lenght = PHYSFS_fileLength(data_file); //We get the file size to find out how many bytes you need to allocate for the file.
		*buffer = new char[(uint)file_lenght]; //We allocate memory in a buffer of the size of the file
		uint readed = PHYSFS_read(data_file, *buffer, 1, (uint)file_lenght); //We read data from a PhysFS filehandle
		if (readed != file_lenght) //If the file lenght is not the same that the one was readed, there will be an error
		{
			LOG("Error while reading from file %s: %s\n", file, PHYSFS_getLastError());
			RELEASE(buffer); //We delete the buffer
		}
		else
			ret = readed; //If everything goes well, we return the size of the data

		PHYSFS_close(data_file); //Now we close the PhysFs handle used to read the data
	}
	else
		LOG("Error while opening file %s: %s\n", file, PHYSFS_getLastError());

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
