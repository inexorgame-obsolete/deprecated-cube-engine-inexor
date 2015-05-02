## Changelog

### Inexor - Caffeine Edition (v0.1-alpha, 2015-05-01)

* Choosed the name of the game

#### Develoment environment

* Github source code, issues, wiki
* Travis build server
 * Nightly builds for testing
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
* Muparser (math expression library)
* JSON API
* JSON Import API (not completed yet)
 * JSON references to other JSON files

#### Unit tests

* Integrated unit test framework: Google test

#### API documentation

* Defined a standardized way of documenting packages and their content
* Documentation guidelines
* Integrated Doxygen

#### Licensing and content management

* Choose legitimate licenses to use for content ("License Policy")
* Provide some freely licensed basic textures and maps

#### Gameplay

* Renamed /kill to /suicide
* Console improvements
 * Warnings won't spam the console anymore
 * Lines are fading out, instead of simple disappear
 * Timestamps
 * History, reuse commands easily from your last game session

#### Inter process communication

* Communication with the Inexor process
* External NodeJS integration

#### Graphics

* Implemented ambient occlusion during the calclight process (zero cost ingame, calculated during calclight)
