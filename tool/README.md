# Compiling with the tools

The script `install-homunculus.command` above can be used to
automatically compile Inexor or to generate Eclipse, CodeBlocks, 
Xcode projects. For Mingw users it can also generate
visual studio projects.

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
* SDL2
* SDL2_Image
* SDL2_Mixer
* ASIO
* Google Protobuf

Depending on your environment you also need some of those:

* make (on linux, mingw)
* Eclipse (if you want to use Eclipse)
  * egit Plugin (install it using the Eclipse Marketplace)
* CodeBlocks (if you want to use CodeBlocks)
* Xcode (on Mac OS X)
* CMake GUI (optional)
* Github for Mac/Windows (optional)
