// ----------------------------------------------------
// j1Module.h
// Interface for all engine modules
// ----------------------------------------------------

#ifndef __j1MODULE_H__
#define __j1MODULE_H__

#include <string>
#include "PugiXml\src\pugixml.hpp"

class j1App;
struct Collider;
class GUI;

class j1Module
{
private:
	bool enabled = true;

public:

	j1Module() : active(false)
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}
	void Enable()
	{
			active = true;
			Start();
	}

	void Disable()
	{
			active = false;
			CleanUp();
	}

	// Callbacks ---
	virtual void OnCollision(Collider*, Collider*) {}
	virtual bool Interact(GUI* element) { return true; }

public:

	std::string	name;
	bool		active;

};

#endif // __j1MODULE_H__