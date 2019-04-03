#ifndef __j1ASSETMANAGER_H__
#define __j1ASSETMANAGER_H__

#include "j1Module.h"

struct SDL_RWops;

int close_sdl_rwops(SDL_RWops *rw);

class j1AssetManager : public j1Module
{
public:

	j1AssetManager();

	// Destructor
	virtual ~j1AssetManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	uint LoadData(const char* file, char** buffer) const;

	bool CreatePath(const char* newDir, const char* mount_point = nullptr);

	bool Exists(const char* file) const;

	SDL_RWops* Load(const char* file) const;

private:

};

#endif // __j1FILESYSTEM_H__