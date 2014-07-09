# Compiling with the tools

The script `install-homunculus.sh` above can be used to
automatically compile Sauerbraten fork or to generate
Eclipse, Code Blocks, Xcode projects. For Mingw users it
can also generate visual studio projects.

It works on OS X, Debian (and derivatives, e.g. Ubuntu),
Arch Linux and MinGW.

Just download and run it.

Mac users will have to install XCode first.

## Without tools

### Install the dependencies

First you need to install the dependencies. Those boil down
to:

* Git
* A compile (e.g. GCC)
* A linker (e.g. GCC)
* Cmake
* OpenGL
* SDL
* SDL_Image
* SDL_Mixer

Depending on your environment you also need some of those:

* make (linux, mingw)
* Eclipse or (if you want to use eclipse)
* Xcode (under Mac OS X)
* CMake GUI (optional)
* Github for Mac/Windows (optional)
