## Changelog

### Inexor - Coffein Edition (alpha 0.1, 2015-04-11)

* Choosed the name of the game

#### Develoment environment

* Github source code, issues, wiki
* Travis build server
* Waffle.io kanboard
* Separate repositories for code and content

#### More flexible build system

* CMake setup (unified cross platform build environment)
* New file structure for generated binaries
* Separated external libraries from our source (including enet)

#### Refactoring and code cleanup

* Remove static file paths
* Remove rpggame
* Remove cube 1 map loader
* Cleaner data/media structure

#### Integration of 3rd party libraries

* SDL2 (including better fullscreen support under linux)
* muparser (math expression library)
* JSON API
* JSON Import API (not completed yet)
* JSON references to other JSON files

#### Unit tests

* Integrated unit test framework: google test

#### API documentation

* Defined a standardized way of documenting packages and their content
* Documentation guidelines
* Integrated Doxygen

#### Licensing and content management

* Choose legitimate licenses to use for content ("License Policy")
* Removed non-free content (textures, models, maps)
* Fixed file paths

#### Texture management and distribution

* JSON files contains information about the texture files, the texture settings and the texture meta data
* Distribution of textures using JSON files

#### Gameplay

* Renamed /kill to /suicide

#### Inter process communication

* Communication with the inexor process
* External NodeJS integration

#### Graphics

* Implemented ambient occlusion during the calclight process (zero cost ingame, calculated during calclight)
