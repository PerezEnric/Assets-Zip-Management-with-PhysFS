# Assets Management with PhysFS

Many times game developers find that when they make a build of a game it is too heavy due to assets folders and files.
One way to solve this problem is to compress all this data in a compressed archive, like .zip, and loading all the files from that using a library called PhysFS. And this is what we are going to see below adding some SDL features like SDL_RWops.

## PhysFS

First of all, according to icculus.org definition: "PhysFS is a library to provide abstract access to various archives". It is a portable, flexible input/output file abstraction. It brings different benefits:
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
* PHYSFS_mount(const char* newDir, const char* mountPoint, int appendToPath ): add an archive or directory to the search path.
* **PHYSFS_openRead**(const char* _filename_): opens a file for reading, in platform-independent notation. _Filename_ is the file we want to open.
* **PHYSFS_fileLength**(PHYSFS_file* _handle_): gets the total length of a file in bytes. _Handle_ is the handle returned from PHYSFS_openRead().
* **PHYSFS_Read**(PHYSFS_File* _handle_, void* _buffer_, PHYSFS_uint32 _objSize_, PHYSFS_uint32 _objCount_): reads data from a PhysFS filehandle. _Handle_ is the handle returned from PHYSFS_openRead(), _buffer_ is where data info is stored, _objSize_ is size in bytes of objects readed from handle and _objCount_ number of objects to read from handle.
* **PHYSFS_close**(PHYSFS_file* _handle_): closes a PhysFs filehandle. _Handle_ is the handle returned from PHYSFS_openRead();
* **PHYSFS_getLastErrorCode**(): get machine-readable error information.

## SDL_RWops

According to SDL Wiki SDL_RWops is an abstraction over input/output. It provides interfaces to read, write and seek data in a stream, without the caller needing to know where the data is coming from.

### SDL_RWops functions

The function that will be used are the follwuing ones:

* **IMG_Load_RW**(SDL_RWops* _src_, int _freesrc_): This can load all supported image formats, except TGA (raster images and bitmaps file format). The image is load from _src_, if we want that _src_ is automatically freed or closed we have to add an non-zero value in _freesrc_. 
* **Mix_LoadWAV_RW**(SDL_RWops* _src_, int _freesrc_): This can load WAVE, AIFF, RIFF, OGG, and VOC formats. The sample is loaded from the _src_ pointer. As the previous function, we can add a non-zero value in _freesrc_ to close or free automatically _src_.
* **Mix_LoadMUS_RW**(SDL_RWops* _src_, int _freesrc_):  This can load WAVE, MOD, MIDI, OGG, MP3, FLAC. Again, as fucntions mentioned before, _src_ is the pointer that the sample is loaded from this and _freesrc_ with a non-zero value is to free or close automatically.
* **SDL_RWFromConstMem**(const void* _mem_, int _size_): this prepares a read-only buffer memory buffer for use with SDL_RWops. _mem_ is a pointer to a read-only buffer, _size_ the buffer size in bytes.
