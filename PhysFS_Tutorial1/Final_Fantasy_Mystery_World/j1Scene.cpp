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
	bool ret = App->asset_manager->Exists("audio/music/first_track.ogg");
	
	PrintImage();
	

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

	App->render->Blit(texture, 0, 0, &rect, false);

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		App->audio->PlayFx(1);
	/*App->audio->LoadMusicFile();*/
	LoadSceneMusic();
	LOG("LALALA");

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
	pugi::xml_parse_result result = data_file.load_buffer(buffer, file_size);

	pugi::xml_node attributes = data_file.child("data").child("texture");
	texture = App->tex->Load(attributes.attribute("file").as_string());

	return true;
}

bool j1Scene::LoadSceneMusic()
{
	pugi::xml_document music_document;
	char* music_buffer;
	int music_file_size = App->asset_manager->LoadData("data/music_data.xml", &music_buffer);
	pugi::xml_parse_result result_music = music_document.load_buffer(music_buffer, music_file_size);
	RELEASE(music_buffer);

	pugi::xml_node music_node = music_document.child("data").child("track");
	App->audio->PlayMusic(music_node.attribute("file").as_string());

	return true;
}

