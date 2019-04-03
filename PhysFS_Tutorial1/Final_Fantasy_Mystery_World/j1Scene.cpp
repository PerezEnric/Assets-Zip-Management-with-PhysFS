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
	bool ret = App->asset_manager->Exists("sprites/Entity.png");
	
	SpawnEntity("data/entity_data.xml");

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

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 300 * dt;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 300 * dt;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 300 * dt;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 300 * dt;

	App->render->Blit(texture, 0, 0, &rect, false);

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

bool j1Scene::SpawnEntity(std::string file)
{
	pugi::xml_document data_file;
	char* buffer;
	int file_size = App->asset_manager->LoadData(file.c_str(), &buffer);
	pugi::xml_parse_result result = data_file.load_buffer(buffer, file_size);

	pugi::xml_node attributes = data_file.child("data");
	LoadImages(attributes);

	return true;
}

bool j1Scene::LoadImages(pugi::xml_node attributes)
{
	bool ret = true;
	pugi::xml_node node = attributes.child("texture");
	std::string text = node.attribute("file").as_string();

	
	texture = App->tex->Load(text.c_str());

	return ret;
}

