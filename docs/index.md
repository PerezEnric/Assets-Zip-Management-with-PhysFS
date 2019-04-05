# Assets Management with PhysFS

## Links

* [Handouts](https://github.com/PerezEnric/Assets-Zip-Management-with-PhysFS/releases/tag/Handout)
* [Solution](https://github.com/PerezEnric/Assets-Zip-Management-with-PhysFS/releases/tag/Solutionv1.0)
* [Repository](https://github.com/PerezEnric/Assets-Zip-Management-with-PhysFS)
* [Presentation](https://github.com/PerezEnric/Assets-Zip-Management-with-PhysFS/blob/master/docs/WebsiteImages/Presentation_PhysFS.pptx)

Many times game developers find that when they make a build of a game it is too heavy due to assets folders and files.
One way to solve this problem is to compress all this data in a compressed archive, like .zip, and loading all the files from that using a library called PhysFS. And this is what we are going to see below adding some SDL features like SDL_RWops.

## Objective

Our main goal is to have our release folder with only the .dll needed, the .exe and a .zip file where all the assets we will use for our game are inside. In this way, we will reduce the weight of our game.

<img src="https://github.com/PerezEnric/Assets-Zip-Management-with-PhysFS/blob/master/docs/WebsiteImages/IncorrectRelease.png?raw=true">
<img src="https://github.com/PerezEnric/Assets-Zip-Management-with-PhysFS/blob/master/docs/WebsiteImages/CorrectRelease.png?raw=true">

## PhysFS

First of all, we need to know what PhysFS is. According to icculus.org definition: "PhysFS is a library to provide abstract access to various archives". It is a portable, flexible input/output file abstraction. It brings different benefits:
* It is safe, which means that no file access is permited outside the specified directories.
* It is flexible, so achives (specially zip files) can be used transparently as directory structures.

This library is supported by the following archives:
* .ZIP (pkZip/WinZip/Info-ZIP compatible)
* .7Z (7zip archives)
* .ISO (ISO9660 files, CD-ROM images)
* .GRP (Build Engine groupfile archives)
* .PAK (Quake I/II archive format)
* .HOG (Descent I/II HOG file archives)
* .MVL (Descent II movielib archives)
* .WAD (DOOM engine archives)
* .VDF (Gothic I/II engine archives)
* .SLB (Independence War archives)

### PhysFS functions

Let's start by introducing a sort of functions in order to set up the library:

* **PHYSFS_init**(): initializes the library. It must be called before any other PhysFS function.
* **PHYSFS_deinit**(): closes any files opened via PhysFS, blanks the search/write paths and frees the memory.
* **PHYSFS_mount**(const char* _newDir_, const char* _mountPoint_, int _appendToPath_ ): add an archive or directory to the search path. _newDir_ directory or archive to add to the path, _mountPoint_ is the location that this archive will be "mounted", NULL or "" is equivalent to "/". _AppendToPath_ may be a non-zero value to append to search path.
* **PHYSFS_addToSearchPath**(const char* _newDir_, int _appendToPath_): add an archive or directory to the search path. this works in the same way as PhysFS_mount().
* **PHYSFS_openRead**(const char* _filename_): opens a file for reading, in platform-independent notation. _Filename_ is the file we want to open.
* **PHYSFS_fileLength**(PHYSFS_file* _handle_): gets the total length of a file in bytes. _Handle_ is the handle returned from PHYSFS_openRead().
* **PHYSFS_Read**(PHYSFS_File* _handle_, void* _buffer_, PHYSFS_uint32 _objSize_, PHYSFS_uint32 _objCount_): reads data from a PhysFS filehandle. _Handle_ is the handle returned from PHYSFS_openRead(), _buffer_ is where data info is stored, _objSize_ is size in bytes of objects readed from handle and _objCount_ number of objects to read from handle.
* **PHYSFS_close**(PHYSFS_file* _handle_): closes a PhysFs filehandle. _Handle_ is the handle returned from PHYSFS_openRead();
* **PHYSFS_getLastErrorCode**(): get machine-readable error information.

## SDL_RWops

According to SDL Wiki, SDL_RWops is an abstraction over input/output. It provides interfaces to read, write and seek data in a stream, without the caller needing to know where the data is coming from.

### SDL_RWops functions

The function that will be used are the following ones:

* **IMG_Load_RW**(SDL_RWops* _src_, int _freesrc_): This can load images from memory buffer. The image is load from _src_, if we want that _src_ is automatically freed or closed we have to add an non-zero value in _freesrc_. 
* **Mix_LoadWAV_RW**(SDL_RWops* _src_, int _freesrc_): This can load WAVE, AIFF, RIFF, OGG, and VOC formats from memory buffer. The sample is loaded from the _src_ pointer. As the previous function, we can add a non-zero value in _freesrc_ to close or free automatically _src_.
* **Mix_LoadMUS_RW**(SDL_RWops* _src_, int _freesrc_):  This can load WAVE, MOD, MIDI, OGG, MP3, FLAC from memory buffer. Again, as functions mentioned before, _src_ is the pointer that the sample is loaded from this and _freesrc_ with a non-zero value is to free or close automatically.
* **SDL_RWFromConstMem**(const void* _mem_, int _size_): this prepares a read-only buffer memory buffer for use with SDL_RWops. _mem_ is a pointer to a read-only buffer, _size_ the buffer size in bytes.

## Code Structure

### Assets ZIP
In order to start to understand the code, we have to take a look to the folder where all data files are provided, called _Assets.zip_.
Here, we will find 3 folders called _audio_, _data_ and _sprites_ respectively.
* _Audio_: folder that contains another folder called _sfx_ where a sample called _fx_sound.wav_ is inside.
* _Data_: folder that contains 2 xml documents called _entity_data.xml_ and _fx_data.xml_. Both only contain the path where the image and the fx are in their respective folder. For now, it is enough to get to know how to load files from xml in zip files. 

```
<data>

<texture file = "sprites/Entity.png"/>

</data>
```

```
<data>
  
<fx file="audio/sfx/fx_sound.wav"/>
  
</data>
```

* _Sprites_: this folder only contains a png image.

<img src="https://github.com/PerezEnric/Assets-Zip-Management-with-PhysFS/blob/master/docs/WebsiteImages/Assets_Folder_gif.gif?raw=true">

### Code

#### Header

First of all, we can see the different methods of the class called _j1AssetManager_.

```
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

};
```


To begin with, let's see the constructor and destructor. Their main role here is to initialize and close the PhysFS library respectively.

```
j1AssetManager();

virtual ~j1AssetManager();
```

Next, we have Awake(pugi::xml_node&). As well as it is called before render is available, we will call the funtion that lets us to add a search path from where we will find all the data.

```
bool Awake(pugi::xml_node&);
```

Then, we have LoadData(const char* file, char** buffer) const. This function is one of the most important due to lets us to read the file and and allocate the needed bytes to a buffer. This function returns the size of the lenght read that we will use later to load the files from the xml.

```
uint LoadData(const char* file, char** buffer) const;
```

Now, we see the function CreatePath(const char* newDir, const char* mount_point = nullptr), where basically we use the function PhysFS_mount() in order to mount an archive file into the virtual filesystem created by init. We call it in the constructor.

```
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
```

We also have the function Exists(const char* file) const, which only returns true if the file exists.

```
bool j1AssetManager::Exists(const char* file) const
{
	return PHYSFS_exists(file);
}
```

Finally, we have Load(const char* file) const, which lets us to load images/fx/music from a memory buffer with SDL. This method with be called in IMG_Load_RW(), Mix_LoadWAV_RW() and Mix_LoadMUS_RW().

```
SDL_RWops* Load(const char* file) const;
```

## TODOs and Solutions
### TODO 1: Initialize and close the PhysFS library
What you have to do is to use the methods mentioned before to initialize and close the library in their respective place

#### Solution

```
j1AssetManager::j1AssetManager() : j1Module()
{
	name = ("asset_manager");

	PHYSFS_init(nullptr);

	//This works as a default path
	CreatePath(".");
}

// Destructor
j1AssetManager::~j1AssetManager()
{
	PHYSFS_deinit();
}
```

### TODO 2: add an archive to the search path
Here, you have to call another function in order to search the path where the data is

#### Solution:

```
bool j1AssetManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Asset Manager");
  
	PHYSFS_addToSearchPath("Assets.zip", 1);

	return true;
}
```

### TODO 3: open and read the file we want to
* You will need to use the correct function to open and read file
* Make sure that the file is not nullptr
* Also allocate memory in a buffer of the size of the file

### TODO 4: read data from a PhysFS filehandle
* Make sure that the lenght of the data readed is the same as the lenght of the file
* If it is not, we delete the buffer
* If they are the same, we return the lenght of the readed data
* Finally, we close the handle used

#### Solution TODO 3 and 4

```
uint j1AssetManager::LoadData(const char* file, char** buffer) const
{
	uint ret = 0;

	PHYSFS_file* data_file = PHYSFS_openRead(file); 

	if (data_file != nullptr)
	{
		int file_lenght = PHYSFS_fileLength(data_file); 
		*buffer = new char[(uint)file_lenght];
		uint readed = PHYSFS_read(data_file, *buffer, 1, (uint)file_lenght); 
		if (readed != file_lenght)
		{
			LOG("Error while reading from file %s: %s\n", file, PHYSFS_getLastError());
			RELEASE(buffer);
		}
		else
			ret = readed;

		PHYSFS_close(data_file);
	}
	else
		LOG("Error while opening file %s: %s\n", file, PHYSFS_getLastError());

	return ret;
}
```

### TODO 5: replace the functions into the new ones
* Now we read from a memory buffer
* Use the functions explained earlier in relation to SDL_RWops
* Remember that you need to use different methods from the old ones

#### Solution

```
music = Mix_LoadMUS_RW(App->asset_manager->Load(path), 1);
```

```
Mix_Chunk* chunk = Mix_LoadWAV_RW(App->asset_manager->Load(path), 1);
```

```
SDL_Surface* surface = IMG_Load_RW(App->asset_manager->Load(path), 1);
```

### TODO 6: uncomment he methods
* Basically this one in to get feedback if the library and methods are well implemented

#### Solution
If everything went well, you should see the following image and play a fx when you press F.
<img src="https://github.com/PerezEnric/Assets-Zip-Management-with-PhysFS/blob/master/docs/WebsiteImages/FeedBack_Capture.JPG?raw=true">

## Links to Resources
* [https://icculus.org/physfs/](https://icculus.org/physfs/)
* [https://icculus.org/physfs/physfstut.txt](https://icculus.org/physfs/physfstut.txt)
* [https://gamedev.stackexchange.com/questions/37820/how-do-you-set-up-physfs-for-use-in-a-game](https://gamedev.stackexchange.com/questions/37820/how-do-you-set-up-physfs-for-use-in-a-game)
* [https://gregfmartin.com/2017/01/02/physicsfsphysfs-basic-tutorial/](https://gregfmartin.com/2017/01/02/physicsfsphysfs-basic-tutorial/)
* [http://sdl.beuc.net/sdl.wiki/SDL_RWops](http://sdl.beuc.net/sdl.wiki/SDL_RWops)
* [https://icculus.org/physfs/docs/html/physfs_8h.html](https://icculus.org/physfs/docs/html/physfs_8h.html)
* [https://icculus.org/physfs/docs/html/physfs_8h.html#a0956d926822291a23ee540c2ffefa1af](https://icculus.org/physfs/docs/html/physfs_8h.html#a0956d926822291a23ee540c2ffefa1af)
* [https://github.com/carcasanchez/ALinkBetweenAges](https://github.com/carcasanchez/ALinkBetweenAges)

## Author
This research has been bone by Enric Pérez Rifà.

Github: [PerezEnric](https://github.com/PerezEnric)
Email: enriic19@gmail.com
