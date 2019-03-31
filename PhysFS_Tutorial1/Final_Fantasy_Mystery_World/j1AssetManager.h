#ifndef __j1ASSETMANAGER_H__
#define __j1ASSETMANAGER_H__

#include "j1Module.h"

struct SDL_RWops;

//int close_sdl_rwops(SDL_RWops *rw);

class j1AssetManager : public j1Module
{
public:

	j1AssetManager();

	// Destructor
	virtual ~j1AssetManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);
	uint LoadData(const char* file, char** buffer);

	//// Called before quitting
	//bool CleanUp();

	//// Utility functions
	bool CreatePath(const char* zip_path, const char* mount_point = nullptr);
	//bool Exists(const char* file) const;
	//bool IsDirectory(const char* file) const;
	//const char* GetSaveDirectory() const
	//{
	//	return "";
	//}

	//// Open for Read/Write
	//unsigned int Load(const char* file, char** buffer) const;
	//SDL_RWops* Load(const char* file) const;

	//unsigned int Save(const char* file, const char* buffer, unsigned int size) const;

private:

};

#endif // __j1FILESYSTEM_H__