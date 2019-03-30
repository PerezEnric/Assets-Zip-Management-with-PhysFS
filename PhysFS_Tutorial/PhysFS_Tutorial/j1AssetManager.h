#ifndef __j1ASSETMANAGER_H__
#define __j1ASSETMANAGER_H__

#include "j1Module.h"

class j1AssetManager:public j1Module
{
public:
	j1AssetManager();
	~j1AssetManager();

	//// Called before render is available
	//bool Awake(pugi::xml_node&);

	//// Called before quitting
	//bool CleanUp();

	
};

#endif