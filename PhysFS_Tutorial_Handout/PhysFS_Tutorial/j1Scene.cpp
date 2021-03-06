#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1AssetManager.h"
#include <string>

#include "Brofiler/Brofiler.h"

j1Scene::j1Scene() : j1Module()
{
	name.assign("scene");

}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	bool ret = App->asset_manager->Exists("data/entity_data.xml");
	
	//TODO 6: uncomment this methods to get feedback

	/*PrintImage();
	App->audio->LoadFxFile();*/

	return ret;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateScene", Profiler::Color::Orange);
	// debug pathfing ------------------


	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("UpdateScene", Profiler::Color::Aqua);

	App->render->Blit(texture, 0, 0, &rect, false); //If everything is correct and image will be printed

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) // and a fx will be reproduced
		App->audio->PlayFx(1);

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateScene", Profiler::Color::Purple);

	bool ret = true;

	


	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool j1Scene::PrintImage()
{
	pugi::xml_document data_file;
	char* buffer;
	int file_size = App->asset_manager->LoadData("data/entity_data.xml", &buffer);
	pugi::xml_parse_result result = data_file.load_buffer(buffer, file_size); //We load the buffer as an immutable one
	RELEASE(buffer)

	pugi::xml_node attributes = data_file.child("data").child("texture");
	texture = App->tex->Load(attributes.attribute("file").as_string());

	return true;
}

