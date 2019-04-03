#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"


struct SDL_Texture;
struct SDL_Rect;


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool SpawnEntity(std::string file, iPoint position);

	bool LoadImages(pugi::xml_node attributes);

public:

private:
	
	SDL_Texture * texture = nullptr;
	SDL_Rect rect = { 0, 0, 16, 31 };
	
};

#endif // __j1SCENE_H__